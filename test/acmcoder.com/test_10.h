#pragma once

/*

���ڵ���ʱ
��Ŀ����
�ھ��á��Ƽ����淢��Ľ��죬���Ƕ�ʱ��İ���Խ��Խ�ϸ񣬶���һ��һ��Ӱ�����Ĺ�˾�ĸ߹���˵��������Ҫ���Լ����г���ǰ���ŵ��¸��¡�������ͨ����˵����Ҳ���ܽ�����֮��İ����Ѿ���ǰ���á�
�����һ�����������������δ����ĳһ�컹ʣ�����졣
���������2015��10��18�ա�
����
����һ�����ڸ�ʽΪyyyy-MM-dd�������������Ƿ�С�ڽ��졣
��������
2015-10-19
���
���һ�����ֱ�ʾ���죨2015��10��18�գ���������ڻ�ʣ�����졣
�������
1


*/




#include <iostream>
using namespace std;
#include<string>
struct date
{
public:
    date(){};
    date(const string s)
        :_str(s)
    {
        _year = get_year();
        _day = get_day();
        _month  = get_month();
    }

    string _str;

    // yyyy-MM-dd
    int get_year()
    {
        string str;
        return atoi(str.assign(_str, 0, 4).c_str());
    }
    int get_month()
    {
        string str;
        return atoi(str.assign(_str, 5, 2).c_str());
    }
    int get_day()
    {
        string str;
        return atoi(str.assign(_str, 8, 2).c_str());
    }

    int getday_frommonth(const date& d, int month)
    {
        int day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        if (d._year % 400 == 0 || (d._year % 4 == 0 && d._year % 100 != 0))
        {
            day[2] = 29;
        }

        return day[month];
    }

    int getday_fromyear(int year)
    {
        if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        {
            return 366;
        }

        return 365;
    }


    int get_dif( date& future)
    {
        int count = 0;
        int day_dif = future._day - _day;
        if (day_dif < 0)
        {
            // 1��
            if (future._month == 1)
            {
                future._year--;
                future._month = 12;
                day_dif += 31;
            }
            else
            {
                // --future.month ��7 ��--7 Ϊ6 ��ʾ�õ���6�µ��Ǹ�30������7�µĲ���
                day_dif += getday_frommonth(future, --future._month);
            }
        }    // ������յĲ���

            count += day_dif;
            

            //  �����µĲ��� 12 - 11 ��ʾ �� 11�·ݵ�����
            //int month_count =  future._month - _month;
            
            // 20161117 2016918    ->  201610  20169
           // int end_month = future._month;
           // int start_month = _month;
            day_dif = 0;

            //if (month_count < 0)
            //{
            //    day_dif += getday_fromyear(--future._year);
            //   // swap(start_month, end_month);
            //}

                //if (month_count >= 0)
                //{
                //    
                //    for (int m = start_month;m < end_month; m++)
                //    {
                //            day_dif += getday_frommonth(future, m);
                //    }
                //}
                //else
                //{
                //    // 2016 03      �� 2016�� 1,2    �� 2015
                //    // 2015 05      ��ȥ 2015  ��1,2,3,4
                //    date tmp(future);
                //    tmp._year += 1;
                //    for (int m = 1;m < start_month; m++)
                //    {
                //            day_dif += getday_frommonth(tmp, m);
                //    }

                //    for (int m = 1; m < end_month; m++)
                //    {
                //        day_dif -= getday_frommonth(future, m);
                //    }

                //}
            
            for (int i = 1; i < future._month; i++)
            {
                day_dif += getday_frommonth(future, i);
            }

            for (int i = 1; i < _month; i++)
            {
                day_dif -= getday_frommonth(*this, i);
            }

            count += day_dif;

            // ����year  ������� future��ʱ����� 20151018

          //  int year_dif = future._year - _year;
         //   if (year_dif > 0)
         //   {
                for (int i = _year; i < future._year; i++)
                {
                    count += getday_fromyear(i);
                }

           // }
            return count;
    }

    int _year;
    int _month;
    int _day;

};



int get_day(/*string future*/date &d2)
{
    // yyyy-MM-dd
    date d("2015-10-18");
    //date d("2015-04-01");
    return d.get_dif(/*future*/d2);
}


void test_10()
{
    //string s;
    int y,m,d;
    while(scanf("%d-%d-%d",&y, &m, &d) != EOF)
    {
        date d2;
        d2._year = y;
        d2._month = m;
        d2._day = d;
        cout<<get_day(d2)<<endl;
    }

}



//
//
//#include <iostream>
//using namespace std;
//
//class Date
//{
//	friend ostream& operator<<(ostream& os, const Date&d);
//	friend istream& operator>>(istream& in, const Date&d);
//public:
//	Date(int year = 1900,int month = 1, int day = 1)
//		:_year(year)
//		,_month(month)
//		,_day(day)
//	{
//		if(IsInvalidDate())
//		{
//			_year = 1900;
//			_month = 1;
//			_day = 1;
//		}
//	}
//
//	Date(const Date& d)
//	{
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//
//	Date& operator=(const Date& d)
//	{
//		if(this != &d)
//		{
//			_year = d._year;
//			_month = d._month;
//			_day = d._day;
//		}
//
//		return *this;
//	}
//
//
//public:
//	bool IsInvalidDate()
//	{
//		if((_year < 1900) 
//			|| ((_month < 1) || (_month > 12))
//			|| ((_day < 1) || (_day > DayInMonth())))
//		{
//			return true;
//		}
//		return false;
//	}
//
//	int DayInMonth()
//	{
//		int Days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30,31};
//		if(IsLeapYear())
//		{
//			Days[2] += 1;
//		}
//		return Days[_month];
//	}
//
//	bool IsLeapYear()
//	{
//		if((_year % 400 == 0)||((_year%4 == 0)&&(_year%100 != 0)))
//		{
//			return true;
//		}
//		return false;
//	}
//
//public:
//	void ToCorrectDate()
//	{
//		//-
//		while(_day <= 0)
//		{
//			if(_month == 1)
//			{
//				_month = 12;
//				_year -= 1;
//			}
//			else
//				_month -= 1;
//
//			_day += DayInMonth();
//		}
//		while(_day > DayInMonth())
//		{
//			_day -= DayInMonth();
//			if(_month == 12)
//			{
//				_month = 1;
//				_year += 1;
//			}
//			else
//				_month += 1;
//		}
//
//	}
//	//bool operator==(Date* this, const Date& d)
//	bool operator==(const Date& d)
//	{
//		if((_year == d._year)
//			&&(_month == d._month)
//			&&(_day == d._day))
//		{
//			return true;
//		}
//		return false;
//	}
//
//	bool operator>(const Date& d)
//	{
//		if(_year > d._year)
//			return true;
//		if(_year == d._year)
//		{
//			if(_month > d._month)
//				return true;
//			if(_month == d._month)
//			{
//				if(_day > d._day)
//				{
//					return true;
//				}
//			}
//		}
//		return false;
//	}
//	bool operator>=(const Date& d)
//	{
//		return (*this>d)||(*this==d);
//	}
//
//	bool operator<=(const Date& d)
//	{
//		return !(*this > d);
//	}
//	bool operator<(const Date& d)
//	{
//		return !(*this >= d);
//	}
//	bool operator!=(const Date& d)
//	{
//		return !(*this == d);
//	}
//	Date operator+(int day)
//	{
//		Date d(*this);
//		d._day += day;
//		//
//		d.ToCorrectDate();
//		return d;
//	}
//	Date& operator+=(int day)
//	{
//		_day += day;
//		//
//		this->ToCorrectDate();
//		return *this;
//	}
//
//	Date operator-(int day)
//	{
//		Date d(*this);
//		d._day -= day;
//		//
//		d.ToCorrectDate();
//		return d;
//	}
//
//	Date& operator-=(int day)
//	{
//		_day -= day;
//		//
//		this->ToCorrectDate();
//		return *this;
//	}
//
//	int operator-(Date &d)
//	{
//		int days = 0;
//		Date d1(d);
//		Date d2(*this);
//		if(d1 > d2)
//		{
//			d1 = (*this);
//			d2 = d;
//		}
//		while(d1 != d2)
//		{
//			days++;
//			d1+=1;
//		}
//		return days;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//ostream& operator<<(ostream& os, const Date&d)
//{
//	os<<d._year<<"-"<<d._month<<"-"<<d._day<<endl;
//	return os;
//}
//istream& operator>>(istream& in, const Date&d)
//{
//	return in;
//}
//
////int main()
////{
////	/*Date d(2016,3,1);
////	d-=33;
////	d.operator+=(1);
////	cout << d<<endl;
////	getchar();*/
////	Date d1(2015,3,1);
////	Date d2(2016, 3, 1);
////	cout << d2-d1<<endl;
////	getchar();
////	return 0;
////}
//#include<string>
//void test_10()
//{
//    string str;
//    while (cin>>str)
//    {
//        // yyyy-MM-dd
//        Date d1(2015,10,18);
//        int year = atoi(string().assign(str,0,4 ).c_str());
//        int month= atoi(string().assign(str,5,2 ).c_str());
//        int day = atoi(string().assign(str,8,2).c_str());
//        Date d2(year, month, day);
//        cout<<d2-d1<<endl;
//    }
//
//}
