//Michael Murgia
//Section 8
//Programming Assignment #7
//Due date: 4/26/24
//

#include "stack.h"
#include<iostream>
#include<cstring>
#include<cctype>

using namespace std;


char getTop(Stack<char>& stack)
{
	char top;
	stack.pop(top);
	stack.push(top);
	return top;
}

bool isPalindrome(const char* pal)
{
	Stack< char > charStack; 
	int len = strlen(pal);

	for (int i = 0; pal[i] != '\0'; i++)
	{
		if (isalpha(pal[i]))
			charStack.push(tolower(pal[i]));
	}

	for (int i = 0; pal[i] != '\0'; i++)
	{
		if (isalpha(pal[i]))
		{
			char ch = tolower(pal[i]);
			if(ch != tolower(getTop(charStack)))
				return false;
			charStack.pop(ch);
		}
	}
	return true;
}

int main()
{
	int max = 101;
	char input[max];

	cout << "Please enter a string:\n > ";
	cin.getline(input, max);

	if (isPalindrome(input))
		cout << "\"" << input << "\"" << " IS a palindrome" << endl;
	else
		cout << "\"" << input << "\"" << " is NOT a palindrome" << endl;


	return 0;
}
