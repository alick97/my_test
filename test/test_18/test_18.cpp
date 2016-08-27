#include <iostream>
using namespace std;



//////////////////////////////////////////////////////////////
// ʵ��һ��ֻ�ڡ��ѡ������ɵĶ���
//////////////////////////////////////////////////////////////


class B
{
public:
    static B* GetObj()
    {
        return new B;
    }
    ~B()
    {
        cout<<"~B()"<<endl;
    }

protected:
    B(){};
    
    B(const B&); // ----------------------��������ҲҪ��ֹ �� ����ֹ�������� B* pb = B::GetObj(); B b2(*pb);�ǳɹ���  �� ��b2����ջ�ϵġ�
};

void testB()
{
   // error  B b;
   // error B* pb = new B;
   //error B b(B());
    B* pb = B::GetObj();
    //B b2(*pb);  һ��ҪB(const B&);Ϊprotected
 
    delete pb;
}









///////////////////////////////////////////////////////////////
// ʵ��һ��ֻ�ڡ�ջ�������ɵĶ���
///////////////////////////////////////////////////////////////


// ����һ A() A��constA&��;����Ϊprotected ���� &(A())
// ��ȱ��  ���ܷ�ֹ��������ȫ�ֵĶ��� ȫ�ֵ�ʵ�ֵķ�ʽ��ͬ
// �� A* pa = new AA;  pa��ȫ�ֵ� ���ǳɹ��ģ������Ҳ��� vs2012�ǲ��е� ȫ�ֵ�Ҳ�ǲ��еģ�
class A
{
public:
    static A* GetA()
    {
        return &(A());
    }

    ~A()
    {
        cout<<"~A()"<<endl;
    }
    int a;
protected:
    A(){};    // ���ﲻ�ܹ����� �� A();    ��Ȼ���� �Ҳ������ӵ��ⲿ����
    A(const A& a);// �򵥴ֱ� ���������� ��������protected  ��A* paa = new A(*pa);�ǿ���ִ�е� ���ɵ��Ƕ��ϵ�
    
};
 // vs2012  error  A* pa = new A; ����vs2013����

void test1()
{

   //error  A a;
   // error  A* pa = new A;
    A* pa = A::GetA();
    pa->a = 2;
    cout<<pa->a<<endl;

   // error  A* paa = new A(*pa);
}


// ������ �� ��
// new ��ʵ�����ȵ��� operator new(size_t) �� operator new[](size_t) Ȼ�������Ӧ�Ĺ��캯��
// operator new ������ һ���Ǿֲ���  ���еľ�̬����   һ����ȫ�ֵ�  ������� ������ȫ�ֵ�����õ���ȫ�ֵ�operator new
// ���������ֹnew   ���Խ����е�operator new����Ϊprotected��
class C
{
public:
    void CSay()
    {
        cout<<"I am c"<<endl;
    }
    int val;
    C()
    {
        cout<<"C()"<<endl;
    }

protected:
    void* operator new(size_t);
    void operator delete(void*);

    void* operator new[](size_t);
    void operator delete[](void*);
};

// error C* pc = new C();

void testC()
{
   //error  C* pc = new C;

   //error C* pc =(C*)malloc(sizeof(C));
  //  new (pc) C;

    /* ok   ��ֹ�������� Ҫ��ֹ��Ҫ�񷽰�һһ�������캯����������
    C* pc = (C*)malloc(sizeof(C));
    pc->CSay();
    pc->val = 1;
    cout<<pc->val<<endl;
    
    C* pc = (C*)malloc(sizeof(C));
    pc->C::C();
    */
    C c;

}

// ����3  ǰ���ַ����Ľ��
class E
{
public:
    static E* GetE()
    {
        return &(E());
    }  
protected:
    E(){};
    E(const E& objE){};
protected:
    void* operator new(size_t);
    void operator delete(void*);

    void* operator new[](size_t);
    void operator delete[](void*);
};
void testE()
{
    //error E* pe = new E();
    E* pe = E::GetE();
}


// ��֤ ���õ���ȫ�ֵ�operator  ���� ���оֲ���
// ����ȫ�ֵ�operator new
// �ο�url :      http://blog.csdn.net/qq_29227939/article/details/51638241
void * operator new(size_t size)
{
cout << "ȫ���ڴ����"<<endl;
return malloc(size);
}

int *pa = new int; // ����ȫ�ֵ�operator new

class FF
{};

FF* pff = new FF; // ���õ���ȫ�ֵ�operator new

class GG
{
public:
    void * operator new(size_t size)
{
cout << "�ֲ��ڴ����"<<endl;
return malloc(size);
}

};

GG* pgg1 = new GG;  // ���þֲ�    �ֲ�ʵ�ֵ��õ��Ǿֲ��� ����ֲ�ûʵ�ֵ��õ���ȫ�ֵ�
void testgg()
{
    GG* pgg2 = new GG; // ���õ��Ǿֲ���   ����ֲ�ûʵ�ֵ��õ���ȫ�ֵ� ����testgg���޹�ϵ
}



int main()
{
   // test1();
    testB();
   // testC();
    //testE();
   // testgg();
    return 0;
}


