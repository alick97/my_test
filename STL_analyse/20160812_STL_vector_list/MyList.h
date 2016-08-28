#pragma once
#include "MyIterator.h"
/************
 * ģ��ʵ�� �򻯰�List ������
 * 
****************/

template<class T>
struct __ListNode
{
     __ListNode()
        :_next(NULL)
        ,_prev(NULL)
    {}

    __ListNode(const T& x)
        :_data(x)
        ,_next(NULL)
        ,_prev(NULL)
    {}


    __ListNode<T>* _prev; // ָ��ǰһ������ָ��
    __ListNode<T>* _next; // ָ���һ������ָ��
        T _data;    //  �������
};


// List �� ������
template<class  T, class Ref, class Ptr>
struct __ListIterator 
{
    /////////////////////////////// 
     typedef ForwardIteratorTag IteratorCategory; // ������������
    typedef T ValueType; // ��������ָ�Ķ��������
    typedef size_t DifferenceType; // ����������֮��ľ���
      typedef T ValueType; // ֵ
    ///////////////////////////////


  typedef __ListIterator<T, Ref, Ptr> Self;
  typedef __ListIterator<T, T&, T*>            Iterator;
  typedef __ListIterator<T, const T&, const T*> ConstIterator;

  typedef Ptr Pointer; // ָ��
  typedef Ref Reference; // ����
  typedef __ListNode<T>* LinkType;

  LinkType _node;

  __ListIterator(LinkType x) : _node(x) {}
  __ListIterator() {}
  //__ListIterator(const Iterator& x) : _node(x._node) {}

  bool operator==(const Self& x) const
  {
      return _node == x._node;
  }


  bool operator!=(const Self& x) const
  {
      return _node != x._node;
  }

  Reference  operator*() const
 //error  T& operator*()
  {
      return (*_node)._data;
  }

  Pointer operator->() const
  {
      return &(operator*()); 
  }

  Self& operator++()
  {
      _node = _node->_next;
      return *this;
  }

  Self operator++(int)
  {
      Self tmp = *this;
      _node = _node->_next;
      return tmp;
  }

  Self& operator--()
  {
        _node = _node->_prev;
        return *this;
  }

  Self operator--(int)
  {
      Self tmp = *this;
      _node = _node->_prev;
      return tmp;
  }

  


};







template<class T>
class List
{
public:
	typedef __ListNode<T> ListNode;
	typedef __ListIterator<T, T&, T*> Iterator;
	typedef __ListIterator<T, const T&, const T*> ConstIterator;

    typedef ReverseIterator<Iterator> ReverseIterator;

	List()
	{
		_head = new ListNode;

		_head->_next = _head;
		_head->_prev = _head;
	}



    //.................����........................

    // pos ǰ��һ��λ�ò���һ�����
    void Insert(Iterator pos, const T& x)
    {
        ListNode* cur = pos._node;
        ListNode* prev = cur->_prev;

        ListNode* tmp = new ListNode(x);

        prev->_next = tmp;
        tmp->_prev = prev;

        tmp->_next = cur;
        cur->_prev = tmp;
    }

    


	void PushBack(const T& x)
	{
		/*ListNode* tail = _head->_prev;

		ListNode* tmp = new ListNode(x);
		tail->_next = tmp;
		tmp->_prev = tail;

		_head->_prev = tmp;
		tmp->_next = _head;*/
        Insert(End(), x);
	}

    void PushFront(const T& x)
    {
        Insert(Begin(), x);
    }


    Iterator Begin()
    {
        return Iterator(_head->_next);
    }

    Iterator End()
    {
        return Iterator(_head);
    }

    ConstIterator Begin() const
    {
        return ConstIterator(_head->_next);
    }


    ConstIterator End() const
    {
        return _head; // ******�Զ� ��ʽת�� ����ǿת  ���ù��캯��
    }

    ReverseIterator RBegin()
  {
      return ReverseIterator(End());
  }

  ReverseIterator REnd()
  {
      return ReverseIterator(Begin());
  }


    Iterator Erase(Iterator pos)
    {
        assert(pos != End());

        ListNode* next = pos._node->_next;
        ListNode* prev = pos._node->_prev;

        prev->_next = next;
        next->_prev = prev;

        delete pos._node;
        return Iterator(next);
    }

    void PopBack()
    {
        Erase(--End());
    }

    void PopFront()
    {
        Erase(Begin());
    }



protected:
	ListNode* _head;
};



/*   ����1  lΪ��const �ɹ�
void PrintList( List<int>& l)
{
	List<int>::Iterator it = l.Begin();
	while (it != l.End())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}
*/

/* ����2     lΪconst   

* ���벻ͨ��  
* ����	1	error C2662: ��List<T>::Begin��: ���ܽ���this��ָ��ӡ�const List<T>��ת��Ϊ��List<T> &��	
* ԭ�� �� ��Щ��Ա������ConstIterator Begin() const         ConstIterator End() const�� ����û��const ���� 
    l ��const�� ����ֻ�ܵ���const �ķ��� 

*/
/*
void PrintList(const List<int>& l)
{
	List<int>::ConstIterator it = l.Begin();
	while (it != l.End())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}
*/


/********
 * ����3    
 * ����  ��Ȼ ConstIterator  it
 * ���� T& operator*���� ���Ի��ǿ����޸�*it��ֵ��
 * T& operator*()   ������ Ӧ���� Reference  operator*()
 * :ConstIterator��Reference ��Ӧ const T&
**********/
void PrintList(const List<int>& l)
{
     List<int>::ConstIterator it = l.Begin();
	while (it != l.End())
	{
		//*it = 10;
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}
void test_iterator()
{
    List<int> l;
    for (int i = 0; i < 5; i++)
    {
        l.PushBack(i);
    }

    PrintList(l);

}

struct A
{
    int value1;
    int value2;
};

void test_list()
{
    List<int> l;
    l.PushBack(1);
    l.PushBack(2);
    l.PushBack(3);
    l.PushBack(4);



    PrintList(l);

    l.PopFront();
    l.PopBack();
    PrintList(l);
    List<int>::Iterator it = l.Begin();
    while (it != l.End())
    {
        *it = 10;
        cout<<*it<<" ";
        ++it;
    }
    cout<<endl;

    List<A> la;
    la.PushBack(A());

    List<A>::Iterator ita = la.Begin();

    while (ita != la.End())
    {
        (*ita).value1 = 10;
        (*ita).value2 = 11;
        cout<<(*ita).value1<<" "<<(*ita).value2<<" ";
        ++ita;
    }

    ita = la.Begin();
    ita->value1 = 45;
    ita->value2 = 55;
    cout<<(*ita).value1<<" "<<(*ita).value2<<" ";


}



void test_list_reverseIterator()
{
    List<int> l;
    l.PushBack(1);
    l.PushBack(2);
    l.PushBack(3);
    l.PushBack(4);
    PrintList(l);


    List<int>::ReverseIterator rIt = l.RBegin();
    while (rIt != l.REnd())
    {
        cout<<*rIt<<endl;
        ++rIt;
    }

    cout<<endl;
}

