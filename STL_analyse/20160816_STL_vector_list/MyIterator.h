#pragma once
// ���������ͱ�

struct InputIteratorTag {};  // ֻ��������
struct OutputIteratorTag {}; // ֻд������
struct ForwardIteratorTag : public InputIteratorTag {};     // ǰ������� 
struct BidirectionalIteratorTag : public ForwardIteratorTag {}; // ˫�������
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {}; // ������ʵ�����


template <class T, class Distance>
struct InputIterator {
	typedef InputIteratorTag IteratorCategory;
	typedef T                  ValueType;
	typedef Distance           DifferenceType;
	typedef T*                 Pointer;
	typedef T&                 Reference;
};

struct OutputIterator {
	typedef OutputIteratorTag IteratorCategory;
	typedef void                ValueType;
	typedef void                DifferenceType;
	typedef void                Pointer;
	typedef void                Reference;
};

template <class T, class Distance> 
struct ForwardIterator {
	typedef ForwardIteratorTag IteratorCategory;
	typedef T                    ValueType;
	typedef Distance             DifferenceType;
	typedef T*                   Pointer;
	typedef T&                   Reference;
};


template <class T, class Distance>
struct BidirectionalIterator {
	typedef BidirectionalIteratorTag IteratorCategory;
	typedef T                          ValueType;
	typedef Distance                   DifferenceType;
	typedef T*                         Pointer;
	typedef T&                         Reference;
};

template <class T, class Distance>
struct RandomAccessIterator {
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T                          ValueType;
	typedef Distance                   DifferenceType;
	typedef T*                         Pointer;
	typedef T&                         Reference;
};

//
// ��������Ƕ������5����Ӧ���ͱ�
// Iterator Category��Value Type��Difference Type��Pointer��Reference
// ��5����Ƕ���ͱ��壬ȷ�����ܹ�������ĸ�STL�ںϡ�
// �ҷ���Iterator Traits��������ȡ
//
//////////////////////////////////////////////////////////////////////////////
//  ValueType�������������ɵ����� ��ȡ�������е��������͡�����������������ȡ��
template<class T, class Distance>
inline T* ValueType(const InputIterator<T, Distance>&)
{
    return (T*)(0);
}
template <class T, class Distance> 
inline T* ValueType(const ForwardIterator<T, Distance>&) {
	return (T*)(0);
}

template <class T, class Distance> 
inline T* ValueType(const BidirectionalIterator<T, Distance>&) {
	return (T*)(0);
}

template <class T, class Distance> 
inline T* ValueType(const RandomAccessIterator<T, Distance>&) {
	return (T*)(0);
}

template <class T>
inline T* ValueType(const T*) { return (T*)(0); }

////////////////////////////////////////////////////////////////////////////

// ������
template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct Iterator
{
    typedef Category IteratorCategory; // ������������
    typedef T ValueType; // ��������ָ�Ķ��������
    typedef Distance DifferenceType; // ����������֮��ľ���
    typedef Pointer Pointer; // ��������ָ�������͵�ָ��
    typedef Reference Reference; //�������������͵�����
};


// Traits ��ȡ��������������Ӧ���ͱ�

template <class Iterator>
struct IteratorTraits
{
    typedef typename Iterator::IteratorCategory IteratorCategory ;
    typedef typename Iterator::ValueType ValueType; 
    typedef typename Iterator::DifferenceType DifferenceType; 
    typedef typename Iterator::Pointer Pointer; 
    typedef typename Iterator::Reference Reference;  
};

// ƫ�ػ� ԭ��ָ������
template<class T>
struct IteratorTraits<T*>
{
    typedef RandomAccessIteratorTag IteratorCategory; // ������������
    typedef T ValueType; // ��������ָ�Ķ��������
    //////////////////////////////////////////////////////////////
    typedef size_t  DifferenceType; // ����������֮��ľ���
    typedef T* Pointer; // ��������ָ�������͵�ָ��
    typedef T& Reference; //�������������͵�����
};


// ƫ�ػ� constԭ��ָ������
template<class T>
struct IteratorTraits<const T*>
{
    typedef RandomAccessIteratorTag IteratorCategory; // ������������
    typedef T ValueType; // ��������ָ�Ķ��������
    //////////////////////////////////////////////////////////////
    typedef size_t  DifferenceType; // ����������֮��ľ���
    typedef const T* Pointer; // ��������ָ�������͵�ָ��
    typedef const T& Reference; //�������������͵�����
};

// Distance ��ʵ��
// _Distance ����
template<class InputIterator>
inline typename IteratorTraits<InputIterator>::DifferenceType
_Distance(InputIterator first, InputIterator last, InputIteratorTag) // O(N)
{
    IteratorTraits<InputIterator>::DifferenceType n = 0;
    // ǰ��� Ҫһ��һ���� �� List::iterator
    while (first != last)
    {
        ++first;
        ++n;
    }
    return n;
};

template<class RandomAccessIterator>
inline typename IteratorTraits<RandomAccessIterator>::DifferenceType 
_Distance(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIteratorTag) // O(1)
{
    return last - first;// ����ĵ����� ����last �� first ��ָ��  ֱ��������� ��vector::Iterator
};


template<class InputIterator >
inline typename IteratorTraits<InputIterator>::DifferenceType
Distance(InputIterator first, InputIterator last)
{
   // return _Distance(first, last, InputIterator::IteratorCategory());
    // InputIterator::IteratorCategory()�뷨�ܺ� ���� ����Vector���� Iterator��T* �� ��֧�� ��ΪVector���� ��û��һ�� ��������õ���Iterator   ����Iteratorֻ��T*�ı����� û������ Iterator ��������Ͷ��� �� IteratorCategory ���Ա����ǲ�ͨ����
    //

    return _Distance(first, last, IteratorTraits<InputIterator>::IteratorCategory());
};




/* Advance ��ʵ��*/
template<class InputIterator, class Distance>
inline void _Advance(InputIterator &i, Distance n, InputIteratorTag)
{
    while (n--) ++i;
}

// �ػ�  ˫�������
template<class BidirectionalIterator, class Distance>
inline void _Advance(BidirectionalIterator& i, Distance n, BidirectionalIteratorTag)
{
    if (n >= 0)
        while(n--) ++i;
    else
        while (n++) --i;
}

// �ػ� ���������
template<class RandomAccessIterator, class Distance>
inline void _Advance(RandomAccessIterator& i, Distance n, RandomAccessIteratorTag)
{
    i += n;
}


template <class InputIterator, class Distance>
inline void Advance(InputIterator &i, Distance n )
{
    _Advance(i, n, IteratorTraits<InputIterator>::IteratorCategory());
}


/****************
 * ����������Ķ���  ������������������������һ���װ
******************/

template<class Iterator>
class ReverseIterator
{
public:
    // ͨ����������ȡ������ȡ������������ж���Ļ�������
    typedef typename IteratorTraits<Iterator>::IteratorCategory IteratorCategory;
    typedef typename IteratorTraits<Iterator>::ValueType ValueType;
    typedef typename IteratorTraits<Iterator>::DifferenceType DifferenceType;
    typedef typename IteratorTraits<Iterator>::Pointer Pointer;
    typedef typename IteratorTraits<Iterator>::Reference Reference;

    typedef Iterator IteratorType;
    typedef ReverseIterator<Iterator> Self;
public:
    ReverseIterator() {};
    explicit ReverseIterator(IteratorType x) // explicit ��ֹǿ������ת�� IteratorType����ֱ��ת����RecerseIterator
        :_current(x)
    {}

    Reference operator*() const
    {
        // ���������ʱ ȡ���� ��ǰλ�õ�ǰһ������
        // ��Ϊ RBegin () == End()   REnd() == Begin()
        Iterator tmp = _current;
        return *--tmp;
    }

    Pointer operator->() const
    {
        return &(operator*());
    }

    Self& operator++()
    {
        --_current;
        return *this;
    }

    Self operator++(int)
    {
        Self tmp = *this;
        --_current;
        return tmp;
    }

    Self operator--()
    {
        ++_current;
        return tmp;
    }

    Self operator--(int)
    {
        Self tmp = *this;
        ++_current;
        return tmp;
    }

    bool operator != (const Self& x)
    {
        return _current != x._current;
    }



protected:
    Iterator _current;// ֱ�Ӿ��Ƕ�����������ķ�װ
};
