#pragma once



/*

����¥�������

��Ŀ����
С����һ�����ǵĳ���Ա�����Ļ�����Ҫ����������¥���ٶ��ر��( > c < )��
С���ļ�ס�ڵ�n�㣬������ѡ��ӵ�����¥������ֻ��С��һ���˻��õ��ݣ�������¥����¥��
��ǰ����ͣ�ڵ�m�㣬������ӵ����µ���1�㣬��Ҫ�������ȵ�����һ��->����->����->�����ٵ����һ��->���ţ����Ŀ���ʱ��ҲҪ�������ڣ���
 
���ڸ����㡪��
С���ļ���¥��n����ǰ����ͣ�ڵ�¥��m��
�Լ�����ÿ����һ��¥��ʱ��t1������ʱ��t2������ʱ��t3������С��ÿ��һ��¥��ʱ��t4��
�����С������һ�£�����쵽���1���ʱ�䡣

����
��һ����������n��m������n��ʾС�����ڵ�¥�㣬m��ʾ��ǰ����ͣ�ڵ�¥�㣬
�ڶ����ĸ�������t1��t2��t3��t4������t1��ʾ����ÿ����һ��¥��ʱ�䣬t2��ʾ����ʱ�䣬t3��ʾ����ʱ�䣬t4��ʾС��ÿ��һ��¥��ʱ�䡣
 
���ݱ�֤����
����80%�Ĳ��Ե㣬1<=n,m<=10��1<=t1,t2,t3,t4<=100
����100%�Ĳ��Ե㣬1<=n,m<=100000��1<=t1,t2,t3,t4<=100000

��������
5 10
1 5 5 4

���
���һ�У�����һ����������ʾС����쵽���1���ʱ�䡣

�������
16

*/

#include <iostream>
using namespace std;
#include <math.h>

long long get_fastpath(long long n, long long m, long long t1, long long t2, long long  t3, long long t4)
{
    long long time_lift ;
    long long time_walk =  (n - 1) * t4;
    long long time_lift2 ;//= 2*t1*t4*(n-m)/(t4 + t1) + 2*t2 + t3;
    if (n < m)
    {
           time_lift = (m - 1)*t1 + 2*t2 +t3 ;
    }
    else
    {
        long long t,d;
        t = n;
        d = m;
          long long s = t1 + t4;
          long long dis = n - m;
        while (s <= dis)
        {
            t--;
            d++;
            s += t1 + t4;
        }
        d += dis - (s -t1 -t4);
         time_lift = (d - m)*t1 + (d - 1)*t1 + 2*t2 +t3 ;
    }

   
    return time_lift < time_walk ? time_lift : time_walk;
   
}


void test_16()
{
    long long n,m,t1,t2,t3,t4;
    while (cin>>n>>m>>t1>>t2>>t3>>t4)
    {
        cout<<get_fastpath( n, m, t1, t2,  t3, t4)<<endl;
    }

    
}
