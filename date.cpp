//Michael Murgia
//Section 8
//Due date: Feb 9, 2024
//Programming Assignment #2
//////////////////////////////////


#include <iostream>
#include <iomanip>
#include <string>
#include "date.h"

using namespace std;

Date::Date(int m, int d, int y)
{
	if (InputCheck(m, d, y))
	{
		month = m;
		day = d;
		year = y;
	}
	else
	{
		day = 1;
		month = 1;
		year = 2000;
	}
}

void Date::Input()
{
	char slash;
	cout << "Enter a date (ex. 1/1/2000): ";
	cin >> month >> slash >> day >> slash >> year;
	if (InputCheck(month, day, year))
	{
		cout << "Valid input";
	}
	else
	{
		do 
		{
			cout << "Invalid Input. Try Again: ";
			cin >> month >> slash >> day >> slash >> year;
		} while (!InputCheck(month, day, year));
	}
}

void Date::Show() const
{
	if (format == 'D')
	{
		cout << month << "/" << day << "/" << year;
	}
	else if (format == 'T')
	{
		cout << setfill('0') << setw(2) << month << "/" << setw(2) << day << "/" << setw(2) << (year % 100);
	}
	else if (format == 'L')
	{
		string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
		cout << months[month - 1] << " " << day << ", " << year;
	}
	else if	(format == 'J')
	{
		int jul = day;
		for (int i = 1; i < month; ++i)
			jul += MonthDays(i, year);
		cout << setw(2) << (year % 100) << "-" << setw(3) << jul; 
	}
	else
	{
		cout << month << "/" << day << "/" << year;
	}
}

bool Date::Set(int m, int d, int y)
{
	if (InputCheck(m, d, y))
	{
		month = m;
		day = d;
		year = y;
		return true;
	}
	else
	{
		return false;
	}
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetDay() const
{
	return day;
}

int Date::GetYear() const
{
	return year;
}

bool Date::SetFormat(char f)
{
	switch (f) {
		case 'D':
		case 'T':
		case 'L':
		case 'J':
			format = f;
			return true;
		default:
			return false;
	}
}

void Date::Increment(int numDays)
{
	int add = numDays;
	if (InputCheck(month, (day + add), year))
	{
		day = day + add;
	}
	else
	{
		day = day + add;
		do
		{
			if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				day = day - 30;
				month = month + 1;
			}
			else if (month == 2 && year % 4 != 0)
			{
				day = day - 28;
				month = month + 1;
			}
			else if (month == 2 && year % 4 == 0)
			{
				day = day - 29;
				month = month + 1;
			}
			else if (month == 12)
			{
				day = day - 31;
				month = month + 1 - 12;
				year = year + 1;
			}
			else
			{
				day = day - 31;
				month = month + 1;
			}
		} while (!InputCheck(month, day, year));

	}
}

int Date::Compare(const Date& d)
{
	if (d.year > year)
	{
		return -1;
	}
	else if (d.year < year)
	{
		return 1;
	}
	else
	{
		if (d.month > month)
		{
			return -1;
		}
		else if (d.month < month)
		{
			return 1;
		}
		else
		{
			if (d.day > day)
			{
				return -1;
			}
			else if (d.day < day)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
}

bool Date::InputCheck(int m, int d, int y)
{
        if (m > 12 || m < 1)
        {
                return false;
        }
        else if (y < 1)
        {
                return false;
        }
        else if (d > 31 || d < 1)
        {
                return false;
        }
        else if (m == 2 && y % 4 == 0)
        {
		if(y % 400 == 0)
		{  
	                if (d > 29 || d < 1)
                		return false;
		}
		else if (y % 100 == 0)
		{
			if (d > 28 || d < 1)
				return false;
		}
		else
		{
			if (d > 29 || d < 1)
				return false;
		}
        }
        else if (m == 2 && y % 4 != 0)
        {
                if (d > 28 || d < 1)
                	return false;
        }
        else if (m == 4 || m == 6 || m == 9 || m == 11)
        {
                if (d > 30 || d < 1)
                        return false;
		return true;
        }
	else
	{
		return true;
	}
}

int Date::MonthDays(int m, int y) const
{
	if (m==2)
	{
		if ((y % 4 == 0 && y % 100 !=0) || (y % 400 == 0))
			return 29;
		else
			return 28;
	}
	else if (m == 4 || m == 6 || m == 9 || m == 11)
	{
		return 30;
	}
	else
	{
		return 31;
	}
}
