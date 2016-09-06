#pragma once 


/*********

 qsort ��ϰ     �ȽϺ��� *p1 - *p2  ��С������
 sort  ��ϰ     �ȽϺ��� int p1  < int p2   ��С������      �ȽϵĽṹ���operator()   Ҳ�� p1<p2  ��С����
***************/

#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define __SIZE__ 8
int arr[__SIZE__] = { 3,5,4,1,2,7,9,5};

int compare_than(const void * p1, const void* p2)
{
    return *(int *)p1 - *(int*)p2;   //  ��С��������
}

int compare_less(const void * p1, const void* p2)
{
    return *(int *)p2 - *(int*)p1;   //  �Ӵ�С����
}
void Print()
{
    for (int i = 0; i < __SIZE__; ++i)
    {
        cout<<arr[i];
    }
    cout<<endl;
}


void test_qsort()         
{
   // qsort(arr,8,sizeof(int),compare_than); // 12345579
    qsort(arr,8,sizeof(int),compare_less); // 97554321
    Print();
}


vector<int> v(arr, arr + sizeof(arr)/sizeof(int));

void print_v()
{
    for (int i = 0; i < __SIZE__; i++)
    {
        cout<<v[i];
    }
    cout<<endl;

}

bool fun_than(const int& a, const int& b)
{
    return a > b;       // �Ӵ�С����
}

struct than
{
    bool operator()(const int& a, const int& b)
    {
        return a < b;     // ��С��������
    }

};


void test_sort()
{
    
    
    //12345579
  // sort(v.begin(), v.end());
  // print_v();

    // 97554321 
   //sort(v.begin(), v.end(), fun_than);
   sort(v.begin(), v.end(), than());
    print_v();
}

