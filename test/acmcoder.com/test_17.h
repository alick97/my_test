#pragma once

/*

���Ĵ�
��Ŀ����
����һ���ַ��������Ƿ��ܹ�ͨ�����һ����ĸ�����ɡ����Ĵ����� �����Ĵ�����ָ���źͷ��Ŷ���һ�����ַ������磺��aa��,��bob��,��testset���ǻ��Ĵ�����alice��,��time�������ǻ��Ĵ���
����
һ��һ����Сд��ĸ���ɵ��ַ������ַ������Ȳ�����10��

��������
coco

���
��������ַ�������ͨ�����һ���ַ����������YES�������������NO����

�������
YES


*/
#include <iostream>
#include <string>
using namespace std;
bool is_palindrome(const char* left, const char *right)
{
    
    bool is = true;
    while (left <= right)
    {
        if (*left != *right)
        {
            is = false;
            break;
            
        }
        left++;
            right--;
    }
    return is;
}

bool get_all(const string& s)
{
    const char* left = s.c_str();
    const char* right = s.c_str() + s.size() - 1;
    bool is_1 = true;
    bool is_2 = true;
    while (left <= right)
    {
        if (*left != *right)
        {
            is_1 = is_palindrome(left+1, right);
            is_2 = is_palindrome(left,right -1);
            break;
        }
        left++;
        right--;
    }
    if (is_1 || is_2 )
    {
        return true;
    }
    else
    {
        return false;
    }

}


void test_is_palindrome()
{
    string t;
    while (cin>>t)
    {
        if(get_all(t))
        {
            cout<<"YES"<<endl;
        }
        else
        {
            cout<<"NO"<<endl;
        }


    }

}
