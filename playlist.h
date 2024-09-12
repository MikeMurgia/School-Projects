//Michael Murgia
//Programming Assignment #4
//Due Date: 3/7/24
//playlist.h
//

#include<iostream>
#include "song.h"
using namespace std;


const int SIZE = 5;

class Playlist
{
public:
	Playlist();	
	~Playlist();

	Playlist(const Playlist &);
	Playlist& operator= (const Playlist &);

	void addSong(const char* t, const char* a, Style c, int s);
	void delSong(const char* title);
	void Lookup(const char* title);
	void showSong() const;
	void update();
	void categoryTotals(Style c);
	void fileSize();

private:
	Song* songs;
	int maxSize;
	int currentSize;

	int findSong(const char* title) const; 
	void findSongbyA(const char* t, int& track) const;
};
