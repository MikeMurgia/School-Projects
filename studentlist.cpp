//Michael Murgia
//Section 8
//Programming Assignment #6
//Due Date: 4/12/24

#include "studentlist.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<string>

using namespace std;


Student::Student(const string& firstname, const string& lastname, const string& course)
	: firstname(firstname), lastname(lastname), course(course) {}

char Student::ComputeLet() const
{
	double avg = ComputeAvg();
	if (avg >= 90.0) return 'A';
	else if (avg >= 80.0) return 'B';
	else if (avg >= 70.0) return 'C';
	else if (avg >= 60.0) return 'D';
	else return 'F';
}



EnglishStudent::EnglishStudent(const string& fName, const string& lName, const string& course, int att, int proj, int mid, int fin)
	: Student(fName, lName, "English") , att(att), proj(proj), mid(mid), fin(fin) {}

double EnglishStudent::ComputeAvg() const
{
	return 0.1 * att + 0.3 * proj + 0.3 * mid + 0.3 * fin;
}

HistoryStudent::HistoryStudent(const string& fName, const string& lName, const string& course, int termp, int midt, int fina)
	: Student(fName, lName, "History"), term(termp), mid(midt), fin(fina) {}

double HistoryStudent::ComputeAvg() const
{
	return 0.25 * term + 0.35 * mid + 0.4 * fin;
}

MathStudent::MathStudent(const string& fName, const string& lName, const string& course, double q1, double q2, double q3, double q4, double q5, int t1, int t2, int fina)
	: Student(fName, lName, "Math"), quiz1(q1), quiz2(q2), quiz3(q3), quiz4(q4), quiz5(q5), test1(t1), test2(t2), fin(fina) {}

double MathStudent::ComputeAvg() const
{
	double quizAvg = (quiz1 + quiz2 + quiz3 + quiz4 + quiz5)/5.0;
	return 0.15 * quizAvg + 0.25 * test1 + 0.25 * test2 + 0.35 * fin;
}

StudentList::StudentList() : students(nullptr), numStu(0), maxStu(0) {}

StudentList::~StudentList()
{
	for(int i = 0; i < numStu; i++)
		delete students[i];
	delete[] students;
}

bool StudentList::ImportFile(const char* filename)
{
	
	ifstream file(filename);
	if (!file.is_open())
		return false;
	int numRecords;
	file >> numRecords;
	file.ignore();

	students = new Student*[numRecords];
	for(int i =0; i < numRecords; i++)
	{
		string fName, lName;
		getline(file, lName, ',');
		getline(file, fName);

		string course;
		file >> course;

		if(course == "English")
		{
			int att, proj, mid, fin;
			file >> att >> proj >> mid >> fin;
			file.ignore();
			students[i] = new EnglishStudent(fName, lName, "English", att, proj, mid, fin);
		}
		else if(course == "History") 
		{
			int term, mid, fin;
			file >> term >> mid >> fin;
			file.ignore();
			students[i] = new HistoryStudent(fName, lName, "History", term, mid, fin);
		}
		else if (course == "Math")
		{
			double quiz1, quiz2, quiz3, quiz4, quiz5;
			int test1, test2, fin;
			file >> quiz1 >> quiz2 >> quiz3 >> quiz4 >> quiz5 >> test1 >> test2 >> fin;
			file.ignore();
			students[i] = new MathStudent(fName, lName, "Math", quiz1, quiz2, quiz3, quiz4, quiz5, test1, test2, fin);
		}
		/*
		if(numStu == maxStu)
		{
			maxStu = maxStu + 3;
			Student** temp = new Student*[maxStu];
			for(int i = 0; i < numStu; i++)
				temp[i] = students[i];
			delete[] students;
			students = temp;
		}*/
	}
	numStu = numRecords;
	file.close();
	return true;
}

bool StudentList::CreateReportFile(const char* filename)
{
	ofstream file;
	file.clear();
	file.open(filename);
	if(!file)
		return false;

	file << "Student Grade Summary\n---------------------\n\n";
	file << "ENGLISH CLASS\n\nStudent\t\t\t\t\tFinal\tFinal\tLetter\n";
	file << "Name\t\t\t\t\tExam\tAvg\tGrade\n";
	file << "----------------------------------------------------------------------\n";

	for(int i = 0; i < numStu; i++)
	{
		if(students[i]->getCourse() == "English")
		{
                        file << setw(42) << left << (students[i]->getFirstname() + " " + students[i]->getLastname());
			file << left << setw(6) << static_cast<int>(students[i]->getFinalExam());
			file << setw(8) << fixed << setprecision(2) << students[i]->ComputeAvg();
			file << setw(8) << students[i]->ComputeLet() << "\n";
		}
	}
	file << "\n\n\nHISTORY CLASS\n\nStudent\t\t\t\t\tFinal\tFinal\tLetter\n";
        file << "Name\t\t\t\t\tExam\tAvg\tGrade\n";
        file << "----------------------------------------------------------------------\n";

	for(int i = 0; i < numStu; i++)
	{
		if(students[i]->getCourse() == "History")
		{
                        file << setw(42) << left << (students[i]->getFirstname() + " " + students[i]->getLastname());
                        file << left << setw(6) << static_cast<int>(students[i]->getFinalExam());
                        file << setw(8) << fixed << setprecision(2) << students[i]->ComputeAvg();
                        file << setw(8) << students[i]->ComputeLet() << "\n";
		}

	}
        file << "\n\n\nMath CLASS\n\nStudent\t\t\t\t\tFinal\tFinal\tLetter\n";
        file << "Name\t\t\t\t\tExam\tAvg\tGrade\n";
        file << "----------------------------------------------------------------------\n";

        for(int i = 0; i < numStu; i++)
        {
                if(students[i]->getCourse() == "Math")
                {
                        file << setw(42) << left << (students[i]->getFirstname() + " " + students[i]->getLastname());
                        file << left << setw(6) << static_cast<int>(students[i]->getFinalExam());
                        file << setw(8) << fixed << setprecision(2) << students[i]->ComputeAvg();
                        file << setw(8) << students[i]->ComputeLet() << "\n";
                }

        }
	

	file << "\n\nOVERALL GRADE DISTRIBUTION\n\n";
	int grade[5] = {0};
	for (int i = 0; i < numStu; i++)
	{
		double finalAvg = students[i]->ComputeAvg();
		if (finalAvg >= 90)
			grade[0]++;
		else if (finalAvg >= 80)
			grade[1]++;
		else if (finalAvg >= 70)
			grade[2]++;
		else if (finalAvg >= 60)
			grade[3]++;
		else
			grade[4]++;
	}

	file << "A:   " << grade[0] << "\n";
	file << "B:   " << grade[1] << "\n";
	file << "C:   " << grade[2] << "\n";
	file << "D:   " << grade[3] << "\n";
	file << "F:   " << grade[4] << "\n";


	file.close();
	return true;
}

void StudentList::ShowList() const
{
	cout << "Last\t\t\tFirst\t\t\tCourse\n\n";
	for (int i = 0; i < numStu; i++)
	{
		cout << left << setw(20) << students[i]->getLastname();
		cout << left << setw(20) << students[i]->getFirstname();
		cout << students[i]->getCourse() << "\n";
	}
	cout << "\n";
}


