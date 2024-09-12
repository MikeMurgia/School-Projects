//Michael Murgia
//Section 8
//studentlist.h
//Due Date: 4/12/24

#include<iostream>
#include<string>

using namespace std;


class Student
{
public:
	Student(const string& firstname, const string& lastname, const string& course);

	virtual double ComputeAvg() const = 0;
	virtual char ComputeLet() const;
	virtual int getFinalExam() const = 0;
	const string& getFirstname() const { return firstname; }
	const string& getLastname() const { return lastname; }
	const string& getCourse() const { return course; }

protected:
	string firstname;
	string lastname;
	string course;
};

class EnglishStudent : public Student
{
public:
	EnglishStudent(const string& fName, const string& lName, const string& course, int atte, int proje, int midt, int fina);
	double ComputeAvg() const; 
	int getFinalExam() const {return fin;}

private:
	int att, proj, mid, fin;
};


class HistoryStudent : public Student
{
public:
	HistoryStudent(const string& fName, const string& lName, const string& course, int termp, int midt, int fina);
	double ComputeAvg() const;
	int getFinalExam() const {return fin;}

private:
	int term, mid, fin;
};


class MathStudent : public Student
{
public:
	MathStudent(const string& fName, const string& lName, const string& course, double q1, double q2, double q3, double q4, double q5, int t1, int t2, int fina);
	double ComputeAvg() const;
	int getFinalExam() const {return fin;}

private:
	double quiz1, quiz2, quiz3, quiz4, quiz5;
	int test1, test2, fin;

};


class StudentList
{
public:
	StudentList();
	~StudentList();

	bool ImportFile(const char* filename);
	bool CreateReportFile(const char* filname);
	void ShowList() const;

private:
	Student** students;
	int numStu;
	int maxStu;

};
