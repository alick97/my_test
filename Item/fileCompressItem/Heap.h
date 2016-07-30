#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
/**
 *  ��
 
 *
 *
 *
 *
 ***/

#include<iostream>
#include<vector>
#include <assert.h>
#include"HuffmanTree.h"
using namespace std;

template<class T>
struct Less
{
    bool operator()(const T& l, const T& r)
    {
        return l < r;
    }
};

// �ػ� T*
template<class T>
struct Less<T*>
{
    bool operator()(const T* l, const T* r)
    {
        return *l < *r;
    }
};

template<class T>
struct Greater
{
    bool operator()(const T& l, const T& r)
    {
        return l > r;
    }
};

template<class T, template<class> class Continer = Greater> //  Ĭ�ϴ��
class Heap
{
public:
    Heap(){};
    Heap(const T* a, int size);
    void Push(const T& x);
    void Pop();

	T& GetTop();
	bool Empty();
	size_t Size();
	void HeapSort(int size);

	void PrintHeap();
protected:
    void _AdjustDown(int parent);    //  ���µ���
	void _AdjustDown(int parent, int size);
    void _AdjustUp(int child);   //  ���ϵ���
protected:
    vector<T> _a;
    Continer<T> _com;
};

template<class T, template<class> class Continer>
Heap<T, Continer>::Heap(const T* a, int size)
{
    assert(a);

    for (int i = 0; i < size; i++)
    {
        _a.push_back(a[i]);
    }

    //  ����
    for (int i = (_a.size() - 2) / 2; i > 0; i--)  
        //  _a.size()-1 Ϊ�±꣨��0��ʼ��   �ҵ�һ����Ҷ�ӽ��   Ҷ�ӽڵ㿴�ɶ�  ������Ҷ�ӽ�� ÿ��������µ���
    {
        _AdjustDown(i); //  ���µ���
    }
    _AdjustDown(0);
}

template<class T, template<class> class Continer>
void Heap<T, Continer>::_AdjustDown(int parent)
{
    int child = parent * 2 + 1;  //  ����
    int size = _a.size();

    while (child < size)    //  ��ֹԽ��
    {
        if (child + 1 < size && _com(_a[child + 1], _a[child]))
        {
            ++child;    //  ���Һ��� ���Һ��Ӵ�������
        }

        if (_com(_a[child], _a[parent]))
        {
            swap(_a[parent], _a[child]);
            //  ����
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            //  ��Ϊ�������źõĶ�
            break;
        }
    }
}



template<class T, template<class> class Continer>
void Heap<T,Continer>::Push(const T& x)
{
	_a.push_back(x);
	_AdjustUp(_a.size() - 1);
}


template<class T, template<class> class Continer>
void Heap<T, Continer>::_AdjustUp(int child)
{
	size_t parent = (child - 1) / 2;

	while (child > 0)	//	�п� ��Ҫ��parent >= 0 �ж� ��Ϊsize_t  parent=��0-1��/2 Ϊ�Ƚϴ������ �� int��parentҲ������ѭ�� ��_com �Ƚ���>=������ʱ 
	{
			if (_com(_a[child], _a[parent]))
		{
			swap(_a[child], _a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

template<class T, template<class> class Continer>
void Heap<T,Continer>::Pop()
{
	assert(!_a.empty());
	size_t size = _a.size();
	swap(_a[0],_a[size - 1]);	//	������ ���һ������ ���������һЩ
	_a.pop_back();
	_AdjustDown(0);
}

template<class T, template<class> class Continer>
T& Heap<T,Continer>::GetTop()
{
	assert(_a.size() > 0);
	return _a[0];
}

template<class T, template<class> class Continer>
bool Heap<T,Continer>::Empty()
{
	return (_a.size() == 0);
}

template<class T, template<class> class Continer>
size_t Heap<T,Continer>::Size()
{
	return _a.size();
}

template<class T, template<class> class Continer>
void Heap<T,Continer>::HeapSort(int size)	//	������
{
	// ����ѣ�����һ���Ǵ��  ÿ�ΰѶѶ��ŵ����棩
	for (int parent = (size - 2) / 2; parent >= 0; --parent)
	{
		_AdjustDown(parent);
	}

	while(size > 1)
	{
		swap(_a[0], _a[size-1]); // ���ķź���
		_AdjustDown(0, --size); // ���Ժ���һ�� �Ѵ�С��һ��
	}
}

template<class T, template<class> class Continer>
void Heap<T,Continer>::_AdjustDown(int parent, int size)
{
	int child = parent * 2 + 1;
	while (child < size)
	{
		//	��������Ǵ�� ���Բ��÷º���
		if (child + 1 < size && _a[child + 1] > _a[child])
		{
			child++;
		}

		if (_a[child] > _a[parent])
		{
			swap(_a[child], _a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}


template<class T, template<class> class Continer>
void Heap<T,Continer>::PrintHeap()
{
	int size = Size();
	for (int i = 0; i < size; i++)
	{
		cout<<_a[i]<<" ";
	}
	cout<<endl;
}



void test_heap_creat()
{
    int array[] = {10, 16, 18, 12, 11, 13, 15, 17, 14, 19};
    size_t size = sizeof(array)/ sizeof(array[0]);
   // Heap<int, Greater> h(array, size);
	// Heap<int> h(array, size);
	Heap<int, Less> h(array, size);
	 h.Push(88);
	 h.Pop();
}

void test_heap_other()
{
	int array[] = {10, 16, 18, 12, 11, 13, 15, 17, 14, 19};
    size_t size = sizeof(array)/ sizeof(array[0]);
    Heap<int, Greater> h(array, size);
	h.PrintHeap();
	cout<<h.GetTop()<<endl;
	cout<<h.Size()<<endl;
	cout<<h.Empty()<<endl;
	h.HeapSort(10);
	h.PrintHeap();
}
	



