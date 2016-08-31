#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <assert.h>
#include <stdarg.h>
#include <Windows.h>
// C++ 11
#include <unordered_map>
using namespace std;

//PerformanceProfiler
struct PPNode
{
    string _filename;
    string _function;
    size_t _line;
    string _desc; // ����������Ϣ

    PPNode(const char *filename, const char *function, const size_t line, const char *desc)
        :_filename(filename)
        ,_function(function)
        ,_line(line)
        ,_desc(desc)
    {}
    // unordered_map �� �õ�operator==
    bool operator==(const PPNode& node) const
    {
        if (_line == node._line
            && _function == node._function
               && _desc == node._desc
               && _filename == node._filename) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

typedef long long LongType;
struct PPSection
{
    PPSection()
        :_costTime(0)
        ,_callCount(0)
    {}
    // �����̰߳�ȫ��
    void Begin()
    {
        _beginTime = clock(); // <ctime>
    }

    void End()
    {
        _costTime += clock()  - _beginTime;
        ++_callCount;
    }

    LongType _beginTime; // ��ʼʱ��
    LongType _costTime;   // ����ʱ��
    LongType _callCount;  // ���õĴ���
};


// ���� hash��ֵ �� �º����ṹ��  ����stl����undered_map �ĵ�����ģ�����
//
//template < class Key,                                    // unordered_map::key_type
//           class T,                                      // unordered_map::mapped_type
//           class Hash = hash<Key>,                       // unordered_map::hasher
//           class Pred = equal_to<Key>,                   // unordered_map::key_equal
//           class Alloc = allocator< pair<const Key,T> >  // unordered_map::allocator_type
//           > class unordered_map;


struct PPNodeHash
{
    static size_t BKDRHash(const char *str)
    {
        unsigned int seed = 131; // 31 131 1313 13131 131313
        unsigned int hash = 0;
        while (*str)
        {
            hash = hash * seed + (*str++);
        }

        return (hash & 0x7FFFFFFF);
    }

    size_t operator()(const PPNode& node) const
    {
        static string hash;
        hash = node._desc;
        hash += node._function;

        return BKDRHash(hash.c_str());
    }
};

class SaveAdapter   //    ���麯��      -----�ӿ�
{
public:
    virtual void Save(const char *format, ...) = 0;
};

// �����̨ ��ӡ��Ϣ
class ConsoleSaveAdapter: public SaveAdapter
{
public:
    virtual void Save(const char *format, ...) // ʵ�ִ��麯��
    {
        // �ɱ�����б�   <stdarg.h>
        va_list args;
        va_start(args, format);
        ////////////////////////
        vfprintf(stdout, format, args);
        va_end(args);
    }

};

// ���ļ� ��ӡ��Ϣ
class FileSaveAdapter: public SaveAdapter
{
public:
    FileSaveAdapter(const char* filename)
    {
        _fout = fopen(filename, "w");
        assert(_fout);
    }
    ~FileSaveAdapter()
    {
        if (_fout)
        {
            fclose(_fout);
        }

    }

    virtual void Save(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        vfprintf(_fout, format, args);
        va_end(args);
    }

protected:
    // ������  ��Ϊ��ָ���ⲿ�ռ��ָ�� _fout   ��ֹ��ǳ�����ķ���  ����򵥴ֱ� ֱ�ӽ�ֹ �������� ��operator= ����������ָ���Scopedptr
    FileSaveAdapter(const FileSaveAdapter&);
    FileSaveAdapter& operator=(FileSaveAdapter&);

protected:
    FILE* _fout;
};

// ����  �� ȫ��ֻ��Ψһ��һ��ʵ��
// �����Ļ��� -- ����ģʽ--����ʱֱ������ʵ����Ҳ���Ի�������ģʽ--��ʱ����ʵ����
template<class T>
class Singleton
{
public:
    // ���ʵ��ָ��
    static T* GetInstance()
    {
        assert(_sInstence);
        return _sInstence;
    }
protected:
    static T* _sInstence;
};

template<class T>
T* Singleton<T>::_sInstence = new T; // ֱ�Ӵ���ģ���� T  ��ʵ��   ������ģʽ��

//////////////////////  ���ü̳� ///////////////////////////////////

class PerformanceProfiler : public Singleton<PerformanceProfiler>
    // Singleton<PerformanceProfiler> �����������ݹ�Ч��  ֻ�Ǹ���ģ�� ���� ģ����ڱ���֮ǰ ƥ��þ����ֵ ����Singleton�� 
    // ����ṹ��node �а���node* _nextһ��  ֻ��node*ָ�� ��������ݹ� �����node����node next�Ż�ݹ鶨��
{
    friend class Singleton<PerformanceProfiler>;

    // ʱ�临�Ӷ� O(1)
    //                    K           V        HashKey()
    typedef unordered_map<PPNode, PPSection*, PPNodeHash> PP_MAP;
public:
    PPSection* CreatSection(const char *filename, const char *function,const size_t line, const char* desc)
    {
        PPNode node(filename, function, line, desc);
        PPSection *section = NULL;
        PP_MAP::iterator it = _ppMap.find(node);
        if (it != _ppMap.end())
        {
            section = it->second;
        }
        else
        {
            section = new PPSection;
            _ppMap.insert(pair<PPNode, PPSection*>(node, section));
        }
        
        return section;
    }

    // �ڲ��ṹ��
    struct Report
    {
        ~Report()
        {
            // ���෽��  GetInstance  ��ȡ����ָ�� �������෽�� OutPut
            GetInstance()->OutPut();
        }
    };

    void OutPut()
    {
        ConsoleSaveAdapter csa;
        _OutPut(csa);  ///////////////////���ö�̬ ͬһ���� ��ͬ���� д����̨

        FileSaveAdapter fsa("PerFormanceProfilerReport.txt");
        _OutPut(fsa);  ///////////////////���ö�̬ ��ͬ���� ͬһ���� ��ͬ���� д�ļ�
    }

    void _OutPut(SaveAdapter& sa)  // �û��������  ʵ�֡���̬��
    {
        int num = 1;
        PP_MAP::iterator ppIt = _ppMap.begin();
        while (ppIt != _ppMap.end())
        {
        // error  onst PPNode& node = ppIt->first;  Ҫ��const  ��Ϊnode��undered_mapde ��key,key�ǲ������޸ĵ�
            const PPNode& node = ppIt->first;
            PPSection* section = ppIt->second;

            sa.Save("No.%d, Desc: %s\n", num++, node._desc.c_str());
            sa.Save("Filename: %s, Line: %d, Function: %s\n",
                node._filename.c_str()
                , node._line
                ,node._function.c_str());
            sa.Save("CostTime:%.2f, CallCount:%lld\n\n"
                ,(double)section->_costTime/1000/* ��*/
                ,section->_callCount);
            
            ++ppIt;
        }
    }

protected:
    PerformanceProfiler(){};
    PerformanceProfiler(const PerformanceProfiler&);
    PerformanceProfiler& operator=(const PerformanceProfiler&);
protected:
    // map<PPNode, PPSection*> +ppMap; // ͳ����Դ��Ϣ������  
    // map �ײ����� ʱ�临�Ӷ� O(logN)  
    // PP_MAP->unordered_map �ײ� �õ��� hashtable  ʱ�临�Ӷ�ΪO(1)  ����    
    // ��ʵ����  ֻ�� unordered_map ����
    PP_MAP _ppMap;
};

//PerformanceProfiler::Report report; // ������������� ������������ ��ӡ����

#define PERFORMANCE_PROFILER_EE_BEGIN(sign, desc)\
    PPSection* ps##sign = PerformanceProfiler::GetInstance()->CreatSection(__FILE__, __FUNCTION__, __LINE__ , desc);\
    ps##sign->Begin();

#define PERFORMANCE_PROFILER_EE_END(sign)\
    ps##sign->End();






void TestPP2()
{
    PerformanceProfiler::Report report; // ������������� ������������ ��ӡ����
    // ������sleep ģ�����е�ʱ��
    // network  mid   sql  ֻ�Ǻ��еı�������һ����
    PERFORMANCE_PROFILER_EE_BEGIN(network, "����");
    // ����
    Sleep(200);   // ���� <Windows.h>
    PERFORMANCE_PROFILER_EE_END(network);


    PERFORMANCE_PROFILER_EE_BEGIN(mid, "�м��߼�");
    // �м��߼�
    Sleep(300);
    PERFORMANCE_PROFILER_EE_END(mid);

    PERFORMANCE_PROFILER_EE_BEGIN(sql, "���ݿ�");
    // ���ݿ�
    Sleep(400);
    PERFORMANCE_PROFILER_EE_END(sql);
}

