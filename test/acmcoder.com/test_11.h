

#pragma once

#include <iostream>
using namespace std;


/*

Լ��
��Ŀ����
Bob��Alice�и�Լ�ᣬһ����Bob�ʹӵ�(0,0)������ǰ��Լ��ص�(a,b)��Bobû��һ�㷽��У������ÿ�ζ�����������������ĸ�������һ���������֮�����Bob��ǰ��(x,y)����ô��һ�����п��ܵ���(x+1,y), (x-1,y), (x,y+1), (x,y-1)������Ȼ����������Ŀ�ĵص�ʱ���Ѿ������ˣ�Alice������ȥ���ڶ��죬Alice����BobΪʲô�������ӣ�Bob˵�����컨��s��������Լ��ص㡣Alice����Bob�ǲ���˵���ˡ����ܷ������֤һ�£�
����
������������a,b,s (-109
��������
5 5 11
���
�����Yes�������Bob������s������(a,b)�����������No��������Ҫ������š�
�������
No

*/


#include <iostream>
using namespace std;


/*

Լ��
��Ŀ����
Bob��Alice�и�Լ�ᣬһ����Bob�ʹӵ�(0,0)������ǰ��Լ��ص�(a,b)��Bobû��һ�㷽��У������ÿ�ζ�����������������ĸ�������һ���������֮�����Bob��ǰ��(x,y)����ô��һ�����п��ܵ���(x+1,y), (x-1,y), (x,y+1), (x,y-1)������Ȼ����������Ŀ�ĵص�ʱ���Ѿ������ˣ�Alice������ȥ���ڶ��죬Alice����BobΪʲô�������ӣ�Bob˵�����컨��s��������Լ��ص㡣Alice����Bob�ǲ���˵���ˡ����ܷ������֤һ�£�
����
������������a,b,s (-109
��������
5 5 11
���
�����Yes�������Bob������s������(a,b)�����������No��������Ҫ������š�
�������
No

*/
#include<cmath>
bool isBobReal(int a, int b, int s)
{
   int len = abs(a) + abs(b);
   if (s >= len && ((s - len) & 0x1 )== 0)
   {
   return true;
   }
   else
   {
   return false;
   }
}

void test_isBobReal()
{
    int a, b, s;
    while (cin>>a>>b>>s)
    {
       if (isBobReal(a, b, s))
           cout<<"Yes"<<endl;
       else
           cout<<"No"<<endl;
    }

}