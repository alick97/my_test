#pragma once

#include <iostream>
using namespace std;



/*****

��Ŀ����
��԰���ж�ƻ����N��1��N��9��ֻ�����֡���һֻ�ܰ����ƻ��ƽ����ΪN�ݣ�����һ�������Ѷ��һ�����ˣ�������һ�ݡ��ڶ�ֻ�ܰ�ʣ�µ�ƻ����ƽ���ֳ�N�ݣ��ֶ���һ������ͬ���Ѷ��һ�����ˣ�������һ�ݣ�����������ֱ����Nֻ�ܶ�����ô���ģ��ʹ�԰��ԭ��[����]�ж��ٸ�ƻ����

����
����1����������ʾ�ܵĸ���������ֵ����1����С��9��
��������
5
���
Ϊ1�����֣���ʾ��԰��ԭ���е�ƻ��������
�������
3121



url  :     http://www.nowcoder.com/question/next?pid=734817&qid=26021&tid=4831062

**********/




//  ���
int get_num(int n)
{
    int count;
    int bear;
    for (int i = n + 1; ; i++)
    {
       count = i;
       bear = n;
       while (count % n == 1)
       {
           count = count - count / n - 1;
           bear--;
       }

       if (bear == 0)
       {
           return i;
       }
    }

    return -1;
}

void test_8()
{
    int n;
    while (cin>>n)
    {
        cout<<get_num(n)<<endl;
    }

}

