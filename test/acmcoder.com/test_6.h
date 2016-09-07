#pragma once

/*

��̨��
��Ŀ����
��һ¥�ݹ�m�����տ�ʼʱ���ڵ�һ������ÿ��ֻ�ܿ���һ���������Ҫ���ϵ�m�������ж����߷���
ע���涨��һ����һ����0���߷���
����
�����������Ȱ���һ������n(1<=n<=100)����ʾ����ʵ���ĸ�����Ȼ����n�����ݣ�ÿ�а���һ������m����1<=m<=40), ��ʾ¥�ݵļ�����
��������
2
2
3
���
����ÿ������ʵ�����������ͬ�߷���������
�������
1
2


*/

#include <iostream>
using namespace std;

int get_method(int n)
{
    if (n == 1)
    {
        return 0;
    }

    if (n == 2)
    {
        return 1;
    }
    if (n == 3)
    {
        return 2;
    }
    int method_count = 0;
    int prev1 = 1;
    int prev2 = 2;
    for (int i = 4; i <= n; i++)
    {     
        method_count = prev1 + prev2;
        prev1 = prev2;
        prev2 = method_count;
    }

    return method_count;
}

void test_6()
{
    int n;
    while (cin>>n)
    {
      int t;
      for (int i = 0; i < n; i++)
      {
      cin>>t;
         cout<<get_method(t)<<endl;
      }
       
    }

}
