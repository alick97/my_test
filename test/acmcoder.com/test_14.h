

#pragma once

/*


�ȴ�С���ַ����ֵ����� ȫ���С�
��Ŀ����
������"abcdefghijkl��12���ַ����������е������а��ֵ������У���������һ�����У�˵��������������е��������ǵڼ�С�ģ�
����
��һ����һ������n��0��n��=10000��;
�����n�У�ÿ����һ�����У�
��������
3
abcdefghijkl
hgebkflacdji
gfkedhjblcia
���
���һ������m��ռһ�У�m��ʾ�����ǵڼ�λ��
�������
1
302715242
260726926

*/

//  Ч��̫��
//   *****************************  ������ַ������������� ������ �����ֵ������
/*
#include <iostream>
using namespace std;
#include <string>

 int str_count  = 0;

bool get_index(char *str, int size,int index ,char* desc)
{
    if (index == size - 1)
    {
        str_count++;
        if (strcmp(str, desc) == 0)
        {
           return true;
        }
        else
        {
           return false;
        }
    }
   bool ret = false;
     for (int i = index; i < size; i++ )
     {
        //swap(str[index], str[i]);
         // ����һλ    abcd     adbc    
         //              ^ ^      ^  
         char tmp = str[i];  // d
         int j = i;
         for (; j > index; j--)
         {
             str[j] = str[j-1];
         }
         str[j] = tmp;
        ret = get_index(str ,size, index + 1, desc);
        if (ret)
        {
          return ret;
        }
        //swap(str[index], str[i]);
        // ����һλ ��ԭ
        //        adbc     abcd
        //         ^          ^
        tmp = str[index];
        for (j = index; j < i; j++)
        {
            str[j] = str[j+1];
        }
        str[j] = tmp;
     }
     return false;
}
string s[100];
void test_14()
{
   
  //  string desc = "abc";
    int n;
    while (cin>>n)
    {
       for (int i = 0; i < n; i++)
       {
          cin>>s[i];
       }

       for (int i = 0; i < n; i++)
       {
           string desc = "abcdefghijkl";
           str_count = 0;
           get_index(const_cast<char*>(desc.c_str()), s[i].size(), 0, const_cast<char*>(s[i].c_str()));
           cout<<str_count<<endl;
       }
    }
   
}
*/

#include <iostream>
using namespace std;
#include <string>
int get_index(string s)
{
     //  12
     int count = 0;
     bool is[256] = {false};
     for (int i = 0; i < s.size() - 1; i++)
     {
         int n = s.size() - i - 1;
         int quan_c = 1;// ȫ����
         while (n > 1)
         {
             quan_c *= n--;
         }
       
         char c = s[i];
         int less_c = 0;
         for (int i = c - 1; i >= 'a'; i--)
         {
            if (!is[(unsigned int)i])
            {
                less_c++;
            }
         }
         is[(unsigned int)c] = true;
             count += less_c * quan_c;
     }
      return count + 1;
}

string s[100];
void test_14()
{
   
  //  string desc = "abc";
    int n;
    while (cin>>n)
    {
       for (int i = 0; i < n; i++)
       {
          cin>>s[i];
       }

       for (int i = 0; i < n; i++)
       {
           cout<<get_index(s[i])<<endl;
       }
    }
   
}