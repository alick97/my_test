#pragma once

#include"TypeTraits.h"

// ������ͷŵ�������
template <class T>
inline void Destroy(T* pointer)
{
	pointer->~T();
}

template <class T1, class T2>
inline void Construct(T1* p, const T2& value)
{
	new(p)T1(value);// new �Ķ�ַ���� ���Ѿ����ٵĿռ��� ���ÿ������졢����
}

// �ͷ�һ���������  ForwardIterator������
template <class ForwardIterator>
inline void 
__DestroyAux(ForwardIterator first, ForwardIterator last, __FalseType) // __FalseType ���� �޹�ʹ�������� �� string
{
	for ( ; first < last; ++first)
		Destroy(&*first);// ���õ����� �ҵ�����ĵ�ַ
}

template <class ForwardIterator> 
inline void
__DestroyAux(ForwardIterator, ForwardIterator, __TrueType) {} // __TrueType �� �޹�ʹ�������� �� int char...

template <class ForwardIterator, class T>
inline void
__Destroy(ForwardIterator first, ForwardIterator last, T*)// T*������Ҫ�� �ص��� ��ȡT���� ͨ��ValueType��ȡT*
{
	typedef typename __TypeTraits<T>::HasTrivialDestructor TrivialDestructor; // ������ȡ
	__DestroyAux(first, last, TrivialDestructor());
}

template <class ForwardIterator>
inline void Destroy(ForwardIterator first, ForwardIterator last)
{
	__Destroy(first, last, ValueType(first));
}

inline void Destroy(char*, char*){}
inline void Destroy(wchar_t*, wchar_t*){}