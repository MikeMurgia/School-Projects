//Michael Murgia
//Section 8
//Programming Assignment #5
//mystring.h
//Due 3/28/24

#include <iostream>
using namespace std;

class MyString
{
	friend ostream& operator<< (ostream& os, const MyString& s1);
	friend istream& operator>> (istream& is, MyString& s1);
	friend istream& getline (istream& is, MyString& s1);
	friend istream& getline (istream& is, MyString& s1, char delim);

	friend MyString operator+ (const MyString& s1, const MyString& s2);

	friend bool operator< (const MyString& s1, const MyString& s2);
	friend bool operator> (const MyString& s1, const MyString& s2);
	friend bool operator<=(const MyString& s1, const MyString& s2);
	friend bool operator>=(const MyString& s1, const MyString& s2);
	friend bool operator==(const MyString& s1, const MyString& s2);
	friend bool operator!=(const MyString& s1, const MyString& s2);

public:
	MyString();				// empty string
	MyString(const char* c);		// conversion from c-string
	MyString(int i);			// conversion from int
	~MyString();				// destructor
	MyString(const MyString& s1);		// copy constructor
	MyString& operator=(const MyString& s);   // assignment operator

	MyString& operator+=(const MyString& s);  // concatenation/assignment

	// bracket operators to access char positions
	char& operator[] (unsigned int index);
	const char& operator[] (unsigned int index) const;

	// insert s into the string at position "index"
	MyString& insert(unsigned int index, const MyString& s);

	// find index of the first occurrence of s inside the string
	//  return the index, or -1 if not found
	int indexOf(const MyString& s) const;

	int getLength() const;		// return string length
	const char* getCString() const;	// return c-string equiv

	MyString substring(unsigned int i1, unsigned int i2) const;
	MyString substring(unsigned int i1) const;

private:
	char * str;
	int size;

};
