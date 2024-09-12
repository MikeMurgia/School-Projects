//Michael Murgia
//COP 3330
//Programming Assignment #3
//Due Date Feb 22, 2024

#include<iostream>
using namespace std;

class Mixed
{
	friend istream& operator>>(istream& in, Mixed& m);
	friend ostream& operator<<(ostream& out, const Mixed& m);
	friend bool operator<(const Mixed& mix1, const Mixed& mix2);
	friend bool operator>(const Mixed& mix1, const Mixed& mix2);
	friend bool operator<=(const Mixed& mix1, const Mixed& mix2);
	friend bool operator>=(const Mixed& mix1, const Mixed& mix2);
	friend bool operator==(const Mixed& mix1, const Mixed& mix2);
	friend bool operator!=(const Mixed& mix1, const Mixed& mix2);
	friend Mixed operator+(const Mixed& mix1, const Mixed& mix2);
	friend Mixed operator-(const Mixed& mix1, const Mixed& mix2);
	friend Mixed operator*(const Mixed& mix1, const Mixed& mix2);
	friend Mixed operator/(const Mixed& mix1, const Mixed& mix2);

public: 
	Mixed(int part, int num, int den);
	Mixed(int part = 0);
	
	double Evaluate() const;
	void ToFraction();
	void Simplify();
	
	Mixed& operator++();
	Mixed operator++(int);
	Mixed& operator--();
	Mixed operator--(int);

private:
	int part;
	int num;
	int den;
};
