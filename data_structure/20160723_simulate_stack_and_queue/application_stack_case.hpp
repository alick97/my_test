/*

1.ʵ��һ��ջ��Ҫ��ʵ��Push����ջ����Pop����ջ����Min��������Сֵ�Ĳ�������ʱ�临�Ӷ�ΪO(1)

*/

#include "MyStack.hpp"
template<class T>
class StackInO1: public Stack<T>
{
public:
    void Push(const T& x)
    {
       Stack<T>::Push(x);

       if (minStack.Empty())
       {
           minStack.Push(x);
       }
       else
       {
           if (minStack.Top() > x)
           {
               minStack.Push(x);
           }
           else
           {
               minStack.Push(minStack.Top());
           }
       } 
    }

    void Pop()
    {
        Stack<T>::Pop();
        minStack.Pop();
    }

    T& FindMin()
    {
        assert(!minStack.Empty());
        return minStack.Top();
    }

protected:
    Stack minStack;
};

void test_StackInO1()
{
	StackInO1<int> s1;
	int min;
	s1.Push(4);
	s1.Push(3);
	s1.Push(2);
	s1.Push(1);

	min = s1.FindMin();
	
	s1.Pop();
	min = s1.FindMin();

	s1.Pop();
	min = s1.FindMin();
	
	s1.Pop();
	min = s1.FindMin();
	
	/*s1.Pop();
	min = s1.FindMin();*/
}