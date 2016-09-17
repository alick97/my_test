#pragma once


/*


�������갮��ѧ

��Ŀ����
С����һ�����յĳ���Ա����ʮ���Ȱ���ѧ���˳�ȥ��˾ӦƸ��·�ϣ�С�����ڹ����Լ���ʫ���ˡ���
 
"����С����С����˧����˧��˧�ˣ�
    ����С����С���������ܰ��ɰ��ˣ�
    ����С����С��������������������"
 
����С����ʫ�衪���������ôһ�㡪�������������ҡ�������������ֻС����������
���ǣ�С���Լ����������������еġ�
 
С��������Ҫ����һ��ǡ��Ϊһ������������n��������Ҫ����������ﵽ��һ�Կɣ�����ʫ�衭��
���ṹ��m�ֳ��ȵĶ̾䣨���������ס�ʫ�衱���г���Ϊ1��7�Ķ̾䣩������ÿ�ֳ��ȵĶ̾����ķѵ�ʱ������ͬ�ġ�
���������æ���£�С��������Ҫ����ʱ�䣬���ܴ���Լ���Ŀ���أ����û�а취ʵ�֣������"It is not true!"��û�����ţ���

����
��һ��һ������n����ʾС���봴��ʫ��������ļ��ϴ�С��
������n�У����е�i��Ϊһ����a[i]����ʾ����ʫ�������a[i]���֡�
�ڶ���һ������m����ʾС�����Թ����m�ֲ�ͬ���ȶ̾�ĸ�����
������m�У����е�i��Ϊ��������b[i],c[i]������b[i]��ʾС�����Դ���������Ϊb[i]�Ķ̾䣬��Ӧ��c[i]��ʾ�������ֳ��ȶ̾������ĵ�ʱ�䡣
 
���ݱ�֤����a[]�е���������ͬ��b[]�е���������ͬ��c[]������10000.
���ݱ�֤����
����30%�Ĳ��Ե㣬n=1��1<=m<=2��1<=a[],b[]<=20��
����70%�Ĳ��Ե㣬1<=n,m<=5��1<=a[],b[]<=100;
����100%�Ĳ��Ե㣬1<=n,m<=100��1<=a[],b[]<=10000;

��������
2
7
11
2
3 1
2 100

���
���һ�У�
����а취���Ŀ�꣬�����һ����������ʾ���Ŀ����������Ҫ�Ĵ���ʱ�䡣
���û�а취���Ŀ�꣬�����"It is not true!"��û�����ţ�

�������
103

*/

/* ����˼��  ������ �������� �����ظ� �� Ϊһ�����������������   �ⷨ������쳲��������� ���������¼��� �����ظ������ʱ�临�Ӷ�*/

#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
vector<int> len,t;

const int MAX = 0x7FFFFFFF;
vector<int> keep_dp(10001); // �Ż��ݹ�

int dp(int x)
{
    if (x == 0)
    {
        return 0;
    }

    if (keep_dp[x] > 0)
    {
        return keep_dp[x];
    }
    int smin = MAX;
    for (int i = 0; i < len.size(); i++)
    {
        if (x - len[i] >= 0)
        {
            smin = min(smin, dp(x - len[i]) + t[i]);
        }
    }
    keep_dp[x] = smin;

    return smin;
}






void test_20()
{
    int n;
    while (cin>>n)
    {
        vector<int> req(n);
        for (int i = 0; i < req.size(); i++)
        {
            cin>>req[i];
        }

        int m;
        cin>>m;

        len.resize(m), t.resize(m);

        for (int i = 0; i < t.size(); i++)
        {
            cin>>len[i]>>t[i];
        }

        int smin = MAX;
        for (int i = 0; i < req.size(); i++)
        {
            smin = min(smin, dp(req[i]));
        }

        if (smin < MAX)
        {
            cout<<smin<<endl;
        }
        else
        {
            cout<<"It is not true!"<<endl;
        }


    }

}



















/*
        // ���˵ĳ��� �ο�  ������쳲��������еĵݹ� �����������¼��� �Ż����Ӷ�
#include <iostream>
#include <string.h>
#include <cstdio>
#include <vector>
using namespace std;
vector<int> len,t;
const int MAX=2000000;
vector<int> keep_dp(10001);
int dp(int x)
{
	//if(x<0)return MAX;
	if(!x)return 0;
	if(keep_dp[x]>0)return keep_dp[x];
	int smin=MAX;
	for(int i=0;i<len.size();i++)
	{
		if(x-len[i]>=0)
			smin=min(smin,dp(x-len[i])+t[i]);
	}
	keep_dp[x]=smin;
	return smin;
}

int main()
{
	#ifdef H2
		freopen("in.txt","r",stdin);
		freopen("out.txt","w",stdout);
	#endif
	int n;
	cin>>n;
	vector<int> req(n);
	for(int i=0;i<n;i++)
		cin>>req[i];
	int m;
	cin>>m;
//	len.resize(m);t.resize(n);
	len.resize(m);t.resize(m);
	for(int i=0;i<m;i++)
		cin>>len[i]>>t[i];
	int smin=MAX;
	//cout<<smin<<endl;
	for(int i=0;i<req.size();i++)
	{
		smin=min(smin,dp(req[i]));
	}
	if(smin<MAX)
		cout<<smin<<endl;
	else cout<<"It is not true!"<<endl;
    return 0 ;
}
*/



