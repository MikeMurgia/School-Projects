//Michael Murgia
//COP3330
//Assignment #4
//Due Date: 3/7/24
//menu.cpp


#include<iostream>
#include<cstring>
#include<iomanip>
#include<cctype>
#include "playlist.h"

void printMenu()
{
	cout 	<< "\nA: Add a song to the playlist" << endl
		<< "F: Find a song from the playlist" << endl
		<< "D: Delete a song from the playlist" << endl
		<< "S: Show the entire playlist" << endl
		<< "C: Category summary" << endl
		<< "Z: Show playlist size" << endl
		<< "M: Show this Menu" << endl
		<< "X: eXit the program" << endl << "\n";
}

char Input()
{
	char choice;
	cout << "Enter your choice: ";
	cin >> choice;
	return toupper(choice);
}

Style letToCat(char c)
{
	if (c == 'P')
		return POP;
	else if (c == 'R')
		return ROCK;
	else if (c == 'A')
		return ALTERNATIVE;
	else if (c == 'C')
		return COUNTRY;
	else if (c == 'H')
		return HIPHOP;
	else
		return PARODY;
}

void addToPL(Playlist& pl)
{
	
	char title[36];
	char artist[21];
	char cat;
	int size;
	cout << "Enter song title: ";
	cin.ignore();
	cin.getline(title, 36);
	cout << "Enter artist: ";
	cin.getline(artist, 21);
	cout << "Enter category (P, R, A, C, H, Y): ";
	cin >> cat;
	if (cat != 'P' && cat != 'R' && cat != 'A' && cat != 'C' && cat != 'H' && cat != 'Y')
	{
		do
		{
			cout << "Invalid category. Try again: ";
			cin >> cat;

		} while (cat != 'P' && cat != 'R' && cat != 'A' && cat != 'C' && cat != 'H' && cat != 'Y');
	}
	cout << "Enter size (in KB): ";
	cin >> size;
	while (size < 0)
	{
		cout << "Must enter a positize size. Please re-enter: ";
		cin >> size;
	}
	pl.addSong(title, artist, letToCat(cat), size);
}

int main()
{
	Playlist p;
	char choice;

	do
	{
		printMenu();
		choice = Input();
		switch (choice)
		{
			case 'A':
			{
				addToPL(p);
				break;
			}
			case 'F':					// need to find artists too
			{
				char title[35];
				cout << "Find a song: ";
				cin.ignore();
				cin.getline(title, 36);
				p.Lookup(title);				
				break;
			}
			case 'D':
			{
				char title[35];
				cout << "Delete a song: ";
				cin.ignore();
				cin.getline(title, 36);
				p.delSong(title);
				break;
			}
			case 'S':
			{
				p.showSong();				
				break;
			}
			case 'C':
			{
				char cat;
				cout << "Input a category (P, R, A, C, H, Y): ";
				cin >> cat;
				p.categoryTotals(letToCat(cat));
				break;
			}
			case 'Z':
			{
				p.fileSize();
				break;
			}
			case 'M':
			{
				printMenu();
				break;
			}
			case 'X':
			{
				break;
			}
			default:
			{
				cout << "Not a valid option. Try again." << endl;
				break;
			}
		}


	} while (choice != 'X');

	return 0;
}
