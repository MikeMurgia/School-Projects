//Michael Murgia
//Section 8
//programming assignment #6
//Due Date: 4/12/24
//
//

#include "studentlist.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	StudentList list;
	
	char choice;

	do
	{
		cout << "*** Student List menu ***\n";
		cout << "I\tImport students from a file\n";
		cout << "S\tShow student list (brief)\n";
		cout << "E\tExport a grade report (to file)\n";
		cout << "M\tShow this Menu\n";
		cout << "Q\tQuit Program\n";
		cout << "> ";
		cin >> choice;
		cin.ignore();

		switch (tolower(choice))
		{
			case 'i':
				char file1[31];
				cout << "Enter filename: ";
				cin.getline(file1, 31);
				if (list.ImportFile(file1))
					cout << "file imported successfully\n";
				else
					cout << "Invalid file. No data imported\n";
				break;
			case 's':
				list.ShowList();
				break;
			case 'e':
				char file2[31];
				cout << "Enter filename: ";
				cin.getline(file2, 31);
				if (list.CreateReportFile(file2))
					cout << "Grade report exported\n";
				else
					cout << "Failed to export\n";
				break;
			case 'm':
				break;
			case 'q':
				cout<< "Goodbye!\n";
				break;
			default:
				cout << "Invalid choice. Try again\n";
				break;
		}
	} while (tolower(choice) != 'q');


	return 0;
}
