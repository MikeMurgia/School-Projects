//Michael Murgia
//Section 8
//Programming Assignment #5
//mystring.cpp
//Due 3/28/24


#include "mystring.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <fstream>

using namespace std;

MyString::MyString()		//empty string
{
	size = 0;
	str = new char[1];
	str[0] = '\0';
}

MyString::MyString(const char* c)	//convert from c-string
{
	size = strlen(c);
	str = new char[size+1];

	for(int i = 0; i < size; i++)
		str[i] = c[i];
	strcpy(str, c);
}

MyString::MyString(int n)	//convert from int
{
	int digits = 0;
	int x = n;
	int temp = n;
	while (temp != 0)
	{
		temp /= 10;
		digits++;
	}
	if (n<0)
	{
		digits++;
		x *= -1;
	}
	size = digits;
	str = new char[size + 1];
	for (int i = size - 1; i >= 0; --i)
	{
		str[i] = '0' + (x % 10);
		x /= 10;
	}
	if (n<0)
	{
		str[0] = '-';
	}
	str[size] = '\0';

}

MyString::~MyString()		//destructor
{
	delete[] str;
}

MyString::MyString(const MyString& s1)	//copy constructor
{
	size = s1.size;
	str = new char[size+1];
	for(int i = 0; i < size; i++)
		str[i] = s1.str[i];
	str[size + 1] = '\0';
}

MyString& MyString::operator=(const MyString& s)
{
	if (this != &s)
	{
		delete[] str;
		
		size = s.size;
		str = new char[size + 1];
		strcpy(str, s.str);
	}
	return *this;
}

MyString& MyString::operator+=(const MyString& s)
{
	char* temp = new char[size + s.size + 1];
	strcpy(temp, str);
	strcat(temp, s.str);
	delete[] str;
	str = temp;
	size += s.size;
	return *this;
}

char& MyString::operator[](unsigned int index)
{
	if (index >= 0 && index < size)
	{
		return str[index];
	}
	else
	{
		int newSize = index + 1;
		char* temp = new char[newSize + 1];
		strcpy(temp, str);
		for (int i = size; i < newSize; i++)
			temp[i] = ' ';
		temp[newSize] = '\0';
		delete[] str;
		str = temp;
		size = newSize;
		return str[index];
	}
}

const char& MyString::operator[](unsigned int index) const
{
	if (index >= 0 && index < size)
	{	return str[index];	}
	else
	{
		static const char null = '\0';
		return null;
	}
}

MyString& MyString::insert(unsigned int index, const MyString& s)
{
	if (index < 0 || index > size)
		index = size;	
	char* temp = new char[size + s.size + 1];
	strncpy(temp, str, index);
	strcpy(temp + index, s.str);
	strcpy(temp + index + s.size, str + index);
	delete[] str;
	str = temp;
	size += s.size;
	return *this;
}

int MyString::indexOf(const MyString& s) const
{
	if (s.size > size)
		return -1;
	for (int i = 0; i <= size - s.size; i++)
	{
		bool found = true;
		for (int j = 0; j < s.size; j++)
		{
			if (str[i+j] != s.str[j])
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return i;
		}
	}
	return -1;
}

int MyString::getLength() const
{
	return size;
}

const char* MyString::getCString() const
{
	return str;
}

MyString MyString::substring(unsigned int i1, unsigned int i2) const
{
	if (i1 < 0 || i1 >= size || i2 <= 0)
		return MyString();
	if (i1 + i2 > size)
		i2 = size - i1;
	char* temp = new char[i2 + 1];
	strncpy(temp, str + i1, i2);
	temp[i2] = '\0';
	MyString final(temp);
	delete[] temp;
	return final;
}

MyString MyString::substring(unsigned int i1) const
{
	return substring(i1, size - i1);
}

ostream& operator<< (ostream& os, const MyString& s1)
{
	os << s1.str;
	return os;
}

istream& operator>> (istream& is, MyString& s1)
{

	s1 = MyString();
	char ch;
	int i = 0;
	int j = 10;
	char* temp = new char[j];

	
	while(is.peek() != ' ' && is.peek() != '\n' && is.peek() != '\t')
	{	
		is.get(ch);
		temp[i] = ch;
		i++;
		if (i == j)
		{
			int k = j + 5;
			char* temp2 = new char[j];
			for (int l = 0; l < i; l++)
				temp2[l] = temp[l];
			delete[] temp;
			temp = temp2;
			j = k;
		}
	}
	s1.size = i;
	delete[] s1.str;
	s1.str = temp;
	return is;
}

istream& getline (istream& is, MyString& s1)
{
	s1 = MyString();
	char ch;
	int i = 0;
	int j = 30;
	char* temp = new char[j];

	while(is.peek() != '\n')
	{
		is.get(ch);
		temp[i] = ch;
		i++;
		if(i == j)
		{
			int k = j + 5;
			char* temp2 = new char[k];
			for(int l = 0; l < i; l++)
				temp2[l] = temp[l];
			delete[] temp;
			temp = temp2;
			j = k;
		}
	}
	s1.size = i;
	delete[] s1.str;
	s1.str = temp;
	return is;
}

istream& getline (istream& is, MyString& s1, char delim)
{
	s1 = MyString();
	char ch;
	int i = 0;
	int j = 30;
	char* temp = new char[j];

	while(is.peek() != delim && is.peek() != '\n')
	{	
		is.get(ch);
		temp[i] = ch;
		i++;
		if(i == j)
		{
			int k = j + 5;
			char* temp2 = new char[k];
			for(int l = 0; l < i; l++)
				temp2[l] = temp[l];
			delete[] temp;
			temp = temp2;
			j = k;
		}
	}
	if (is.peek() == delim)
		is.ignore();
	s1.size = i;
	delete[] s1.str;
	s1.str = temp;
	return is;
}

MyString operator+ (const MyString& s1, const MyString& s2)
{
	MyString final;
	final.size = s1.size + s2.size;
	final.str = new char[final.size + 1];
	strcpy(final.str, s1.str);
	strcat(final.str, s2.str);
	return final;
}

bool operator< (const MyString& s1, const MyString& s2)
{
	return strcmp(s1.str, s2.str) < 0;
}

bool operator> (const MyString& s1, const MyString& s2)
{
	return strcmp(s1.str, s2.str) > 0;
}

bool operator<=(const MyString& s1, const MyString& s2)
{
	return strcmp(s1.str, s2.str) <= 0;
}

bool operator>=(const MyString& s1, const MyString& s2)
{
	return strcmp(s1.str, s2.str) >= 0;
}

bool operator==(const MyString& s1, const MyString& s2)
{
	return strcmp(s1.str, s2.str) == 0;
}

bool operator!=(const MyString& s1, const MyString& s2)
{
	return strcmp(s1.str, s2.str) != 0;
}

