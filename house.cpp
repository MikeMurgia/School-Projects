//Michael Murgia
//Section 8
//Due Date: Jan 30, 2024
//Programming Assignment #1
///////////////////////////


#include <iostream>
#include <iomanip>
#include <cmath>
#include "house.h"

using namespace std;

House::House(int s, char b, char f)
{
	fill = f;
	bord = b;
	size = s;
	if (size < 3)
		size = 3;
	if (size > 37)
		size = 37;
}

int House::GetSize() const
{
	return size;
}

int House::Perimeter() const
{
	int perRoof = (size + 2) * 2 + 2;
	int perBox = size * 3;
	return perRoof + perBox;
}

double House::Area() const
{
	double areaRoof = (size + 2)*(size + 2)*((sqrt(3))/4);	//needed double variable
	int areaBox = size * size;
	return (areaBox + areaRoof);
}

void House::Grow()
{
	if (size < 37)
		size++;
}

void House::Shrink()
{
	if (size > 3)
		size--;
}

void House::SetBorder(char newBord)
{
	if (newBord >= '!' && newBord <= '~')
	{
		bord = newBord;
	}
	else
	{
		bord = 'X';
	}
}

void House::SetFill(char newFill)
{
	if (newFill >= '!' && newFill <= '~')
	{
		fill = newFill;
	}
	else
	{
		fill = '*';
	}
}

void House::Draw() const
{
	// triangle / roof
	for (int i = 0; i < (size + 2); i++)			//determines rows
	{	
		for (int j = 0; j < (size - i + 1); j++)	//determines space on each row
		{
			cout << " ";
		}
		if (i == 0)					// when no filler is needed
		{
			cout << bord;
			cout << "\n";
		}
		if (i == 1)					// ^^^
		{
			cout << bord << " " << bord << "\n";
		}
		if (i > 1 && i < (size + 1))			// used for filler lines up to edge of roof
		{
			cout << bord;
			for (int k = 0; k < (i - 1); k++ )
			{
				cout << " " << fill;
			}
			cout << " " << bord << "\n";
		}
		if (i == size + 1)				// used for edge of roof line
		{
			cout << bord << " " << bord << " ";
			for (int h = (size - 2); h > 0; h--)
			{
				cout << fill << " ";
			}
			cout << bord << " " << bord << "\n"; 
		}
	}

	// building / square
	for (int i = (size); i > 0; i--)			//determines amount of rows
	{
		if (i > 2)					//needed for fill lines 
		{
			cout << "  " << bord;
			for (int j = (size - 2); j > 0; j--)
			{
				cout << " " << fill;
			}
			cout << " " << bord;
			cout << "\n";
		}
		if (i < 2)					//border lines
		{
			cout << "  " << bord;
			for (int k = (size - 1); k > 0; k--)
			{
				cout << " " << bord;
			}
			cout << "\n";
		}
	}
}

void House::Summary() const
{
	cout << "House width and height base to roof = " << size << " units." << endl;
	cout << "Perimeter of house = " << Perimeter() << " units." << endl;
	cout << "Area of house = " << std::fixed << std::setprecision(2) << Area() << " units." << endl;
	cout << "House looks like: \n";
	Draw();
}
