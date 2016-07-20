#define _CRT_SECURE_NO_WARNINGS 1
//#include <iostream>
#include "BigData.h"

BigData::BigData(INT64 value)
	:_value(value)
{
	INT64ToString();
}

BigData::BigData(const char *pData)
{
	if (NULL == pData)
	{
		assert(false);
		return;
	}

	// "1235464678"
	// "+123456789"
    // "+"
    // "       "
    // "000012312313"
	// "-12131313123"
	// "123123asdad1231213"
	// "a4546546"
	// "000000000"

    char *pStr = (char*)pData;
	char cSymble = pData[0]; // ����λ
	// �淶�� �涨 :1��һλΪ���� �Ժ��ֻ��������λ
	//              2 ����λ���һλ����
    //  ���ࣺ����  �Ƿ��ŵ�
	if (cSymble == '+' || cSymble == '-')
	{
		pStr++;
	}
	else if (cSymble >= '0' && cSymble <= '9')
	{
		cSymble = '+';
	}
	else // ��һλ�Ƿ�
	{
		_value = UN_INT;
		return;
	}

	// ȥ�������0 ��"0000123123132"
    while ('0' == *pStr)
	{
		++pStr;
	}

	// ����strData��С  resize�Լ�ά����\0�� �����1�Ǽӷ���λ
	_strData.resize(strlen(pStr) + 1);
	_strData[0] = cSymble;

  


	// "122121a121212"->"122121"
	_value = 0;

      if (1 == _strData.size())
    {
        _strData.append(1, '0'); // "+" "0000000" 
        return;
    }

	int count = 1; // ��������
	while (*pStr >= '0' && *pStr <= '9')
	{
		_value = _value * 10 + (*pStr - '0');
		_strData[count++] = *(pStr++);
	}
	// ���µ���strData��С ��ֹ"45464adsd44564"���������
	_strData.resize(count);

    if (1 == count)
    {
        _value = UN_INT; // ��ֹ ��+ashdashj�� ����0
        return;
    }

	if (cSymble == '-') 
	{
		_value = 0 - _value;
	}
}

// �����
bool BigData::IsINT64Overflow() const
{
	std::string temp("+9223372036854775807"); //0x7fffffffffffffff

	if ('-' == _strData[0])
	{
		temp = "-9223372036854775808"; // 0x1000000000000000
	}

	if (_strData.size() < temp.size())
	{
		return false;
	}
	else if ((_strData.size() == temp.size()) && (_strData <= temp))
	{
		return false;
	}
	else
	{
		return true;
	}
}

BigData BigData::operator+(const BigData& bigData)
{
	// ��������û����� ���û�����
	if (!IsINT64Overflow() && !bigData.IsINT64Overflow())
	{
		// ������� �����
		if (_strData[0] != bigData._strData[0])
		{
			return BigData(_value + bigData._value);
		}

		// ����ͬ�� �п������ 
		// ���������
		// ����1 ��������7 ��2   10 - 7 >= 2 
		// ����2 �������� -7,-2  -10-(-7) <= -2

		// ͬ�� ��������
        INT64 temp = MIN_INT64 - _value;
		 if ((_value >= 0 && MAX_INT64 - _value >= bigData._value) || (_value < 0 && /*MIN_INT64 - _value*/temp <= bigData._value))  
            // MIN_INT64 - _value <= bigData._value) ������ 0 <= -3 �����޷����� -3�ǱȽϴ������ ���ڸ�����С + -3  ����0<=-3  ������������������������ ����  ����Ҫ��temp
            // ���뾯�棺��\bigdataoperationitem\bigdata.cpp(116): warning C4018: ��<=��: �з���/�޷��Ų�ƥ��
		{
			return BigData(_value + bigData._value);
		}
	}


    //  ����������һ�������
	// ������
	if (_strData[0] == bigData._strData[0])
    {
        return BigData((Add(_strData, bigData._strData)).c_str());
    }
    // ��� �� ���������
    return BigData((Sub(_strData, bigData._strData)).c_str());
}

std::string BigData::Add(std::string left, std::string right)
{
	int LSize = left.size();
	int RSize = right.size();

	// ��֤ ��� ���� ���ұ߳�
	if (LSize < RSize)
	{
		std::swap(LSize, RSize);
		std::swap(left, right);
	}

	std::string ret;
	ret.resize(LSize + 1); // ������λ��һλ
	ret[0] = left[0]; // �������λ  ��ߴ� ��߷���Ϊ���շ���
	int carryOver = 0; // �����λ
	for (int i = 1; i < LSize; i++) // i ��1��ʼ
	{
		int src = left[LSize - i] - '0' + carryOver;

		// �ұߵĳ���С ����Խ��
		if (i < RSize)
		{
			src += right[RSize - i] - '0';
		}

		// ret �ܳ�ΪLSize + 1
		ret[LSize + 1 -i] = src % 10 + '0';
		carryOver = src / 10;
	}

	ret[1] = carryOver + '0';

	return ret; // "0004544654564" �����0���ÿ��� operator+ ��return�����¹���BigData���� ���캯����ȥ��
}

 BigData BigData::operator-(const BigData& bigData)
 {
     // ������û����� �ҽ��û����������
     if (!IsINT64Overflow() && !bigData.IsINT64Overflow())
     {
         // ����ͬ��
         if (_strData[0] == bigData._strData[0])
         {
             return BigData(_value - bigData._value);
         }
         else // �������
         {
             // + ��ȥ-    10 + (-2) = 8 >= 7
             if ((_value >= 0 && MAX_INT64 + bigData._value >= _value)
                 // -��ȥ+  -10 + ��2�� = -8 <= -7
                     || (_value < 0 && MIN_INT64 + bigData._value <= _value))
             {
                 return BigData(_value - bigData._value);
             }
         }
     }

     // 
     // ������
     // ���
     if (_strData[0] != bigData._strData[0])
     {
         BigData ret =  BigData(Add(_strData, bigData._strData).c_str());
         // ��Ϊ�ӷ��ķ������Գ������ķ���Ϊ׼ ���Զ��ڱ������Ƕ̵ĵ����Ҫ����
         ret._strData[0] = _strData[0];
         return ret;
     }

     // ͬ��
     return BigData(Sub(_strData, bigData._strData).c_str());

 }


std::string BigData::Sub(std::string left, std::string right)
{
    //ǰ��  ���� ���� ͬ��
    int iLSize = left.size();
    int iRSize = right.size();
    char cSymble = left[0]; // ������߳�ʼ�� ����operator+�� �����������Sub ��Sub��������ͬ�Ų���  ���������ȷ�ģ�

    // ��֤��߳��� ���ڵ��� �ұ�
    if (iLSize < iRSize || (iLSize == iRSize && left < right))
    {
        std::swap(left, right);
        std::swap(iLSize, iRSize);

        //  2 - 3 = -1  2+  -1  + ->-
        //  -2 - (-3) = 1   2- +1   -->+
        if ('+' == cSymble)
        {
            cSymble = '-';
        }
        else
        {
            cSymble = '+';
        }

    }
        // ������
        std::string strRet;
        strRet.resize(left.size());
        strRet[0] = cSymble;

        for (int Idx = 1; Idx < iLSize; ++Idx)
        {
           int cRet = left[iLSize - Idx] - '0';

           // ��ֹ ���� right�ķ�Χ
           if (Idx < iRSize)
           {
               cRet -= (right[iRSize - Idx] - '0');
           }

           if (cRet < 0)
           {
               // ���λ��λ
               left[iLSize - Idx - 1] -= 1;
               cRet += 10;
           }

           strRet[iLSize - Idx] = cRet + '0';
        }

        return strRet;
    }

BigData  BigData::operator*(const BigData& bigData)
{
    if (_strData[1] == '0' || bigData._strData[1] == '0')
    {
        return BigData(INT64(0));
    }
    // ����������� �ҽ������� �����
    if (!IsINT64Overflow() && !bigData.IsINT64Overflow())
    {
        // ͬ��
        if (_strData[0] == bigData._strData[0])
        {
            // 10 / -2 = -5 <= -3
            // 10 / 2 = 5 >= 3
            if (_value > 0 && MAX_INT64 / _value >= bigData._value 
                || (_value < 0 && MAX_INT64/_value <= bigData._value ))
            {
                return BigData(_value * bigData._value);
            }

        }
        else // ���
        {
            // -10 / 2 = -5 <= -3
            // -10 / -2 = 5 >= 3
             if (_value > 0 && MIN_INT64 / _value <= bigData._value 
                || (_value < 0 && MIN_INT64/_value >= bigData._value ))
            {
                return BigData(_value * bigData._value);
            }
        }
    }

    // ������

    return BigData(Mul(_strData, bigData._strData).c_str());
}

std::string BigData::Mul(std::string left, std::string right)
{ 
    // ȷ������λ
    char cSymbol = '+';
    if (left[0] != right[0])
    {
        cSymbol = '-';
    }

    int iLSize = left.size();
    int iRSize = right.size();

    // ��֤��߳��� С�� �ұ� (ʹ�� ���� ��ѭ������ѭ��Сһ��)
    if (iLSize > iRSize)
    {
        std::swap(left, right);
        std::swap(iLSize, iRSize);
    }

    // ���� ���ؿռ�   Ϊ�������Ⱥͼ��Ϸ���λ 
    // ��Ϊ100*1000<= 100000 ����99*999 < 100000 5λ
    std::string sRet;
   // sRet.resize(iLSize + iRSize - 1);// ע�� �������λ�������� ���Լ�ȥ1
     // ������һ�� ��ֹ��ע2�� ÿ�ζ�ӡ�0�� 
    sRet.assign(iLSize + iRSize - 1, '0');

    sRet[0] = cSymbol;
   
    int iDataLen = sRet.size();
   


    int ioffset = 0; // ÿ���������λ
    // ��ȡ���һ�� �� �ұ�ÿһλ���
    for (int iLIdx = 1; iLIdx < iLSize; iLIdx++)
    {
        char cLeft = left[iLSize - iLIdx] - '0';// ��Ȼchar ��������˼������ �����ַ� ��ʡ�ռ�
        char cStep = 0;// ��λ

        if (cLeft == 0)
        {
            ioffset++;
            continue;
        }
        // 99*999
        for (int iRIdx = 1; iRIdx < iRSize; ++iRIdx)
        {
            char cRet = cLeft * (right[iRSize - iRIdx] - '0') + cStep;
           //��ע2��//���� ÿ�ζ�ӡ�0�� sRet[iDataLen - iRIdx - ioffset] += cRet%10 + '0';
            // ������� �����桾ע2�� ���ٿռ�����string��assign��ʼ���ɡ�0��
            cRet += sRet[iDataLen - iRIdx - ioffset] - '0';
            sRet[iDataLen - iRIdx - ioffset] = cRet%10 + '0';
            cStep = cRet/10;
        }
        sRet[iDataLen - iRSize - ioffset] += cStep;
        ioffset++;
    }

    return sRet;
}







std::ostream& operator<<(std::ostream& _cout, const BigData& bigData)
{
	if (!bigData.IsINT64Overflow())
	{
		_cout << bigData._value;
	}
	else
	{
		char* ptr = (char*)bigData._strData.c_str();
		if ('+' == ptr[0])
		{
			ptr++;
		}
		_cout<<ptr;
	}

	return _cout;
}

void BigData::INT64ToString() // ��_valueת��Ϊ�ַ���
{
	char cSymble = '+';
    INT64 pnumber = _value;
	if (_value < 0)
	{
		cSymble = '-';
        pnumber = 0 - pnumber; // ע��  -9223372036854775808 ������С �޷�ת�� ����  �� ��λ�� ���λ����λ 0 - 100 = 100 ��������Ҫ ע���жϸ���  �����桾ע��1��
	}
	_strData.append(1, cSymble);

	while (pnumber)
	{
		int num = pnumber % 10;

        // ��ע��1�� 
        if (num < 0)
        {
            num = 0 - num;
        }

		_strData.append(1, num + '0');
		pnumber /= 10;
	}

	char* pleft = (char*)_strData.c_str() + 1;
	char* pright = pleft + _strData.size() -2;

	while (pleft < pright) // �ַ�������
	{
		std::swap(*pleft, *pright);
		pleft++;
		pright--;
	}

    if (1 == _strData.size())
    {
        _strData.append(1, '0');
    }

}

bool BigData::IsLeftStrBig(char* pLeft, int LSize,const char* pRight, int RSize)
{
    if (LSize > RSize || LSize == RSize && strncmp(pLeft, pRight, RSize) >= 0)
    {
        return true;
    }

    return false;
}

char BigData::SubLoop(char* pLeft, int LSize,const char* pRight, int RSize)
{
    assert(pLeft != NULL && pRight != NULL);
    char cRet = '0'; // ��¼�� �Ĵ��� ��'0'
    while(true)
    {
        if (!IsLeftStrBig(pLeft, LSize, pRight, RSize))
        {
            break;
        }

        for (int iIdx = 1; iIdx < RSize; ++iIdx)
        {
            pLeft[LSize - iIdx] -= pRight[RSize - iIdx]; // ��0��������
            if ( pLeft[LSize - iIdx] < 0)
            {
                pLeft[LSize - iIdx - 1] -= 1;// ��λ��λ
                pLeft[LSize - iIdx] += 10;
            }

            // ��ԭ���ַ�
            pLeft[LSize - iIdx] += '0'; 
        }

        // ����� ǰ�� �� ��0�� ȥ��
        // ��ֹ����ֹȥ�� �硰3300000�� - ��33�� ���� ��0000000000000�� ����ֹ�� �̲����ӡ�0��������
        // 090  ��0����ȥ
     /*   while (*pLeft == '0' && LSize > 0)
        {
            pLeft++;
            LSize--;
        }*/

        cRet++; 
    }

    return cRet;
}


BigData BigData::operator/(const BigData& bigData)
{
    //2222222222222/33

    // ��������Ϊ0
    if ('0' == _strData[0])
    {
        assert(false);
    }
    // ���� ��û�����
    if (!IsINT64Overflow() && !bigData.IsINT64Overflow())
    {
        return _value / bigData._value;
    }

    // ��� С�� �ұ�
    if (_strData.size() < bigData._strData.size() || /*_strData.size() == bigData._strData.size() &&*/ strcmp(_strData.c_str() + 1, bigData._strData.c_str() + 1) < 0 )
    {
        return BigData(INT64(0));
    }

    // �ұ� +-1 
    if (!bigData.IsINT64Overflow() && (1 == bigData._value || -1 == bigData._value))
    {
        if (1 == bigData._value)
        {
            return *this;
        }

         std::string ret = _strData;
        // -1
        if ('+' == ret[0])
        {
            ret[0] = '-';
        }
        else
        {
            ret[0] = '+';
        }

        return BigData(ret.c_str());
    }

    // ��� ���� �ұ�
    if (strcmp(_strData.c_str() + 1, bigData._strData.c_str() + 1) == 0)
    {
        std::string ret = "+1";
        if (_strData[0] != bigData._strData[0])
        {
            ret[0] = '-';
        }

        return BigData(ret.c_str());
    }
    // ����
    return BigData(Div(_strData, bigData._strData).c_str());
}

std::string BigData::Div(std::string left, std::string right)
{
    //  ǰ�� ��� ���� �ұ�

    std::string sRet;
    sRet.append(1, '+');
    if (left[0] != right[0])
    {
        sRet[0] = '-';
    }
    //Խ������λ
    char* pLeft = (char*)(left.c_str() + 1);
    char* pRight = (char*)(right.c_str() + 1);
    int LSize = left.size() - 1;
    int RSize = right.size() - 1;
    int DataLen = RSize; // ƫ�� ��pLeft����ܹ����Կ�������λ �տ�ʼ����Ϊ1 Ҳ�ɳ�ʼ��Ϊ�ұ���ֵ����
    
  

    for (int iIdx = 0; iIdx < LSize;)
    {
          // ������0��
        // 3300000000000/33  00  0000000000000
        if ('0' == *pLeft)
        {
            sRet.append(1, '0');
            pLeft++;
            iIdx++;
            continue;
        }


        if (!IsLeftStrBig(pLeft, DataLen, pRight,RSize))
        {
            // ��� С�� �ұ� �̲�0
            sRet.append(1, '0');
            DataLen++; // �������ӳ�һλ
            if (DataLen + iIdx > LSize) // >= ����һλ ��ֹԽ�糬����ߵ��ܳ���
            {
                break;
            }
        }
        else // ��ߴ����ұ�
        {
            sRet.append(1, SubLoop(pLeft, DataLen, pRight, RSize));
            // ����pLeft ��Ϊ����SubLoop��pLeft�õ���ֵ���� ����Ҫ���������
            while (*pLeft == '0' && DataLen > 0 )
            {
                pLeft++;
                iIdx++;
              
                DataLen--; // 33333/33 left 33 ���00 <33 ��Datalenû���Ļ� -> left 0033 ��= 33  -> ��11 ԭ��Ҫ�� 101   �����м��0    DataLen--��ֹ����0
                // Ҳ��ֹ ��330000000000��
            }
            // 22222222222222/33
            // "0242222222222222"
            //  "242222222222222"
            DataLen++; // ��ֹ����һ����24 �� 33 �Ƚ� 24 < 33 �̶�����һ��0
            if (DataLen + iIdx > LSize) // >= ����һλ
            {
                break;
            }
        }
    }


    return sRet;
}




