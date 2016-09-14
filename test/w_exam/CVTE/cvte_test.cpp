#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
using namespace std;

// "��������ִ� �ı���"

// "abababa"   ->  �ǻ���  ֱ�ӷ���
// "ababab"    ->    ���ǻ��� ���[���]���ַ� ʹ�ó�Ϊ����   ���a���� "abababa"


string get_str(string s)
{
    int size = s.size();
    int l = 0;
    int r = size - 1;
    while (l <= r)
    {
       int l_index = l;
       int r_index = r;
       bool is = true;
       while (l_index <= r_index)
       {
           if (s[l_index] != s[r_index])
           {
              is = false;
              break;
           }
           l_index++;
           r_index--;
       }
       if (is)
       {
          while (--l >= 0)
          {
             s.insert(s.end(), s[l]);
          }
          break;
       }
       l++;
    }

    return s;
}

int main()
{
    string s = "ababab";
    cout<<get_str(s)<<endl;
    string s2 = "ababa";
    cout<<get_str(s2)<<endl;

    while(cin>>s)
    {
    cout<<get_str(s)<<endl;
    
    }
    return 0;
}