#define _CRT_SECURE_NO_WARNINGS 1

/*

    ������ܺ�
    ʱ�����ƣ�C/C++���� 2000MS���������� 4000MS
    �ڴ����ƣ�C/C++���� 65536KB���������� 589824KB
    ��Ŀ������
    ������������2��ż��֮��ľ��룬Ϊ��������֮�������ĸ�������С��������n������2��ż�����������������֮�������ܺͣ�Ӧ����n*(n-1)/2�����룬����ܺ;ͺ�)��
    ����
    ��һ��������ż���ĸ�������СΪ2�������ܵ�����֮��ÿ��Ϊһ��ż������С��4���������Ǽ����򣬲��ظ����������С�
    ���
    �������������������ܺͣ���Ӧ����һ����С��0��������

    ��������
    3
    4
    6
    12
    �������
    6


    */



#include<algorithm>

#include<iostream>
#include <vector>
using namespace std;

bool is_zhishu(int num)
{
  
    for (int i = 2; i <= num/2; i++)
    {
         if (num % i == 0)
         {
          return false;
         }
    }
    return true;
}

int get_geshu(int n1, int n2)
{
     int count = 0;
     for (int i = n1; i <= n2; i++)
     {
         if (is_zhishu(i))
         {count++;}
     }
     return count;
}

int main()
{
    int n;
    int tmp;
    while(cin>>n)
    {
        int count = 0;
         vector<int> v;
        for (int i = 0; i < n; i++)
        {
           cin>>tmp;
           v.insert(v.end(), tmp);
        }
        // GET ����
        vector<int> pri;
        for (int i = v[0]; i <= *(--v.end()); i++)
        {
             if (is_zhishu(i))
             {
                pri.insert(pri.end(), i);
             }
        }

        vector<int> pri_count;
        pri_count.resize(v.size() - 1);
        int prev = 0;
        for (int i = 1; i < v.size(); i++)
        {
              for (int j = prev; j < pri.size(); j++)
              {
                 if (pri[j] < v[i])
                 {
                  pri_count[i - 1]++;
                 }
                 else
                 {
                    prev = j;
                    break;
                 }
              }
        }
        //    4         6        12     14
        //         5         7\11    13  
        //         1         2         1               (1+2)+(1+2+1)+(2 + 1)    +1 + 2 + 3 = 14
        for (int i = 0; i < pri_count.size(); i++)
        {
           for (int j = i + 1; j < pri_count.size(); j++)
           {
               //count +=( pri_count[i] + pri_count[j]);
               for (int k = i; k <= j; k++)
               {
                   count += pri_count[k];
               }
           }
           count += pri_count[i];
        }


         cout<<count<<endl;
    }
    return 0;
}



/*

һ���ַ�����������ǰ׺����
ʱ�����ƣ�C/C++���� 1000MS���������� 3000MS
�ڴ����ƣ�C/C++���� 65536KB���������� 589824KB
��Ŀ������
��һ���ַ�����������ǰ׺���ȡ�������ָ���������������һ�����ַ��������硰abcdcba������һ�����ġ�
����
һ���ı��ļ������ٰ���һ���ֽڡ�ÿ���ֽ���һ���ַ�����󳤶ȿ����м�ʮ���ֽڡ�
���
������ǰ׺�ĳ��ȡ�

��������
sogou
�������
1


*/
///////////////////////////////  �����⣿����  //////////////////////////////////////
//
//#include<string>
//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//
//
//int get_count(string s)
//{
//    int s_size = s.size();
//    string rev_str = s.assign(s, s_size/2 + 1, s_size);
//    string fas_str = s.assign(s, 0, s_size/2);
//    reverse(rev_str.begin(), rev_str.end());
//    
// 
//    int count = 0;
//    for (int i = 0; i < s_size/2; i++)
//    {
//        for (int j = 0; j < s_size/2 - i; j++)
//        {
//             string s_tmp(s.c_str() + i + j);
//            size_t f = rev_str.find(s_tmp);
//            if (f != string::npos)
//            {
//                count++;
//            }
//        }
//        
//    }
//    return count;
//}
//
//int main()
//{
//    string s;
//    while (cin>>s)
//    {
//       cout<<(get_count(s)+1)/2<<endl;
//    }
//   return 0;
//}
