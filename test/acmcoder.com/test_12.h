#pragma once

#include <iostream>
using namespace std;


/*

�������˿�
��Ŀ����
һ������������n��վ�㣬�˿ʹ�ǰ���ϳ����Ӻ����³���
����ͳ�����ڵ�i��վ���³�����a[i]���Լ��ϳ�����b[i]��
�ʹ���������ʱ��������ж��ٳ˿�
����
��һ�ж���һ������n(1<=n<=100)����ʾ��n��վ��
������n�У�ÿ��������ֵ���ֱ��ʾ�ڵ�i��վ���³��������ϳ�����
��������
4
0 3
2 5
4 2
4 0
���
ÿ������������ĳ˿���Ŀ
�������
6

*/

int get_max_people(int (*p)[2], int n)
{
    int max = 0;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        count += p[i][1] - p[i][0];
        if (max < count)
        {max = count;}
    }

    return max;
}

void test_get_max_people()
{
    int arr[100][2];
    int n;
    while (cin>>n)
    {
       for (int i = 0; i < n; i++)
       {
          cin>>arr[i][0]>>arr[i][1];
       }
       cout<<get_max_people(arr, n)<<endl;
    }
}



