#pragma once
#include <iostream>
using namespace std;
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

    T _data;    //  �������
    __ListNode<T>* _prev; // ָ��ǰһ������ָ��
    __ListNode<T>* _next; // ָ���һ������ָ��
};


// List �� ������
template<class  T, class Ref, class Ptr>
struct __ListIterator 
{
  typedef __ListIterator<T, Ref, Ptr> Self;
  typedef __ListIterator<T, T&, T*>            Iterator;
  typedef __ListIterator<T, const T&, const T*> ConstIterator;
  typedef T ValueType; // ֵ
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

  Reference  operator*()
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
        return _node;
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



	List()
	{
		_head = new ListNode;

		_head->_next = _head;
		_head->_prev = _head;
	}

	

    //.................����........................

	void PushBack(const T& x)
	{
		ListNode* tail = _head->_prev;

		ListNode* tmp = new ListNode(x);
		tail->_next = tmp;
		tmp->_prev = tail;

		_head->_prev = tmp;
		tmp->_next = _head;
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
