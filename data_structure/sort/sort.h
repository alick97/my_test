#pragma once

// ֱ�Ӳ�������
void InsertSort(int*arr, int size);
void test_InsertSort();


//2 ϣ������
// 2 5 4 9 3 6 8 7 1 0
// 2     9     8     0
//   5     3     7
//     4     6     1

void ShellSort(int* arr, int length);
void test_ShellSort();


//3 ѡ������

void SelectSort(int* arr, int size);
void test_SelectSort();

//4 ������
// ���µ���
void _AdjustDown(int* arr, int parent, int size) ;
void HeapSort(int* arr, int size);
void test_HeapSort();


// 5 ð������
void BubbleSort(int* arr, int size);
void test_BubbleSort();


// ��������
// [begin , end] һ�λ���
int Partition(int* arr, int begin, int end);
void QuickSort(int* arr, int size);
void _QuickSort(int* arr, int begin, int end);
void test_QuickSort();
// �����Ż�
void QuickSort_OP(int* arr, int size);
void test_QuickSort_OP();

// �����Ż�
void QuickSort_OP(int* arr, int size);
void test_QuickSort_OP();

int Partition_OP(int* arr, int begin, int end);
// ���� ���ǵݹ顿 ����stack
void _QuickSort_NRe(int* arr, int left, int right);
void test_QuickSort_NRe();


// ���� ���ǵݹ顿 ����stack
void _QuickSort_NRe(int* arr, int left, int right);
void test_QuickSort_NRe();
// �鲢����
void MergeSort(int* arr, int n);
void test_MergeSort();
// ��������
// 1  �� ֪����Χ 0-99  �ù�ϣֱ�Ӷ�ַ��
// 2 �緶Χ100000-200000    ���ȥ100000 �����±�ӳ��
void CountSort(int* arr, int size);
void test_CountSort();

// �������� �о������ת�õ�Ӱ��
void RadixSort(int* arr, int size);
void test_RadixSort();


