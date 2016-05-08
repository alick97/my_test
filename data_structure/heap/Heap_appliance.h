#pragma once
#include <assert.h>
#include <time.h>
//�ѵ�Ӧ��
// 1
// ��������ݡ�N���� ����һ�ε����ڴ� �����ļ��� ��ǰn�������
// �ⷨ���Ƚ�n�����ݵ� ��С�ѡ�   ��ʣ�µ�����ÿ��������pushһ�� Ȼ���ٴ�����ÿ��popһ��  ���
// ʣ�µ�n�� ����ǰn�������     ��С���ص� �Ѷ���С ÿ�ΰ���С�ĵ��� �������µ� ���Ǵ�ġ�
// ʱ�临�Ӷ� Nlog2 n     ��Ϊ log2 n ��N���̫С ���� ԼΪ N  



// 2
// 10000���� ����������ǰ100�û�   ����չ �������ݴ���
const int N = 10000;
const int k = 100;

void _ajustDown(int a[], int size,int parent)
{
	assert(a && size >= 0);

	int child = parent * 2 + 1;

	while (child < size)
	{
		if (child + 1 < size && a[child + 1] < a[child]) // С��
		{
			child++;
		}

		if (a[child] < a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else 
		{
			break;
		}
	}
}


void GetTopK(int a[],int topk[],int k)	// topk ���շ��ص�����k��Ԫ��
{
	assert(a && k >= 0);
	//int topk[k];
	// ���� ǰk������
	for (int i = 0; i < k; i++)
	{
		topk[i] = a[i];
	}

	// ��С��
	for (int i = (k - 2)/2; i > 0; --i)
	{
		_ajustDown(topk, k, i);	// ���µ���
	}

	// С�Ѷ����� ʣ�µ�����

	for (int i = k; i < N; i++)
	{
		if (a[i] > a[0])
		{
			topk[0] = a[i];
			_ajustDown(topk, k, 0);
		}
		else
		{
			continue;
		}	
	}
}


void test_topk()
{
	int a[N], topk[k];

	srand(time(0));

	for (int i = 0; i < k; i++)
	{
		a[i] = rand() % N;
	}

	for (int i = k; i < N; i++)
	{
		a[i] = N + i;
	}

	GetTopK(a,topk,k);

	cout<<topk[0]<<endl;
}


//3
// ������
// heap.hpp ��