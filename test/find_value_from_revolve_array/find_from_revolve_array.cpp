#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
/**
 * �����������ת����45679123 ���ҵ�����6��λ��
 * ������� ������ת
 * ���ֲ���˼��
 * ʱ�临�Ӷ�С��O(N)
 * {7,8,9,10,1,2,3,4,5,6}
 *************/

int find_revolve_array(const int arr[], int len, int value)
{
	if (NULL == arr || len < 0)
	{
		throw exception("Invalid input");
		return 0;
	}

	int left = 0;
	int right = len - 1;
	int mid = -1;

	while (left <= right)
	{
		mid = (left - right) / 2 + right; // ��Ҫ�� left / 2 + right / 2   ��Ϊ(5 + 7)/2 = 6  �� (5/2 + 7/2) = 5

		if (arr[mid] == value)
		{
			return mid;
		}
		else if (value < arr[mid]) 
		{
			if (value >= arr[left]) // �����
			{
				right = mid -1;
			}
			else // ���ұ�
			{
				left = mid + 1;	
			}
		}
		else
		{
			if (value <= arr[right])
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
	}

	return -1;
}

void test()
{
	int arr[] = {7,8,9,10,1,2,3,4,5,6};
	int index = find_revolve_array(arr, 10, 7);
}

int main()
{
	test();
	return 0;
}
