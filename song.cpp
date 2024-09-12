//Michael Murgia
//Programming Assignment #4
//March 7, 2024
//song.cpp

#include "song.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>

using namespace std;

Song::Song()
{
	title[0] = '\0';
	artist[0] = '\0';
	category = POP;
	size = 0;
}

void Song::Set(const char* t, const char* a, Style c, int s)
{
	strncpy(title, t, 35);
	strncpy(artist, a, 20);
	category = c;
	size = s;
}

const char* Song::GetTitle() const
{	return title;	}

const char* Song::GetArtist() const
{	return artist;	}

int Song::GetSize() const
{	return size;	}

Style Song::GetCategory() const
{	return category;}

ostream& operator<<(ostream& os, const Song& s)
{
	os 	<< s.title << " ";
	for (int i = strlen(s.title); i < 35; i++)
		os.put(' '); 
	os	<< setw(20) << left << s.artist << " ";
	
	
	if (s.category == POP)
		os << setw(12) << left << "Pop ";
	else if (s.category == ROCK)
		os << setw(12) << left << "Rock ";
	else if (s.category == ALTERNATIVE)
		os << setw(12) << left << "Alt ";
	else if (s.category == COUNTRY)
		os << setw(12) << left << "Ctry ";
	else if (s.category == HIPHOP)
		os << setw(12) << left << "HH ";
	else if (s.category == PARODY)
		os << setw(12) << left << "Par ";
	
	os	<< std::setw(7) << right << fixed << setprecision(2) << s.size / 1000.00 << endl;
	return os;
}
