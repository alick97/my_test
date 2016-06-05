#define _CRT_SECURE_NO_WARNINGS 1


// ��������
void InsertSort(int* arr, int size);
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

// ѡ������ͬʱ��������С
void SelectSort_min_max(int* arr, int size);
void test_SelectSort_min_max();

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

