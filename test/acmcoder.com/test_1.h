#pragma once
#include <iostream>
using namespace std;

/*

    ��Ŀ����
    �й�����
    �У�С�����ǣ�
    �������ܵļ��㣬С������һ֧��Ʊ����֪���������Ʊ�����쿪ʼ����Ʊ�������±仯����һ�첻�䣬�Ժ���һ�죬��һ�죬�����죬��һ�죬�����죬��һ��...�������ơ�
    Ϊ������㣬����ÿ���Ǻ͵���Ϊ1����Ʊ��ʼ����ҲΪ1����������Ʊ�ĵ�n��ÿ�ɹ�Ʊֵ����Ǯ��
    ����
    ��������������ݣ�
    ÿ������һ��n��1<=n<=10^9 ��
    ��������
    1
    2
    3
    4
    5
    ���
    �������ÿ�ɹ�Ʊ����Ǯ������ÿ�����ݣ����һ�С�
    �������
    1
    2
    1
    2
    3

*/
#include <vector>

// ���ݶ� �ڴ泬��  acmcoder.com����ͨ����50% 
//vector<int> v;
//int getmoney(int n)
//{
//    int money = 0;
//    int index = 0;
//    v.resize(100);
//    v[index++] = 1;
//    int prev = 1;
//    int tag = 1;
//  while (index != n)
//  {
//      if (tag > 0)
//      {
//          v[index++] = 1;
//          tag--;
//      }
//      else
//      {
//          v[index++] = -1;
//          prev = prev + 1;
//          tag = prev;
//      }
//  }
//  for (int i = 0; i < n; i++)
//  {
//      money += v[i];
//  }
//
//
//    return money;
//
//}


int getmoney(int n)
{
    int money = 1;
    int i = 1;
    int count = 1;

    for (i = 2; ; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (j !=i)
            {
                money += 1;
            }
            else
            {
                money--;
            }
            count++;
            if (count == n)
            {
                return money;
            }

        }

    }

    return 1;

}


void test_1()
{
    int n;
    while (cin>>n)
    {
        cout<<getmoney(n)<<endl;
    }

}
