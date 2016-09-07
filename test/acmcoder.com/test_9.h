#pragma once

/*

��·�ϵ�·��
��Ŀ����
����E����·���кܶ�·�ƣ�ÿ��������·��֮��ļ������1���С���ǳ���E���쵼��Ϊ��ʹE���и�����õķ�չ����Ҫ�ڳ���E��һ�γ���ΪM�����ɵ��ϵ�һЩ���򽨵�������Щ����Ҫ�ǽ��˵���������ҪŲ����Ӧ��·�ơ����԰ѳ���ΪM�����ɵ�����һ�����ᣬһ��������0��λ�ã���һ����M��λ�ã������ϵ�ÿ�������㶼��һ��·�ơ�Ҫ����������Щ��������������������ϵ���ʼ�����ֹ���ʾ����֪��һ�������ʼ�����ֹ������궼������������֮��������غϵĲ��֡�����Ҫ����Щ�����е�·�ƣ���������˵㴦������·�ƣ����ߡ����ܰ���С������һ�£�����Щ·�����ߺ���·�ϻ��ж���·�ƣ�
����
�����ļ��ĵ�һ������������M��1 <= M <= 10000���� N��1 <= N <= 100����M������·�ĳ��ȣ�N�����������Ŀ��M��N֮����һ���ո��������������N��ÿ�а���������ͬ����������һ���ո��������ʾһ���������ʼ�����ֹ������ꡣ
�������붼Ϊ��������M��N�ķ�ΧΪ������ʾ��Χ��
��������
500 3
100 200
150 300
360 361
���
����ļ�����һ�У���һ��ֻ����һ����������ʾ��·��ʣ��·�Ƶ���Ŀ��
�������
298

*/

#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> v;

int residue(int M, int N)
{
    int first, second;
     for (int i = 0; i < N; i++)
        {
            pair<int,int> p;
            //cin>>v[i].first>>v[i].second;
            cin>>p.first>>p.second;
            if (v.size() == 0)
            {
                //v[0] = p;
                v.insert(v.begin(), p);
                continue;
            }

            int index;
            bool is_in = false;
            for (index = 0; index < v.size(); index++)
            {
                if (p.second >= v[index].first && p.second <= v[index].second)
                {
                    is_in = true;
                    if (v[index].first > p.first)
                    {
                        v[index].first = p.first;
                    }
                   break;
                }
                else if (p.first >= v[index].first && p.first <= v[index].second)
                {
                    is_in = true;
                    if (v[index].second < p.second)
                    {
                        v[index].second = p.second;
                    }
                    break;
                }
            }

            if (!is_in)
            {
                v.insert(v.end(), p);
            }
        }

        int count = 0;
        for (int i = 0; i < v.size(); i++)
        {
            count += v[i].second - v[i].first + 1;
        }

        return M + 1 - count;

}


void test_9()
{
    int M,N;
    while (cin>>M>>N)
    {
        cout<<residue(M,N)<<endl;
    }

}
