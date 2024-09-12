//Michael Murgia
//COP 3330
//Programming Assignment #3
//Due Date: Feb 22, 2024

#include "mixed.h"
#include <iostream>
#include <iomanip>

using namespace std;

Mixed::Mixed(int p, int n, int d) : part(0), num(0), den(1)
{
	if (d == 0||(n < 0 && p < 0)||(n < 0 && d < 0)||(d < 0 && p < 0)||(d < 0 && n < 0 && p < 0))
	{
		part = 0;
		num = 0;
		den = 1;
	}
	else
	{
		part = p;
		num = n;
		den = d;
	}
}

Mixed::Mixed(int p) 
{
	part = p;
	num = 0;
	den = 1;
}

double Mixed::Evaluate() const
{
	if (part >= 0)
		return part + (static_cast<double>(num) / den);
	else
		return part - (static_cast<double>(num) / den);
}

void Mixed::ToFraction()
{
	int p1 = part;
	int n1 = num;
	int d1 = den;
	if (part < 0)
		part = part * -1;
	if (num < 0)
		num = num * -1;
	if (den < 0)
		den = den * -1;		
	num = num + (part * den);
	if (p1 < 0|| n1 < 0|| d1 < 0)
		num = num * -1;
	part = 0;
}

void Mixed::Simplify()
{
	int n1 = num;
	if (num < 0)
	{
		n1 = num * -1;
		if (part != 0)
		{
			num = num * -1;
			part = part * -1;
		}
	}
	if (n1 > den)
	{
		do
		{
			n1 = n1 - den;
			if (part < 0)
				part--;
			else
				part++;
		}while (n1 > den);
		if (num < 0 && part == 0)
			num = n1 * -1;
		else if (num < 0)
			num = n1 * -1;
		else
			num = n1; 
	}
	int div = 2;
	if (num > 0)
	{
		while (div <= num && div <= den)
		{
			if (num % div == 0 && den % div == 0)
			{
				num = num/div;
				den = den/div;
			}
			else
			{
				div++;
			}
		}
	}
	if (num < 0)
	{
		int tempnum = num * -1;
		while (div <= tempnum && div <= den)
                {
                        if (tempnum % div == 0 && den % div == 0)
                        {
                                tempnum = tempnum/div;  
                                den = den/div;
                        }
                        else
                        {
                                div++;
			}
		}
		num = tempnum * -1;
		if (num < 0 && part != 0)
		{
			num = num * -1;
			part = part * -1;
		}
	}
}

ostream& operator<<(ostream& out, const Mixed& m)
{
	if (m.part == 0 && m.num == 0)
	{
		out << "0";
	}
	else
	{
		if (m.part != 0)
			out << m.part;
		if (m.num != 0)
		{
			if (m.part != 0)
				out << ' ';
			out << m.num << '/' << m.den;
		}
	}
	return out;
}

istream& operator>>(istream& in, Mixed& m)
{
	int p, n, d;
	char slash;
	in >> p >> n >> slash >> d;
	if (d == 0||(n < 0 && p < 0)||(n < 0 && d < 0)||(d < 0 && p < 0)||(d < 0 && n < 0 && p < 0))
	{
		m.part = 0;
		m.num = 0;
		m.den = 0;
	}
	else
	{
		m.part = p;
		m.num = n;
		m.den = d;
	}
	return in;
}

bool operator<(const Mixed& mix1, const Mixed& mix2)
{
	Mixed m1 = mix1;
	Mixed m2 = mix2;
	m1.num = m1.num + (m1.part * m1.den);
	m2.num = m2.num + (m2.part * m2.den);
	
	return m1.num * m2.den < m2.num * m1.den;
}

bool operator>(const Mixed& mix1, const Mixed& mix2)
{
	Mixed m1 = mix1;
	Mixed m2 = mix2;
	m1.num = m1.num + (m1.part * m1.den);
	m2.num = m2.num + (m2.part * m2.den);

	return m1.num * m2.den > m2.num * m1.den;
}

bool operator<=(const Mixed& mix1, const Mixed& mix2)
{
	if (mix1 > mix2)
		return false;
	else
		return true;
}

bool operator>=(const Mixed& mix1, const Mixed& mix2)
{
	if (mix1 < mix2)
		return false;
	else
		return true; 
}

bool operator==(const Mixed& mix1, const Mixed& mix2)
{
	return mix1 >= mix2 && mix1 <= mix2;
}

bool operator!=(const Mixed& mix1, const Mixed& mix2)
{
	if (mix1 == mix2)
		return false;
	else
		return true;
}

Mixed operator+(const Mixed& mix1, const Mixed& mix2)
{
	Mixed m1 = mix1;
	Mixed m2 = mix2;
	m1.Simplify();
	m2.Simplify();
	int numerator;
	int integerPart;
	int denominator = m1.den * m2.den;
	if (m1.num < 0 && m2.num < 0)
		numerator = m1.num * m2.den + m2.num * m1.den;
	else if (m1.num < 0 || m1.part < 0)
		numerator = (m2.num *m1.den - m1.num * m2.den);
	else if (m2.num < 0 || m2.part < 0)
		numerator = (m1.num *m2.den - m2.num * m1.den);
	else
		numerator = m1.num * m2.den + m2.num * m1.den;
	if (m1.part < 0)
		integerPart = m2.part + m1.part;
	else if (m2.part < 0)
		integerPart = m1.part + m2.part;
	else
		integerPart = m1.part + m2.part;
	Mixed m3(integerPart, numerator, denominator);
	m3.Simplify();
	return Mixed(m3.part, m3.num, m3.den);
}
Mixed operator-(const Mixed& mix1, const Mixed& mix2)
{
	Mixed m1 = mix1;
	Mixed m2 = mix2;
	m1.Simplify();
	m2.Simplify();
	Mixed m3;
	m1.ToFraction();
	m2.ToFraction();

	m3.den = m1.den * m2.den;
	m3.num = m1.num * m2.den - m2.num * m1.den;
	m3.Simplify();
	return Mixed(m3.part, m3.num, m3.den);
}
Mixed operator*(const Mixed& mix1, const Mixed& mix2)
{
	Mixed m1 = mix1;
	Mixed m2 = mix2;
	m1.Simplify();
	m2.Simplify();

	m1.ToFraction();
	m2.ToFraction();
	Mixed m3;
	m3.den = m1.den * m2.den;
	m3.num = m1.num * m2.num;
	m3.Simplify();
	return Mixed(m3.part, m3.num, m3.den);
}
Mixed operator/(const Mixed& mix1, const Mixed& mix2)
{
	Mixed m1 = mix1;
	Mixed m2 = mix2;
	m1.Simplify();
	m2.Simplify();
	m1.ToFraction();
	m2.ToFraction();


	Mixed m3;
	m3.num = m1.num * m2.den;
	m3.den = m1.den * m2.num;
	if (m3.den < 0)
	{
		m3.den = m3.den * -1;
		m3.num = m3.num * -1;
	}


	m3.Simplify();
	return Mixed(m3.part, m3.num, m3.den);
}

Mixed& Mixed::operator++()
{
	num = num + den;
	Simplify();
	return *this;
}

Mixed Mixed::operator++(int)
{
	Mixed temp = *this;
	++(*this);
	return temp;
}

Mixed& Mixed::operator--()
{
	part = part-1;
	Simplify();
	return *this;
}

Mixed Mixed::operator--(int)
{
	Mixed temp = *this;
	part = part-1;
	Simplify();
	return temp;

}
