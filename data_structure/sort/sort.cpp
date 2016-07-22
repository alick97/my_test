#define _CRT_SECURE_NO_WARNINGS 1
#include "sort.h"
#include <iostream>
#include <assert.h>
using namespace std;

// ֱ�Ӳ�������
void InsertSort(int*arr, int size)
{
    assert(arr && size > 0);

    for (int i = 0 ; i < size; i++)
    {
        int tmp = arr[i];
        int end = i - 1;

        while (end >= 0 && arr[end] > tmp)
        {
            arr[end + 1] = arr[end];
            end--;
        }

        arr[end + 1] = tmp;

    }

}

void test_InsertSort()
{
     int arr[10] = {2,5,4,9,3,6,8,7,1,0};
     InsertSort(arr, 10);
}


//2 ϣ������
// 2 5 4 9 3 6 8 7 1 0
// 2     9     8     0
//   5     3     7
//     4     6     1

void ShellSort(int* arr, int length)
{
    assert(arr && length);

    int gap = length;
    while (gap > 1)
    {
        gap = gap /3 + 1;

        for (int i = 0; i < length - gap; i++)
        {
            int end = i;
            int tmp = arr[i + gap];

            while (end >= 0 && arr[end] > tmp)
            {
                arr[end + gap] = arr[end];
                end -= gap;
            }

            arr[end + gap] = tmp;

        }

    }

}

void test_ShellSort()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
    ShellSort(arr, 10);
}



//3 ѡ������

void SelectSort(int* arr, int size)
{
    assert(arr && size > 0);

    for (int i = 0; i < size; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }

        swap(arr[i], arr[min]);

    }

}

void test_SelectSort()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
    SelectSort(arr, 10);
}



//4 ������
// ���µ���
void _AdjustDown(int* arr, int parent, int size) 
{
    int child = parent * 2 + 1;

    while (child < size)
    {
        if (child + 1 < size && arr[child + 1] > arr[child])
        {
            child++;
        }

        if (arr[child] > arr[parent])
        {
            swap(arr[child], arr[parent]);
            parent = child;
            child = parent* 2 + 1;
        }
        else
        {
            break;
        }
    }

}

void HeapSort(int* arr, int size)
{
    assert(arr && size > 0);

    // �����
    for (int i = (size - 1 -1)/2; i >= 0; i--)
    {
        _AdjustDown(arr, i, size);
    }

    while (size > 1)
    {
        swap(arr[0], arr[size - 1]);
        _AdjustDown(arr, 0, --size);
    }
}

void test_HeapSort()
{
     int arr[10] = {2,5,4,9,3,6,8,7,1,0};
     HeapSort(arr, 10);
}



// 5 ð������
void BubbleSort(int* arr, int size)
{
    assert(arr && size > 0);

    for (int i = 0; i < size; i++)
    {
        bool isOrder = true;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                isOrder = false;
            }
        }

        if (isOrder)
        {
            break;
        }
    }
}

void test_BubbleSort()
{
        int arr[10] = {2,5,4,9,3,6,8,7,1,0};
         BubbleSort(arr, 10);
}



// ��������
// [begin , end] һ�λ���
int Partition(int* arr, int begin, int end)
{
    assert(arr);
    int tmp = end;
    int left = begin;
    int right = end - 1;

    while (left < right)
    {
        while (left < right && arr[left] < arr[tmp])
        {
            left++;
        }

        while (left < right && arr[right] > arr[tmp])
        {
            right--;
        }

        swap(arr[left], arr[right]);
    }

    if (arr[left] > arr[tmp])
    {
        swap(arr[left], arr[tmp]);
        return left;
    }

    return tmp;

}

// ������ �ڿӷ�
// [begin end]
int Partition_2(int* arr, int begin, int end)
{
    assert(arr);
    int key = arr[end];

    while (begin < end)
    {
        while (begin < end && arr[begin] <= key)
        {
            begin++;
        }

        arr[end] = arr[begin];

        while (begin < end && arr[end] >= key)
        {
            end--;
        }

        arr[begin] = arr[end];
    }

    arr[end] = key;
    return end;
}

// ������ prev��cur��
// ��ǰ���ֲ�ͬ ������right������ ͬʱҲ�ʺϡ���������
// [begin end]
int Partition_3(int* arr, int begin, int end)
{
    assert(arr);
    int cur = begin;
    int prev= cur -1;
    int key = arr[end]; // ����������ȡ�з��Ż���

    while (cur < end)
    {
        if (arr[cur] < key && ++prev != cur)
        {
            swap(arr[cur], arr[prev]);
        }
        ++cur;
    }

    swap(arr[++prev], arr[end]);

    return prev;
}


void _QuickSort(int * arr, int begin, int end)
{
    assert(arr);

    if (begin < end)
    {
        //int index = Partition(arr, begin, end);
       // int index = Partition_2(arr, begin, end); // �ڿӷ�
        // int index = Partition_3(arr, begin, end); //  prev��cur��
         int index = Partition_OP(arr, begin, end);
        _QuickSort(arr, begin, index -1);
        _QuickSort(arr, index+ 1, end);
    }

}


void QuickSort(int* arr, int size)
{
    assert(arr && size > 0);

    _QuickSort(arr, 0 , size - 1);
}

void test_QuickSort()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
    QuickSort(arr, 10);
}


// �����Ż�
// 1 ����ȡ�з�
// 2 �����䳤�Ƚ�Сʱ ʹ�ñ������ ��ֱ�Ӳ������� ���ٵݹ����

// ���Ż�1 ����ȡ�з� ��ֹ�Ѿ��ź���� ��Ϊ�������O(N^2)��
int GetMid(int* arr,int left, int mid, int right)
{
    assert(arr);
    if (arr[left] < arr[mid])
    {
        if (arr[right] < arr[left])
        {
            return left;
        }
        else if (arr[right] > arr[mid])
        {
            return mid;
        }
        else
        {
            return right;
        }
    }
    else // mid < left
    {
        if (arr[right] < arr[mid])
        {
            return mid;
        }
        else if (arr[right] > arr[left])
        {
            return left;
        }
        else
        {
            return right;
        }
    }
}

int Partition_OP(int* arr, int begin, int end)
{
    assert(arr);
    int cur = begin;
    int prev = cur -1;

    // �Ż� 1 ����ȡ�з�
    int mid = GetMid(arr, begin, begin + (end - begin)/ 2, end);
    int key = arr[mid];
    swap(arr[mid], arr[end]);
    while (cur < end)
    {
        if (arr[cur] < key && ++prev != cur)
        {
            swap(arr[cur], arr[prev]);
        }

        ++cur;

    }

    swap(arr[++prev], arr[end]);
    return prev;
}

void _QuickSort_OP(int* arr, int begin, int end)
{
    assert(arr);
    // ���Ż�2  �����䳤�Ƚ�Сʱ ʹ�ñ������ ��ֱ�Ӳ������� ���ٵݹ������
    if (begin >= end)
    {
        return ;
    }

    if (end - begin <= 10)
    {
        // ����ֱ�Ӳ�������
        InsertSort(arr + begin, end - begin + 1); 
    }
    else
    {
        //int index = Partition(arr, begin, end);
       //  int index = Partition_2(arr, begin, end); // �ڿӷ�
        int index = Partition_3(arr, begin, end); //  prev��cur��
        _QuickSort_OP(arr, begin, index - 1);
        _QuickSort_OP(arr, index + 1, end);
    }
}

void QuickSort_OP(int* arr, int size)
{
    assert(NULL != arr && size > 0);

    _QuickSort_OP(arr, 0, size - 1);
}

#include<Windows.h>
#include<time.h>
void test_QuickSort_OP()
{
    srand(time(0));
  
    int* arr = new int[100];

    for (int i = 0; i < 100; i++)
    {
        arr[i] = rand();
    }

    unsigned  int start_time = GetTickCount();
    QuickSort_OP(arr, 100);
    unsigned int end_time = GetTickCount();
    cout<<"time:"<<(end_time-start_time)<<endl;

    for (int i = 0; i < 100; i++)
    {
        cout<<arr[i]<<endl;
    }

    delete[] arr;
}


// ���� ���ǵݹ顿 ����stack
#include<stack>
void _QuickSort_NRe(int* arr, int left, int right)
{
    assert(arr);
    stack<int> s;
    s.push(left);
    s.push(right);

    while (!s.empty())
    {
        int end = s.top();
        s.pop();

        int start = s.top();
        s.pop();

        int div = Partition(arr, start, end);

        if (start < div -1)
        {
            s.push(start);
            s.push(div - 1);
        }
        
        if (div + 1 < end)
        {
            s.push(div + 1);
            s.push(end);
        }


    }

}


void test_QuickSort_NRe()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
    _QuickSort_NRe(arr,0, 10 - 1);
}

// �鲢����
// 63    95  |  84    46 |  18   24 |  27  31 |  46
// 63    95  |  46    84 |  18   24 |  27  31 |  46
// 46 63 84 95           |     18 24 27 31 | 46
//           18 24 27 31 46 63 84 95       |   46
//                    18 24 27 31 46 46 63 84 95
// [left ,right]

// �ϲ���ǰ�� ������ ����
void Merge(int* arr, int* tmp, int left,int mid, int right) // �ϲ�
{
    assert(arr && tmp);
    int i = left;
    int index = mid + 1;// �ڶ���
    int begin = left;// ��һ��

    while (begin <= mid && index <= right)
    {
        if (arr[begin] > arr[index])
        {
            tmp[i++] = arr[index++];
        }
        else
        {
            tmp[i++] = arr[begin++];
        }
    }

    //����ʣ��һ��Ĳ��� ��������whileִֻ��һ��

    while (begin <= mid)
    {
        tmp[i++] = arr[begin++];
    }

    while (index <= right)
    {
        tmp[i++] = arr[index++];
    }


    for (int j = 0; j <= right; j++)
    {
        arr[j] = tmp[j];
    }
}

void _mergeSort(int* arr,int* tmp, int left, int right)
{
    assert(arr && tmp);
    if (left < right)
    {
        int mid = left + (right - left)/2;
        // ʹ���� С���� ����
        _mergeSort(arr, tmp, left, mid);
        _mergeSort(arr, tmp, mid + 1, right);
        // ���������������� �ϲ�
        Merge(arr, tmp, left, mid, right); // �ϲ�
    }
}

void MergeSort(int* arr, int n)
{
    assert(NULL != arr && n > 0);
    int* tmp = new int[n]; // ��ʱ�ռ� ����źõ��м���
    _mergeSort(arr, tmp, 0, n - 1);

    delete[] tmp;
}

void test_MergeSort()
{
    int arr[] = {63  ,  95  , 84  ,  46 ,  18 ,  24 ,  27 , 31 ,  46};
    MergeSort(arr, 9);
}


// ��������
// 1  �� ֪����Χ 0-99  �ù�ϣֱ�Ӷ�ַ��
// 2 �緶Χ100000-200000    ���ȥ100000 �����±�ӳ��
void CountSort(int* arr, int size)
{
    const int count = 100;
    int* tmp = new int[count];
    memset(tmp, 0, sizeof(int) * count);

    for (int i = 0; i < size; i++)
    {
        tmp[arr[i]] += 1;
    }

    int index = 0;
    for (int i = 0; i < count; i++)
    {
        while (tmp[i] > 0)
        {
            arr[index++] = i;
            tmp[i]--;
        }
    }
}

void test_CountSort()
{
    int arr[10] = {2,5,4,9,6,6,8,7,1,0};
    CountSort(arr, 10);
}

// ��������
// �������������ֵ��λ��
int Maxbit(int* a, int size)
{
    int bit = 1;
    int num = 10;

    for (int i = 0; i < size; i++)
    {
        while (a[i] >= num)
        {
            bit++;
            num*=10;
        }
    }

    return bit;
}

// �������� �о������ת�õ�Ӱ��
void RadixSort(int* arr, int size)
{
    int maxbit = Maxbit(arr, size);
    int* tmp = new int[size];
    int* start = new int[10]; // ��ʼλ��
    int* count = new int[10];// ���� ��¼0-9���ֵĴ���
    int radix = 1; // ��һλ 1 10 100 1000
    for (int bit = 0; bit < maxbit; bit++)
    {
        for (int j = 0; j < 10; j++)
        {
            count[j] = 0;
        }

        for (int j = 0; j < size ; j++)
        {
            int k = (arr[j]/radix) %10; // ��Ӧλ���ϵ�����
            count[k]++;
        }

        // ����start
        start[0] = 0;
        for (int i = 1; i < 10; i++)
        {
            start[i] = start[i - 1] + count[i - 1];
        }

        // һ������
        for (int i = 0; i < size; i++)
        {
            int k = (arr[i]/radix)%10;
            tmp[start[k]++] = arr[i];
        }

        // tmp д��arr
        for (int i = 0; i < size; i++)
        {
            arr[i] = tmp[i];
        }

        radix = radix * 10;
    }

    delete[] tmp;
    delete[] start;
    delete[] count;

}

void test_RadixSort()
{
    int arr[10] = {2,5,4,9,3,6,8,7,1,0};
     RadixSort(arr, 10);
}