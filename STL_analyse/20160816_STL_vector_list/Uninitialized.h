#pragma once
// vs2012  copy出错解决
// 属性-> c\c++ -> 预处理器 -> 预处理器定义 里添加
// _SCL_SECURE_NO_WARNINGS 编译成功
#include "Typetraits.h"
#include "MyIterator.h"
#include "Construct.h"
#include <string.h>


//拷贝一段未初始化的数据
template<class InputIterator, class ForwardIterator>
inline ForwardIterator 
__UninitializedCopyAux(InputIterator first, InputIterator last,
						 ForwardIterator result, __TrueType)
{
	// 这里实际是调用的C++库里的copy
	// 内部要通过模板推演出数据的类型，再调用memcpy
	return copy(first, last, result);
}

//拷贝一段初始化的数据
template<class InputIterator, class ForwardIterator>
inline ForwardIterator __UninitalizedCopyAux(InputIterator first, InputIterator last, ForwardIterator result, __FalseType)
{
    ForwardIterator cur = result;
    try
    {
        for (; first != last; ++first, ++cur)
            Construct(&*cur, *first);
    }
    catch(...)
    {
        Destroy(result, cur);
        throw;
    }

    return cur;
}

template <class InputIterator, class ForwardIterator, class T>
inline ForwardIterator
__UninitializedCopy(InputIterator first, InputIterator last,
					ForwardIterator result, T*)
{
	return __UninitializedCopyAux(first, last, result, __TypeTraits<T>::IsPODType());
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator
UninitializedCopy(InputIterator first, InputIterator last, ForwardIterator result)
{
	return __UninitializedCopy(first, last, result, ValueType(result));
}

// 特化
inline char* 
UninitializedCopy(const char* first, const char* last, char* result)
{
	memmove(result, first, last - first);
	return result + (last - first);
}

inline wchar_t*
UninitializedCopy(const wchar_t* first, const wchar_t* last, wchar_t* result)
{
	memmove(result, first, sizeof(wchar_t) * (last - first));
	return result + (last - first);
}