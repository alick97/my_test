#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

/******
 * 1 һ��������ֻ��һ��������һ�� �������ɶԳ��� �ҳ������
 * ���������
 ****************/

int findValue_1(const int arr[], int length)
{
    assert(NULL != arr && length > 0);

    int ret = 0;
    for (int i = 0; i < length; i++)
    {
        ret ^= arr[i];
    }

    return ret;
}

void test_findValue_1()
{
    int arr[] = {1,2,2,3,3,4,4};
    int value = findValue_1(arr, 7);
}

/************
 * 2 һ�������У����������ֳ�����һ�Σ��������ֶ��ǳɶԳ��֣����ҳ����������֡�
 * ���������
 ****************/
void  findValue_2(const int arr[], int length)
{
    assert(NULL != arr && length > 0);
    int value1 = 0;
    int value2 = 0;

    // ����value1 �� value2ֵ��ͬ �������п϶���һλ��ͬ ������һλ�����ݷֳ�����
    // ���������
    int ex = 0;
    for (int i = 0; i < length; i++)
    {
        ex ^= arr[i];
    }

    unsigned int index = 0;

    // 11100 & 11011 == 11000    11100 ^ 11000 == 00100
    index ^= ex & (ex - 1);//(�����Դ��������һ����ͬ��λ)

    // ���� �ҵ�value1 �� value2 ��index����

    for (int i = 0; i < length; i++)
    {
        if (index == (arr[i] & index))
        {
            value1 ^= arr[i];
        }
        else
        {
            value2 ^= arr[i];
        }
    }


    cout<<"value1:"<<value1<<endl;
    cout<<"value2:"<<value2<<endl;

}


void test_findValue_2()
{
    int arr[] = {1,2,33,33,44,44,55,55,-1,-1};
    findValue_2(arr, 10);
}

/************
 * 3 һ�������У����������ֳ�����һ�Σ��������ֶ��ǳɶԳ��֣����ҳ������������е�һ�����֡�
 * ���������
 ****************/






int main()
{
    //test_findValue_1();
    test_findValue_2();
    return 0;
}



