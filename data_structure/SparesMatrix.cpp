#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <assert.h>
#include <vector>
#include <string>
using namespace std;
/************************
 *
 * ϡ������ѹ���洢(�����ȴ洢)
 *	��ϡ������ת��(��ת�� �� ����ת�÷�)
 *	20160411
 *
 *************************/
// ��Ԫ��
template<class T>
struct Triple
{
	size_t _row;
	size_t _col;
	T _value;

	Triple()
	{}

	Triple(size_t row, size_t col, T value)
		:_row(row)
		,_col(col)
		,_value(value)
	{}
};

// ϡ�����
template<class T>
class SparesMatrix
{
public:
	SparesMatrix();
	SparesMatrix(const T* array, size_t row, size_t col, const T& _invalid);
	SparesMatrix<T> Transport();	//ת��
	SparesMatrix<T> FastTransport();	//����ת��
	void Display();

protected:
	vector< Triple<T>  > _array; // ��̬����洢ϡ�����
	size_t _rowMatrix;
	size_t _colMatrix;
	T _invalid;				// ����Ƿ�ֵ
};

template<class T> 
SparesMatrix<T>::SparesMatrix()
{}

template<class T>
SparesMatrix<T>::SparesMatrix(const T* array, size_t row, size_t col,const  T& invalid )
	:_rowMatrix(row)
	,_colMatrix(col)
	,_invalid(invalid)
{
	for (size_t i = 0; i < _rowMatrix; i++)
	{
		for (size_t j = 0; j < _colMatrix; j++)
		{
			if (array[i*col + j] != invalid)
			{
				Triple<T> cur(i, j, array[i * col + j]);
				_array.push_back(cur);
			}
		}
	}
}


template<class T>
void SparesMatrix<T>::Display()
{
	assert(_array.size() != 0);
	size_t index = 0;
	for (size_t i = 0; i < _rowMatrix; i++)
	{
		for (size_t j = 0; j < _colMatrix; j++)
		{
			if (index < _array.size() && _array[index]._row == i && _array[index]._col == j)
			{
				cout<<_array[index]._value<<" ";
				index++;
			}
			else
			{
				cout<<_invalid<<" ";
			}
		}
			cout<<endl;
	}
	cout<<endl;
}

//	ת��(��ת�÷�)
template<class T>
SparesMatrix<T> SparesMatrix<T>::Transport()
{
	assert(_array.size() != 0);
	SparesMatrix<T> ret;
	ret._rowMatrix = _colMatrix;
	ret._colMatrix = _rowMatrix;

	ret._invalid = _invalid;
	ret._array.reserve(_array.size());//	�������������

	for (size_t j = 0; j < _colMatrix; j++)
	{
		size_t index = 0;
		while (index < _array.size())
		{
		//	�������ȵ����� _array�� ���к��� j ��Ӧ��
		//	���൱�뽫������ ת��Ϊ�����ȣ�
		//	�����ԭ����������� ����ת�þ����������
			if (_array[index]._col == j)
			{
				Triple<T> tp(_array[index]._col, _array[index]._row, _array[index]._value);
				ret._array.push_back(tp);
			}
			index++;
		}
		if (_array.size() == ret._array.size())
		{
			break;
		}
	}
	return ret;


}

template<class T>
SparesMatrix<T> SparesMatrix<T>::FastTransport()	//	����ת��
{
	assert(_array.size() > 0);
	size_t index = 0;
	SparesMatrix<T> ret;
	ret._rowMatrix = _colMatrix;
	ret._colMatrix = _rowMatrix;
	ret._invalid = _invalid;
	ret._array.resize(_array.size());// ������С ����������reserve(ֻ�ǿռ��� ��Sizeû��)  ��resize �ǵ�����С �������䣩
	//ret._array.reserve(_array.size());
	int* RowCounts = new int[_colMatrix];
	int* RowStart = new int[_colMatrix];

	memset(RowCounts, 0, _colMatrix * sizeof(int));
	memset(RowStart, 0, _colMatrix * sizeof(int));

	for (size_t i = 0; i < _array.size(); i++)
	{
		RowCounts[_array[i]._col]++;	//���÷��� ͳ�ƿ����õ���	���к��ҵ���ӦRowCounts
	}

	RowStart[0] = 0;

	for (size_t i = 1; i < _colMatrix; i++)// ע���1��ʼ ��Ҫ�� _colMatrixд��_array.size()
	{
		RowStart[i] = RowStart[i - 1] + RowCounts[i - 1];
	}
	Triple<T> tp;
	for (size_t i = 0; i < _array.size(); i++)
	{
		tp._row = _array[i]._col;
		tp._col = _array[i]._row;
		tp._value = _array[i]._value;
		ret._array[RowStart[_array[i]._col]++] = tp; // ����

		//ret.Display();
	}

	delete[] RowCounts;
	delete[] RowStart;  // ����
	return ret;
}

void testSparseMatrix()
{
	int array[6][5] = 
	{
		{1, 0, 3, 0, 5 },
		{0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0,},
		{1, 0, 3, 0, 5 },
		{0, 0, 0, 0, 0,},
		{0, 0, 0, 0, 0,},
	};
	SparesMatrix<int> s1((int*)array, 6, 5, 0);
	s1.Display();

	SparesMatrix<int> s2;
	s2 = s1.Transport();
	cout<<"ת�ú�ľ���Ϊ��"<<endl;
	s2.Display();

	SparesMatrix<int> s3;
	s3 = s1.FastTransport();
	cout<<"����ת�ú�ľ���Ϊ��"<<endl;
	s3.Display();
}

int main()
{
	testSparseMatrix();
	return 0;
}
