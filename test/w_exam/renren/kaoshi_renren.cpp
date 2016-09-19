#define _CRT_SECURE_NO_WARNINGS 1


//  renren
#include <iostream>
using namespace std;

// �ж�һ���ַ����ǲ��ǻ���
bool is_plalindrome(char* str, int n)
{
    if (str == NULL || n <= 0)
    {
        return false;
    }

    char* left = str + (n>>1) - 1;
    char* right = (n%2 == 0 ? left + 1 : left + 2); // ����ż
    bool is = true;
    while (left >= str)
    {
        if (*left != *right)
        {
            is = false;
            break;
        }
        left--;
        right++;
    }

    return is;
}

void test()
{
    char *s1_1 = "ababa";
    char *s1_2 = "aaaba";
    char *s2_1 = "abba";
    char *s2_2 = "abea";

    cout<<is_plalindrome(s1_1, 5)<<endl;
    cout<<is_plalindrome(s1_2, 5)<<endl;
    cout<<is_plalindrome(s2_1, 4)<<endl;
    cout<<is_plalindrome(s2_2, 4)<<endl;
}




int main()
{
    test();
    return 0;
}





/////-----------------------------------




    
#include <iostream>
using namespace std;


/*

  ���üӼ� �� �������� ��������λ����λ��� ���
  ��λ��֮�� ����һλ ��ʾ ��λ
  ����ʾ ���˽�λ����Ӧλ�ļ�
*/


int get_sum(int a,int b)
{
    int sum;
    int jinwei;
    do
    {
       sum = a^b;
       jinwei = (a&b)<<1;
       a = sum;
       b = jinwei;
    }while (jinwei != 0); // error while (jinwei > 0)

    return sum;
}


int main()
{
    cout<<get_sum(1,2)<<endl;
    cout<<get_sum(-1,-2)<<endl;

    return 0;
}




/*
          ���� 2016 C++
��һ��̨�ף�ÿ��̨������һ���Ǹ������������ڸ�̨����ʱ�������ǰ������̨�ס��ӵ�0��̨�׿�ʼ����ʵ��һ���������ж��Ƿ��ܵ������һ��̨�ס�
���磺 4 2 2 1 0 2 ���� false
            2 1 3 1 1 0 ���� true
1
2
3
bool jump(int array[], int size)
{                 
}


*/

//    �Ӻ���ǰ �õ���־λ 
#include <iostream>
using namespace std;
#include <vector>


bool jump(int array[], int size)
{       bool can = false;           
    vector<bool> is(size, false);
    is[size - 1] = true;
    for (int i = size - 2; i >= 0; i--)
    {
        for (int j =1; j <= array[i]; j++)
        {
            if (i + j <= size - 1)
            {
                if (is[i + j] == true)
                {
                    is[i] = true;
                    break;
                }
            }

        }

        if (i == 0 && is[i] == true)
        {
            can = true;
        }

    }

    return can;
}

void test_jump()
{
    int arr1[6] = {4 ,2, 2 ,1, 0, 2};
    int arr2[6] = {2 ,1 ,3 ,1 ,1 ,0};
    cout<<jump(arr1,6)<<endl;
    cout<<jump(arr2,6)<<endl;
}



int main()
{
    test_jump();
    return 0;
}

