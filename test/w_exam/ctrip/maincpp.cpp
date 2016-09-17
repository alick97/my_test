#define _CRT_SECURE_NO_WARNINGS 1




// <algorithm>
#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;


/*

��Ʊ����
ʱ�����ƣ�C/C++���� 1000MS���������� 3000MS
�ڴ����ƣ�C/C++���� 65536KB���������� 589824KB
��Ŀ������
����һ�������д洢��һ����Ʊ����һ�콻�״����ڸ�ʱ���Ĺ�Ʊ�۸�����������ֻ����һ�������һ�����������ṩһ���㷨�������ͨ��������������Եõ����������
����
�۸����У���,�Ÿ���
���
���Ŀ�������

��������
2,3,2,4
�������
2


*/
#include <string>
vector<int> v;
int get_max(vector<int> v)
{
    int max = 0;
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = i + 1; j < v.size(); j++)
        {
            if (v[j] - v[i] > max)
            {
                max = v[j] - v[i];
            }
        }
    }

    return max;
}

void test_max()
{
    string s;
    while (cin>>s)
    {
        v.clear();
        const char* cur = s.c_str();
        for (int i = 0; i < s.size(); i++)
        {

            if (s[i] == ',')
            {
                s[i] == '\0';
                v.insert(v.end(), atoi(cur));
                cur = &s[i+1];
            }

        }
        v.insert(v.end(), atoi(cur));

        cout<<get_max(v)<<endl;
    }

}


int main()
{
    test_max();
    return 0;
}




#include <iostream>
using namespace std;

/*
���ֲ���
ʱ�����ƣ�C/C++���� 1000MS���������� 3000MS
�ڴ����ƣ�C/C++���� 65536KB���������� 589824KB
��Ŀ������
��дһ�����ֲ����㷨����һ�������ȳ��ֵ�index����������ڼ�������Ҫ����(-1)-��ǰ��Ӧ�ó��ֵ�λ�á����� [1,3,6],����5,5Ӧ������index=2��λ�õ������ڼ����С�����(-1)-2 = -3��
����
��һ�ж���һ������x����ʾҪ���ҵ������ڶ��ж���һ��������n����ʾ�����������Ԫ�ظ����������ж���n���������������ɴ����ҵ����顣
���
����x�������г��ֵ�����λ��(������0��ʼ����)����������ڣ�����(-1)-��ǰ��Ӧ�ó��ֵ�λ�á�

��������
3
5
0 1 3 5 6
�������
2

*/
int arr[1000];
int b_find(int n, int x, int arr[])
{
    int left = 0;
    int right = n - 1;
    int index = 0;
    while (left <= right)
    {
        int mid = left + (right - left)/2;
        if (arr[mid] < x)
        {
            left = mid + 1;
            index = left;
        }
        else if (arr[mid] > x)
        {
            right = mid - 1;
            index = mid;
        }
        else
        {
            return mid;
        }
    }
    return (-1 - index);
}

int main()
{
    int x;
    int n;
    while (cin>>x)
    {
        cin>>n;
        for (int i = 0; i < n; i++)
        {
            cin>>arr[i];
        }
        cout<<b_find(n,x,arr)<<endl;
    }
    return 0;
}






/*
    
�������·������
ʱ�����ƣ�C/C++���� 1000MS���������� 3000MS
�ڴ����ƣ�C/C++���� 65536KB���������� 589824KB
��Ŀ������
���罵�ٵ���ĸ������˿��̹������Ҫ�����������������ٶ���������������ıʿ�Ƿ׷��ײ߹滮·�ߡ���Ϊ����ıʿ֮һ����Ľ�ߵ��㣬����ð�մ�Խ��21���ͽ����������Ѱ������·�ߡ������һ�γ��򣬶�ȡ��������֮��ľ��룬�������ڽӾ����ʾ����������������������·�����ȡ�
����
��һ�У���������������Ϊn
����n���ǹ��Ҽ������ڽӾ����ʾ
���
�������������·������

��������
4
0,1,2,3
1,0,4,5
2,4,0,2
3,5,2,0
�������
5

*/