#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <string>
#include <stdarg.h>
#include <iostream>
using namespace std;
/*
    �ռ�������
*/


/* Trace   ����*/
#define __DEBUG__

static string GetFileName(const string& path)
{
    char ch = '/';
#ifdef _WIN32
    ch = '\\';
#endif
    size_t pos=path.rfind(ch);
    if (pos == string::npos)
        return path;
    else
        return path.substr(pos + 1);
}

// ���ڵ���׷�ݵ�trace log
inline static void __trace_debug(const char* function, const char *filename, int line, char* format, ...)
{
#ifdef __DEBUG__
    // ������ú�������Ϣ
    fprintf(stdout, "[ %s:%d]%s", GetFileName(filename).c_str(), line, function);

    // ����û����trace��Ϣ
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args); // format��ʽ���ַ�ָ��   args �Ƕ��õı���
    va_end(args);
#endif
}

#define __TRACE_DEBUG(...) __trace_debug(__FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)


/////////////////////////////////////////
//             һ���ռ�������(malloc/realloc/free �ķ�װ)

// �ڴ����ʧ���Ժ�ľ������handler����
typedef void(* ALLOC_OOM_FUN)();
template<int inst>
class __MallocAllocTemplate
{
private:
    static ALLOC_OOM_FUN __sMallocAllocOomHander;

    static void* OomMalloc(size_t n)
    {
        ALLOC_OOM_FUN handler = NULL;
        void *result;
        //
        //1 :�����ڴ�ɹ��� ��ֱ�ӷ���
        //2 ��������ʧ�ܣ������Ƿ����ô����handler
        //  ��������Ժ��ٷ��䡣 �����ظ�������̣�ֱ������ɹ�Ϊֹ��
        // û�������ô����handler�� ��ֱ�ӽ�������
        //
        while (true)
        {
            handler=__sMallocAllocOomHander;
            if (handler == NULL)
            {
                cerr<<"out of memory"<<endl;
                exit(-1);
            }

            handler();

            result=malloc(n);
            if (result)
                return result;
        }
    }

    static void OomRealloc(void *p, size_t n)
    {
        // ͬ��
        ALLOC_OOM_FUN handler;
        void* result = NULL;

        for (;;)
        {
            handler=__sMallocAllocOomHander;
            if (0 == handler)
            {
                cerr<<"out of memory"<<endl;
                exit(-1);
            }
            (*handler)();
            result=realloc(p, n);
            if (result) return result;

        }

    }

public:
    static void *Allocate(size_t n)
    {
        __TRACE_DEBUG("(n:%u)\n", n);

        void *result=malloc(n);
        if (NULL == result)
            result = OomMalloc(n);
        return result;
    }

    static void* Reallocate(void *p, size_t new_sz)
    {
        void *result = realloc(p, new_sz);
        if (result == NULL)
        {
            result = OomRealloc(p, new_sz);
        }

        return result;
    }

    static void Deallocate(void *p, size_t /* n */)  // ����n���� ���������Ҫ�� ������һ�� ��Ϊclass SimpleAlloc��װһ�����ռ�������ʱ ������ʽһ��
	{
		__TRACE_DEBUG("һ���ռ������ͷſռ�:0x%p\n", p);
		free(p);
	}

    //����д��  static void(* SetMallocHandler(void(*f)()))()
    // ���û�ȡ�ռ�� �������
    static ALLOC_OOM_FUN SetMallocHandler(ALLOC_OOM_FUN f)
    {
        ALLOC_OOM_FUN old = __sMallocAllocOomHander;
        __sMallocAllocOomHander = f;
        return old;
    }
};

// �����ڴ�ʧ��ʱ�������ľ������ָ��
// ��ʼ����̬����

template <int inst>
ALLOC_OOM_FUN __MallocAllocTemplate<inst>::__sMallocAllocOomHander = NULL;





/////////////////////////////  �����ռ�������  /////////////////////////////////////////
//
template<bool threads, int inst>// instû�� �����Ժ���չ�� Ԥ����
class __DefaultAllocTemplate
{
private:
    enum {__ALIGN = 8};                 // ���л�׼ֵ�����еļ�� ��
    enum {__MAX_BYTES = 128};            // ���ֵ
    enum {__NFREELISTS = __MAX_BYTES/__ALIGN};  // �������Ĵ�С
    // �� �ڴ�����ȡ�� �� �Ǹ���Χ   �� 1,2,3,4,5,6,7��8 ----�� 8
    static size_t ROUND_UP(size_t bytes)
    {
        // ����
        // 7 8 9
        // 8 8 16
        return ((bytes + __ALIGN - 1) & ~(__ALIGN - 1));
    }

    // �� �ڴ��С��������±�
    static size_t FREELIST_INDEX(size_t bytes)
    {
        // bytes == 9    -----> 1
        // bytes == 8     ---->  0
        // bytes == 7     ----->  0
        return ((bytes + __ALIGN - 1)/ __ALIGN - 1);
    }

    union Obj
    {
        union Obj* _freeListLink; // ָ��дһ���ڴ���ָ��
        char _clientData[1]; /* the client sees this �����õ�  ����û����*/
    };


    static Obj* volatile _freeList[__NFREELISTS]; // ��������
    static char *_startFree;             // �ڴ�� ˮλ�߿�ʼ
    static char *_endFree;             // �ڴ��ˮλ�߽���
    static size_t _heapSize;          // ��ϵͳ�ѷ�����ܴ�С

    // ��ȡ����ڴ� ���뵽����������
     static void *Refill(size_t n);
    // ���ڴ�ط������ڴ�
    static char* ChunkAlloc(size_t size, int &nobjs); // nobjs ֻ�ǽ���Ĵ�С ����������ܻ��޸�
public:
    static void *Allocate(size_t n);
    static void Deallocate(void *p, size_t n);
    static void *Reallocate(void *p, size_t old_sz, size_t new_sz);
};


// ��ʼ��ȫ�־�̬����
template<bool threads, int inst>
typename __DefaultAllocTemplate<threads, inst>::Obj* volatile __DefaultAllocTemplate<threads, inst>::_freeList[__DefaultAllocTemplate<threads, inst>::__NFREELISTS] = {0};

template<bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_startFree = 0;

template<bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::_endFree = 0;
template<bool threads, int inst>
size_t __DefaultAllocTemplate<threads, inst>::_heapSize = 0;


/*   �ٶ�������� n   �����Ѿ�aligned �����*/
template<bool threads, int inst>
void* __DefaultAllocTemplate<threads, inst>::Refill(size_t n)
{
    __TRACE_DEBUG("(n:%u)\n", n);

    // ����һ��n bytes���ڴ�
    // �������  ���ܷ�����ٷ������


    /*������û�У���Ҫ���ڴ�����룬���� n bytes����  ��ֹ�´λ�Ҫ �� ÿ�ξͲ���ȡn�ֽ�  ���� ȡn*nobjs�ֽ� ����n�ֽ� ʣ�µĹҵ������ϡ�*/
    /*����nobjs=20 ֻ�ǽ��� 
��ΪChunkAlloc������nobjs�������������� ���� ���ܱ�20��*/
    int nobjs = 20;
    char* chunk = ChunkAlloc(n, nobjs);

    // ���ֻ����һ�飬 ��ֱ�Ӱ�����ڴ� ����
    if (nobjs == 1)
    {
        return chunk;
    }

    Obj *result, *cur;
    size_t index = FREELIST_INDEX(n);
    result = (Obj*)chunk;

    // ��ʣ��Ŀ� ���ӵ�����������
    cur = (Obj*)(chunk + n);
    _freeList[index] = cur;
    /*�������ǹ���������ʵ �ڴ滹������һƬ*/
    for (int i = 2; i < nobjs; i++)
    {
        cur->_freeListLink = (Obj*)(chunk + n*i);
        cur =  cur->_freeListLink;
    }

    cur->_freeListLink = NULL;

    return result;
}


template<bool threads, int inst>
char* __DefaultAllocTemplate<threads, inst>::ChunkAlloc(size_t size, int &nobjs)
{
    __TRACE_DEBUG("(szie�� %u, nobjs:%d)\n", size , nobjs);

    char *result;
    size_t bytesNeed = size * nobjs;
    size_t bytesLeft = _endFree - _startFree;

    // 1. �ڴ�����ڴ��㹻��bytesLeft>=bytesNeed����ֱ�Ӵ��ڴ����ȡ��
    // 2. �ڴ���е��ڴ治�㣬 ���ǹ�һ��,bytesLeft>=size, ��ֱ��ȡ�ܹ�ȡ�����ġ�
    // 3.�ڴ���е��ڴ治�㣬 ���ϵͳ�ѷ�������ڴ浽�ڴ��
    
    if (bytesLeft >= bytesNeed)
    {
        __TRACE_DEBUG("�ڴ�����ڴ��㹻����%d������\n", nobjs);
        result = _startFree;
        _startFree += bytesNeed;
    }
    else if (bytesLeft >= size)
    {
        __TRACE_DEBUG("�ڴ�����ڴ治������%d������ ֻ�ܷ���%d������\n", nobjs,bytesLeft/size);
        result = _startFree;
        nobjs = bytesLeft/size;
        _startFree += nobjs * size;
    }
    else
    {
        // ���ڴ���л���С���ʣ���ڴ棨����size��������ͷ�嵽���ʵ�����������
        if (bytesLeft > 0)
        {
            size_t index = FREELIST_INDEX(bytesLeft);//bytesLeft һ���� aligned �����
            ((Obj*)_startFree)->_freeListLink = _freeList[index];
            _freeList[index] = (Obj*)_startFree;
            _startFree = NULL;

            __TRACE_DEBUG("���ڴ����ʣ��Ŀռ䣬 �����freeList[%d]\n", index);
        }

        // ��ϵͳ�ѷ�������+�Ѿ������heapSize/16 ���ڴ浽�ڴ����
        size_t bytesToGet = 2 * bytesNeed + ROUND_UP(_heapSize >> 4); // >>4    /16
        _startFree = (char*)malloc(bytesToGet);
        __TRACE_DEBUG("�ڴ�ؿռ䲻�㣬 ϵͳ�ѷ���%u bytes�ڴ�\n",bytesToGet);

        // ������֮�١�
        // �����ϵͳ�����ڴ����ʧ�ܣ� ���Ե����������и���Ľڵ��з���

        if (_startFree == NULL)
        {
            __TRACE_DEBUG("ϵͳ���Ѿ�û���㹻���ڴ棬 ����֮�£� ֻ�ܵ����������п���\n");

            // �� �� �� �����ֽڴ�� �������ڵ�����
            // i=size  ���Լ���ǰ��������ʼ��  ����Ϊ ���̻߳��� ���ܻ��б���̻߳����ڴ�
            for (int i = size; i <= __MAX_BYTES; i += __ALIGN)
            {
                Obj *head = _freeList[FREELIST_INDEX(size)];
                if (head)
                {
                    _startFree = (char*)head;
                    // ժ�� һ���ڴ�ڵ�
                    head = head->_freeListLink;
                    //////////////////////////
                    _freeList[FREELIST_INDEX(size)] = head;
                    // ��ʽ�� ���� ���Ϲ���  ��ʵ ʵ�ʴ洢���� ���� ��������
                    // �ڴ�� ����һ��ռ� ��������齻�� ChunkALLoc �ݹ�  һ�������ߵ�ǰ����߼�����
                    _endFree = _startFree + i;
                    return ChunkAlloc(size, nobjs);
                }
            }
            _endFree = NULL;///////////////////////////////////��ֹ �Լ��ռ�������__MallocAllocTemplate<inst>::Allocate(bytesToGet);
                                                /////////////// �����쳣 ���������߼�  ���� ����쳣������  ����ִ�� ���� �������heapSize��Ϊ0
                                                ////////////// ��Ϊ _endFree��ΪNULL  �� startFreeΪ��  _endFree - _startFree ��= 0 ��ʵû�ռ� ��                                          //////////////////////��������пռ� ��ռ䲻���Լ���  �õ�ʱ��һ������   _endFree ��Ұָ��
            
            
            // ��ɽ��ˮ���� ���һ������(һ���ռ�����������
            // ����������Ҳû�з��䵽�ڴ棬 ���ٵ�һ���������з����ڴ棬
            // һ���������� ������ ���õ��ڴ洦���� �����ܷ��䵽�ڴ�

            __TRACE_DEBUG("ϵͳ�Ѻ� ����������û���ڴ棬 һ�������������һ������\n");
            _startFree = (char*)__MallocAllocTemplate<inst>::Allocate(bytesToGet);
        }

        // ��ϵͳ�ѷ�������ֽ����������������´η���ʱ���е��ڣ�
        _heapSize += bytesToGet;
        _endFree = _startFree + bytesToGet;

        // �ݹ���û�ȡ�ڴ� ��ִ�е�ǰ����߼���������䣩
        return ChunkAlloc(size, nobjs);
    }
    return result;
}


template<bool threads, int inst>
void *__DefaultAllocTemplate<threads, inst>::Allocate(size_t n)
{
    __TRACE_DEBUG("(n:%u)\n", n);

    // �� n > __MAX_BYTES ��ֱ�����Լ��ռ��������л�ȡ
    // �����ڶ����������л�ȡ
     if (n > __MAX_BYTES)
     {
         return  __MallocAllocTemplate<inst>::Allocate(n);
     }

     size_t index = FREELIST_INDEX(n);

     // 1. �������������û���ڴ���ͨ��Refill�������
     // 2. �����������������ֱ�ӷ���һ���ڵ���ڴ�
     // ps: ���̻߳���Ҫ���Ǽ���

     Obj *head = _freeList[index];
     if (head == NULL)
     {
         return Refill(ROUND_UP(n));
     }
     else
     {
        __TRACE_DEBUG("��������ȡ�ڴ�:_freeList[%d]\n", index);
         _freeList[index] = head->_freeListLink;
         return head;
     }
}

template<bool threads, int inst>
void __DefaultAllocTemplate<threads, inst>::Deallocate(void *p, size_t n)
{
    __TRACE_DEBUG("(p:%p, n:%u)\n", p ,n );

    // ��n > __MAX_BYTES��ֱ�ӹ黹��һ��������
    // �����ٷŻض�������������������

    if (n > __MAX_BYTES)
    {
    __MallocAllocTemplate<inst>::Deallocate(p, n);
    }
    else
    {
        // ps: ���̻߳���Ҫ���Ǽ���
        size_t index = FREELIST_INDEX(n);

        //ͷ�����������
        Obj *tmp = (Obj*)p;
        tmp->_freeListLink = _freeList[index];
        _freeList[index] = tmp;
    }
}

template<bool threads, int inst>
void *__DefaultAllocTemplate<threads, inst>::Reallocate(void* p, size_t old_sz, size_t new_sz)
{
    void *result;
    size_t copy_sz;
    if (old_sz > (size_t)__MAX_BYTES && new_sz > (size_t)__MAX_BYTES)
    {
        // ֱ�ӵ���һ��
        return (__MallocAllocTemplate<inst>::Reallocate(p, new_sz));
    }

    // ��ͬһ����Χ ���ô���
    if (ROUND_UP(old_sz) == ROUND_UP(new_sz))
    {
        return p;
    }

    result = Allocate(new_sz);
    copy_sz = new_sz > old_sz? old_sz: new_sz;
    memcpy(result, p, copy_sz);
    Deallocate(p, old_sz);
    return result;
}


/////////////////////////////////////////////
//     ��װ�ռ�������

#ifdef _USE_MALLOC   // ֪��ָ�� ֻʹ��һ���ռ�������
typedef __MallocAllocTemplate<0> Alloc;
#else
typedef __DefaultAllocTemplate<0,0> Alloc;
#endif

template<class T, class cAlloc = Alloc> 
class SimpleAlloc
{
public:
    static T* Allocate(size_t n) // n�Ǹ���
    {
        return 0 == n? 0 :(T*)cAlloc::Allocate(n * sizeof(T));
    }

    static T* Allocate(void) // ֻ��һ���ռ�
    {
        return (T*)cAlloc::Allocate(sizeof(T));
    }

    static void Deallocate(T *p, size_t n) // n�Ǹ���
    {
        if (0 != n)
        {
            cAlloc::Deallocate(p, n * sizeof(T));
        }
    }

    static void Deallocate(T *p)
    {
        cAlloc::Deallocate(p, sizeof(T));
    }
};





// ͨ�� __TRACE_DEBUG ���׺в���
// �����ڴ�ص�һ������������������

void TestAllocate()
{

    // ���Ե���һ�������������ڴ�
	cout<<" ���Ե���һ�������������ڴ� "<<endl ;
	char*p1 = SimpleAlloc< char, Alloc>::Allocate (129);
	SimpleAlloc<char , Alloc>:: Deallocate(p1 , 129);

    // ���Ե��ö��������������ڴ�
	cout<<" ���Ե��ö��������������ڴ� "<<endl;          //  �� 128*20*2 bytes
	char*p2 = SimpleAlloc< char, Alloc>::Allocate (128);
	char*p3 = SimpleAlloc< char, Alloc>::Allocate (128);
	char*p4 = SimpleAlloc< char, Alloc>::Allocate (128);
	char*p5 = SimpleAlloc< char, Alloc>::Allocate (128);
	SimpleAlloc<char , Alloc>:: Deallocate(p2 , 128);
	SimpleAlloc<char , Alloc>:: Deallocate(p3 , 128);
	SimpleAlloc<char , Alloc>:: Deallocate(p4 , 128);
	SimpleAlloc<char , Alloc>:: Deallocate(p5 , 128);

    for (int i = 0; i < 21; ++i) // ǰ20�� ����ȡ  ��21�� refill���ڴ��ȡ
	{
		printf(" ���Ե�%d�η��� \n", i +1);
		char*p = SimpleAlloc< char, Alloc>::Allocate (128);
	}
}
