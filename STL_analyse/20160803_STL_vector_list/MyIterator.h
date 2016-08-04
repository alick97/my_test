#pragma once

// ���������ͱ�

struct InputIteratorTag {};  // ֻ��������
struct OutputIteratorTag {}; // ֻд������
struct ForwardIteratorTag : public InputIteratorTag {};     // ǰ������� 
struct BidirectionalIteratorTag : public ForwardIteratorTag {}; // ˫�������
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {}; // ������ʵ�����


// ������
template <class Category, class T, class Distance = int, class Pointer = T*, class Reference = T&>
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
//inline typename IteratorTraits<InputIterator>::DifferenceType
inline size_t _Distance(InputIterator first, InputIterator last, InputIteratorTag) // O(N)
{
    IteratorTraits<InputIterator>::DifferenceType n = 0;
    while (first != last)
    {
        ++first;
        ++n;
    }
    return n;
};

template<class InputIterator>
//inline typename IteratorTraits<InputIterator>::DifferenceType
inline size_t _Distance(InputIterator first, InputIterator last, RandomAccessIteratorTag) // O(1)
{
    IteratorTraits<InputIterator>::DifferenceType n = 0;
    /*while (first != last)
    {
        ++first;
        ++n;
    }*/
    return last - first;
};

//inline typename IteratorTraits<RandomAccessIterator>::DifferenceType
template<class InputIterator >
inline size_t Distance(InputIterator first, InputIterator last)
{
   // return _Distance(first, last, InputIterator::IteratorCategory());
    // InputIterator::IteratorCategory()�뷨�ܺ� ���� ����Vector���� Iterator��T* �� ��֧�� ��ΪVector���� ��û��һ�� ��������õ���Iterator   ����Iteratorֻ��T*�ı����� û������ Iterator ��������Ͷ��� �� IteratorCategory ���Ա����ǲ�ͨ����
    //

    return _Distance(first, last, IteratorTraits<InputIterator>::IteratorCategory());
};

//void test()
//{
//    List<int> l1;
//    l1.PushBack(1);
//    l1.PushBack(2);
//    l1.PushBack(3);
//    l1.PushBack(4);
//    cout<<"List Distance"<<Distance(l1.Begin(), l1.End())<<endl;
//
//
//    Vector<int> v1;
//    v1.PushBack(1);
//    v1.PushBack(2);
//    v1.PushBack(3);
//    v1.PushBack(4);
//    cout<<"Vector Distance"<<Distance(v1.Begin(), v1.End())<<endl;
//}


