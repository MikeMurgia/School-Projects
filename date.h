//Michael Murgia
//Section 8
//Due Date: Feb 9, 2024
//Programming Assignment #2
///////////////////////////

class Date
{
public:

	Date(int m = 1, int d = 1, int y = 2000);	

	void Input();
	void Show() const;
	bool Set(int m, int d, int y);
	int GetMonth() const;
	int GetDay() const;
	int GetYear() const;
	bool SetFormat(char f);
	void Increment(int numDays = 1);
	int Compare(const Date& d);

private:
	int day;
	int month;
	int year;
	char format;
	bool InputCheck(int m, int d, int y);
	int MonthDays(int m, int y) const;
};
