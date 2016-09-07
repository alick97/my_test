//
//
//#pragma once 
//
//
///*********
//
// qsort ��ϰ     �ȽϺ��� *p1 - *p2  ��С������
// sort  ��ϰ     �ȽϺ��� int p1  < int p2   ��С������      �ȽϵĽṹ���operator()   Ҳ�� p1<p2  ��С����
//***************/
//
//#include<iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//#define __SIZE__ 8
//int arr[__SIZE__] = { 3,5,4,1,2,7,9,5};
//
//int compare_than(const void * p1, const void* p2)
//{
//    return *(int *)p1 - *(int*)p2;   //  ��С��������
//}
//
//int compare_less(const void * p1, const void* p2)
//{
//    return *(int *)p2 - *(int*)p1;   //  �Ӵ�С����
//}
//void Print()
//{
//    for (int i = 0; i < __SIZE__; ++i)
//    {
//        cout<<arr[i];
//    }
//    cout<<endl;
//}
//
//
//void test_qsort()         
//{
//   // qsort(arr,8,sizeof(int),compare_than); // 12345579
//    qsort(arr,8,sizeof(int),compare_less); // 97554321
//    Print();
//}
//
//
//vector<int> v(arr, arr + sizeof(arr)/sizeof(int));
//
//void print_v()
//{
//    for (int i = 0; i < __SIZE__; i++)
//    {
//        cout<<v[i];
//    }
//    cout<<endl;
//
//}
//
//bool fun_than(const int& a, const int& b)
//{
//    return a > b;       // �Ӵ�С����
//}
//
//struct than
//{
//    bool operator()(const int& a, const int& b)
//    {
//        return a < b;     // ��С��������
//    }
//
//};
//
//
//void test_sort()
//{
//    
//    
//    //12345579
//  // sort(v.begin(), v.end());
//  // print_v();
//
//    // 97554321 
//   //sort(v.begin(), v.end(), fun_than);
//   sort(v.begin(), v.end(), than());
//    print_v();
//}
//

/********
���������¹���

��Ŀ����
����ѧһЩ���ӻ������������ʱ����ʦ������������Ʋ��ұ������һ������������ʱҲ��������windowsϵͳ�Դ��ļ�������ۺ͹���ȥ��ƣ�����������ʦҪ�������һ�����¹��ܵļ�������ʵ�ֵ�����һ����ʱ���ܹ���������ֽ��һ�����������ӳ˻�����ʽ�����������ӵĴ�С������ʾ��������ҶԼ����������ı�ʾӦ�ú�����ġ�������ʾ����0 �� 9��ʮ�����ֵı�ʾ��ʽ��ÿ�����ֶ�ռ��5 * 3��С���ַ�����

����ʵ������¹��������Կ��ɣ�
����
�����ж���������ݣ�ÿ�����һ��������n��1 < n <= 1000000)��
��������
10
2
���
����ÿ�����������ֽ�����ɸ������˻�����ʽ��������С�����˳�������������֮���á� * ������ʽ���ӡ�
�������
 -     -
  |   |
 -  *  -
|       |
 -     -
 
 -
  |
 -
|
 -




******************/

#pragma once 

#include <iostream>
using namespace std;
#include <vector>
#include <string>
vector<int> v;

void get_prime_v(int n)
{
    v.clear();
    int prime = 2;
    while (n >= prime)
    {
        if (prime == n)
        {
            v.insert(v.end(), prime);
            break;
        }
        else if (n % prime == 0)
         {
             n /= prime;
             v.insert(v.end(), prime);
        }
        else
        {
            prime++;
        }
    }
}



    string line1[10] = {" - ", "   ", " - ", " - ", "   ", " - ", " - ", " - ", " - ", " - "};
    string line2[10] = {"| |", "  |", "  |", "  |", "| |", "|  ", "|  ", "  |", "| |", "| |"};
    string line3[10] = {"   ", "   ", " - ", " - ", " _ ", " - ", " - ", "   ", " - ", " - "};
    string line4[10] = {"| |", "  |", "|  ", "  |", "  |", "  |", "| |", "  |", "| |", "  |"};
    string line5[10] = {" - ", "   ", " - ", " - ", "   ", " - ", " - ", "   ", " - ", " - "};

    string get_string_num(int n)
    {
        string s;
        while (n > 0)
        {
            char tmp = n % 10;
            n /= 10;
            s.insert(s.begin(), tmp + '0');
        }
        return s;
    }

void print_calcuate(int n)
{
    get_prime_v(n);

    /*
    
     -     -
      |   |
     -  *  -
    |       |
     -     -
    
    **/
  
   
     string s;
            for (int j = 0; j < v.size(); j++)
            {
                s = get_string_num(v[j]);
                for (int index = 0; index < s.size(); index++)
                {
                    cout<<line1[s[index] - '0'];
                }
                cout<<" ";
            }
            cout<<endl;
            for (int j = 0; j < v.size(); j++)
            {
                s = get_string_num(v[j]);
                for (int index = 0; index < s.size(); index++)
                {
                    cout<<line2[s[index] - '0'];
                }
                cout<<" ";
            }
            cout<<endl;
            for (int j = 0; j < v.size(); j++)
            {
                s = get_string_num(v[j]);
                for (int index = 0; index < s.size(); index++)
                {
                    cout<<line3[s[index] - '0'];
                }
                if (j != v.size() - 1)
                cout<<"*";
            }
            cout<<endl;
            for (int j = 0; j < v.size(); j++)
            {
                s = get_string_num(v[j]);
                for (int index = 0; index < s.size(); index++)
                {
                    cout<<line4[s[index] - '0'];
                }
                cout<<" ";
            }
            cout<<endl;
            for (int j = 0; j < v.size(); j++)
            {
                s = get_string_num(v[j]);
                for (int index = 0; index < s.size(); index++)
                {
                    cout<<line5[s[index] - '0'];
                }
                cout<<" ";
            }
            cout<<endl;

        

    


}


void test_5()
{
    int n;
    while (cin>>n)
    {
        print_calcuate(n);
    }

}
