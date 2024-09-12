//Michael Murgia
//Section 8
//Due Date: Jan 30, 2024
//Programming Assignment #1
///////////////////////////

class House
{
public:

	House(int s, char b = 'X', char f = '*');

	int GetSize() const;	
	int Perimeter() const;
	double Area() const;
	void Grow();
	void Shrink();
	void SetBorder(char newBord);
	void SetFill(char newFill);

	void Draw() const;
	void Summary() const;

private:
	int size;
	char bord;
	char fill;
};
