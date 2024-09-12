//Michael Murgia
//Programming Assignment #4
//Due Date: 3/7/24
//playlist.cpp
//

#include<iostream>
#include<iomanip>
#include<cstring>
#include<cctype>
#include "playlist.h"
using namespace std;

Playlist::Playlist()
{
	maxSize = SIZE;
	songs = new Song[maxSize];
	currentSize = 0;
}

Playlist::~Playlist()
{
	delete[] songs;
}

Playlist::Playlist(const Playlist & p)
{
	maxSize = p.maxSize;
	currentSize = p.currentSize;
	songs = new Song[maxSize];
	for (int i = 0; i < currentSize; i++)
		songs[i] = p.songs[i];
}

Playlist& Playlist::operator= (const Playlist & p)
{
	if (this != &p)
	{
		delete[] songs;

		maxSize = p.maxSize;
		currentSize = p.currentSize;
		songs = new Song[maxSize];
		for (int i = 0; i < currentSize; i++)
			songs[i] = p.songs[i];
	}
	return *this;
}

void Playlist::addSong(const char* t, const char* a, Style c, int s)
{
	if (currentSize == maxSize)
	{
		update();
	}
	Song s1;
	s1.Set(t, a, c, s);
	songs[currentSize] = s1;
	currentSize = currentSize + 1;
}

void Playlist::delSong(const char* t)
{
	int index = findSong(t);
	if (index != -1)
	{
		for (int i = index; i < currentSize - 1; i++)
			songs[i] = songs[i + 1];
		currentSize--;
	}
	else
	{
		cout << "Song not found in the playlist." << endl;
	}
		

}

void Playlist::Lookup(const char* t)
{
	int index = findSong(t);
	if (index != -1)
	{
		cout << "Song Found: \n";
		cout << songs[index]; 
	}
	else
	{
		int tracker = 0;
		findSongbyA(t, tracker);
		if (tracker == 0)
			cout << t << " not found\n";
	}
	
}

void Playlist::showSong() const
{
	cout << "Title		                    Artist	         Style     Size (MB)" << endl;
	for (int i = 0; i < currentSize; i++)
		cout << songs[i];

}

void Playlist::update()
{
	int newSize = maxSize + 5;
	Song* temp = new Song[newSize];
	for (int i = 0; i < currentSize; i++)
		temp[i] = songs[i];
	delete[] songs;
	songs = temp;
	maxSize = newSize;
}

int Playlist::findSong(const char* t) const 
{
	for (int i = 0; i < currentSize; i++)
	{
		if (strcmp(songs[i].GetTitle(), t) == 0)
		{
			return i;
		}
	}
	return -1;
}

void Playlist::findSongbyA(const char* t, int& track) const
{
	for (int i = 0; i < currentSize; i++)
	{
		if (strcmp(songs[i].GetArtist(), t) == 0)
		{	
			if (track = 0)
				cout << "Song found: \n";
			track = track + 1;
			cout << songs[i];
		}
	}

}

void Playlist::categoryTotals(Style c)
{
	double catTotal = 0.00;
	for (int i = 0; i < currentSize; i++)
	{
		if (songs[i].GetCategory() == c)
		{
			cout << songs[i];
			catTotal = songs[i].GetSize() + catTotal;
		}
	}	
	catTotal = catTotal / 1000;
	cout << "Total size: " << fixed << setprecision(2) << catTotal << "MB" << endl;
}

void Playlist::fileSize()
{
	int total = 0;
	for (int i = 0; i < currentSize; i++)
		total = total + songs[i].GetSize();
	cout << "Total file size: " << total << " KB" << endl;
}
