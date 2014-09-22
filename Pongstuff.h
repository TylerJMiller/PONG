#ifndef IOSTREAM
#include <iostream>
using namespace std;
#endif
#include <fstream>

class Vector		//VECTOR CLASS
{
private:
	float x;
	float y;
public:
	//DECLARING DEFAULTS AND OVERLOADS
	Vector();
	Vector(float, float);
	void Set(float ax, float ay)
	{
		x = ax;
		y = ay;
	}

	//GETTING VALUES
	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}
	float Length()
	{
		return sqrt((x * x) + (y * y));
	}
};

Vector::Vector(float ax, float ay)		//VECTOR CONSTRUCTOR
{
	x = ax;
	y = ay;
}

class Point		//POINT CLASS
{
private:
	float x;
	float y;
public:
	//CONSTRUCTORS
	Point();
	Point(float, float);
	//SETTING VALUES
	void Set(float ax, float ay)
	{
		x = ax;
		y = ay;
	}
	//GETTING VALUES
	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}
};

Point::Point(float ax, float ay)		//POINT CONSTRUCTOR
{
	x = ax;
	y = ay;
}

class Line		//LINE CLASS
{
private:
	float X1;
	float Y1;
	float X2;
	float Y2;
public:
	//CONSTRUCTORS
	Line();
	Line(Point, Point);
	//SETTING VALUES
	void Set(float startx, float starty, float endx, float endy)
	{
		X1 = startx;
		Y1 = starty;
		X2 = endx;
		Y2 = endy;
	}
	void Set(Point a_point1, Point a_point2)//SET OVERLOAD USING POINT CLASS
	{
		X1 = a_point1.GetX();
		Y1 = a_point1.GetY();
		X2 = a_point2.GetX();
		Y2 = a_point2.GetY();
	}
	//GETTING VALUES
	float GetLength()
	{
		return (((X2 - X1) * (X2 - X1)) + ((Y2 - Y1) * (Y2 - Y1)));
	}
	float GetLengthX()
	{
		return (X2 - X1);
	}
	float GetLengthY()
	{
		return (Y2 - Y1);
	}
	Vector GetVector()//GETTING LINE AS VECTOR (FOR SOME REASON)
	{
		Vector v(GetLengthX(), GetLengthY());
		return v;
	}
};

Line::Line(Point a_point1, Point a_point2)		//LINE CONSTRUCTOR
{
	X1 = a_point1.GetX();
	Y1 = a_point1.GetY();
	X2 = a_point2.GetX();
	Y2 = a_point2.GetY();
}


class Box		//BOX CLASS
{
private:
	float X1;
	float Y1;
	float X2;
	float Y2;
public:
	//CONSTRUCTORS
	Box();
	Box(Point, Point);
	Box(float, float, float, float);
	//SETTING VALUES
	void Set(float ax, float ay, float ax2, float ay2)
	{
		X1 = ax;
		Y1 = ay;
		X2 = ax2;
		Y2 = ay2;
	}
	void Set(Point p1, Point p2) //SET OVERLOAD USING POINTS
	{
		X1 = p1.GetX();
		Y1 = p1.GetY();
		X2 = p2.GetX();
		Y2 = p2.GetY();
	}
	//GETTING VALUES
	Point GetLeftBot()
	{
		Point p(X1, Y1);
		return p;
	}
	Point GetLeftTop()
	{
		Point p(X1, Y2);
		return p;
	}
	Point GetRightBot()
	{
		Point p(X2, Y1);
		return p;
	}
	Point GetRightTop()
	{
		Point p(X2, Y2);
		return p;
	}
	Line GetBotLine()
	{
		Line l(GetLeftBot(), GetRightBot());
		return l;
	}
	Line GetRightLine()
	{
		Line l(GetRightBot(), GetRightTop());
		return l;
	}
	Line GetTopLine()
	{
		Line l(GetRightTop(), GetLeftTop());
		return l;
	}
	Line GetLeftLine()
	{
		Line l(GetLeftTop(), GetLeftBot());
		return l;
	}
};
		//BOX CONSTRUCTORS
Box::Box(Point p1, Point p2)	//SET WITH POINT CLASS
{
	X1 = p1.GetX();
	Y1 = p1.GetY();
	X2 = p2.GetX();
	Y2 = p2.GetY();
}
Box::Box(float ax1, float ay1, float ax2, float ay2)		//SET WITH FLOATS
{
	X1 = ax1;
	Y1 = ay1;
	X2 = ax2;
	Y2 = ay2;
}

float Dot(Vector a, Vector b)		//DOT PRODUCT OF TWO VECTORS
{
	return ((a.GetX() * b.GetX()) + (a.GetY() * b.GetY()));
}

bool CheckPointBox(Point p, Box b)		//POINT-BOX COLLISION
{
	if (p.GetX() > b.GetLeftBot().GetX() && p.GetX() < b.GetRightTop().GetX() && p.GetY() > b.GetLeftBot().GetY() && p.GetY() < b.GetRightTop().GetY())
		return true;
	return false;
}

bool CheckLineLine(Line l1, Line l2)				//NOT DONE YET BECAUSE I STOOPUD
{
	return false;
}

bool CheckBoxBox(Box b1, Box b2)		//BOX-BOX COLLISION - ONLY CHECKS POINTS NOT LINES
{
	if (CheckPointBox(b1.GetLeftBot(), b2) || CheckPointBox(b1.GetRightBot(), b2) || CheckPointBox(b1.GetRightTop(), b2) || CheckPointBox(b1.GetLeftTop(), b2))
		return true;
	return false;
}

//PLAYERS CLASS
class PLAYERBAR
{
private:
	float x, y, speed, height, width, leftbound, rightbound;
	unsigned int sprite, moveLeft, moveRight;
public:
	void SetBound(float al, float ar)//SETTING X BOUNDARIES
	{
		leftbound = al;
		rightbound = ar;
	}
	void SetKeys(unsigned int aleft, unsigned int aright)//SETTING X MOVEMENT KEYS
	{
		moveLeft = aleft;
		moveRight = aright;
	}
	float GetWidth()//GETTING SPRITE/COLLISION WIDTH
	{
		return width;
	}
	float GetHeight()//GETTING SPRITE/COLLISION HEIGHT
	{
		return height;
	}
	void SetSize(float awidth, float aheight)//SETTING SIZE
	{
		height = aheight;
		width = awidth;
	}
	void SetSprite(unsigned int asprite)//SETTING SPRITE ID
	{
		sprite = asprite;
	}
	unsigned int GetSprite()//GETTING SPRITE ID
	{
		return sprite;
	}
	float GetX()//GETTING X LOCATION
	{
		return x;
	}
	float GetY()//GETTING Y LOCATION
	{
		return y;
	}
	void SetLoc(float ax, float ay)//SETTING LOCATION
	{
		x = ax;
		y = ay;
	}
	void SetSpeed(float a)//SETTING X SPEED
	{
		speed = a;
	}
	void Move(float aTime)//MOVEMENT LOGIC
	{
		if (IsKeyDown(moveLeft) && x > leftbound)
			x -= (speed * aTime);
		if (IsKeyDown(moveRight) && x < rightbound)
			x += (speed * aTime);
	}
	Box GetBox()//GETTING BOX FOR COLLISION
	{
		Box b(x - (.5f * width), y - (.5f * height), x + (.5f * width), y + (.5f * height));
		return b;
	}
};

//BALL CLASS
class BALL
{
private:
	float x, y, height, width, speedx, speedy, leftbound, rightbound;
	unsigned int sprite;
public:
	float GetWidth()//GETTING SPRITE/COLLISION WIDTH
	{
		return width;
	}
	float GetHeight()//GETTING SPRITE/COLLISION HEIGHT
	{
		return height;
	}
	void SetSize(float awidth, float aheight)//SETTING SPRITE/COLLISION SIZE
	{
		height = aheight;
		width = awidth;
	}
	void SetSprite(unsigned int asprite)//SETTING SPRITE ID
	{
		sprite = asprite;
	}
	unsigned int GetSprite()//GETTING SPRITE ID
	{
		return sprite;
	}
	void SetBound(float al, float ar)//SETTING X MOVEMENT BOUNDARIES
	{
		leftbound = al;
		rightbound = ar;
	}
	float GetX()//GETTING X LOCATION
	{
		return x;
	}
	float GetY()//GETTING Y LOCATION
	{
		return y;
	}
	void SetLoc(float ax, float ay)//SETTING LOCATION
	{
		x = ax;
		y = ay;
	}
	void SetSpeed(float ax, float ay)//SETTING SPEED
	{
		speedx = ax;
		speedy = ay;
	}
	Vector GetSpeed()//GETTING SPEED AS VECTOR
	{
		Vector va(speedx, speedy);
		return va;
	}
	void Reverse()//REVERSING DIRECTION AND INCREASING SPEED
	{
		speedy *= -1.05;
		speedx *= 1.05;
	}
	float GetSpeedY()//GETTING Y SPEED
	{
		return speedy;
	}
	float LengthSpeed()//HOW MUCH IT MOVES AT THE CURRENT SPEED - USED FOR HIGH SCORE
	{
		return GetSpeed().Length();
	}
	Box GetBox()//RETURNS A BOX CLASS WITH FOUR FLOATS
	{
		Box b(x - (.5f * width), y - (.5f * height), x + (.5f * width), y + (.5f * height));
		return b;
	}
	void Move(float atime)//MOVE FUNCTION WITH MAX/MIN X
	{

		x += (speedx * atime);
		y += (speedy * atime);
		if ((x + (speedx * atime)) <= leftbound || (x + (speedx * atime)) >= rightbound)
		{
			speedx *= -1;
		}
	}
};
//FILE I/O
void Write(char writeme)//WRITING
{
	fstream fscores;
	fscores.open("fscores.txt", ios_base::out);
	fscores << writeme << " " << endl;
	fscores.close();
}

void Write(char *writeme)//WRITING OVERLOAD
{
	fstream fscores;
	fscores.open("fscores.txt", ios_base::out);
	fscores << writeme << " " << endl;
	fscores.close();
}
void WriteOld(float writeme)//WRITING OLD SCORE
{
	fstream fscores;
	fscores.open("foldscores.txt", ios_base::out);
	fscores << writeme << " " << endl;
	fscores.close();
}

char *Read()//READING AS CHAR
{
	char ca[6];
	fstream fscores;
	fscores.open("fscores.txt", ios_base::in);
	fscores.getline(ca, 6);
	fscores.close();
	return ca;
}

float ReadAsFloat()//READING AS FLOAT
{
	char ca[6];
	float fa;
	fstream fscores;
	fscores.open("fscores.txt", ios_base::in);
	fscores.getline(ca,6);
	fscores.close();
	fa = atoi(ca);
	return fa;
}