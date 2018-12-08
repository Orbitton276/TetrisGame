#pragma once

#include "Utilities.h"
#include "Gotoxy.h"


using namespace std;

class Point {
	int x;
	int y;
	int dir_x = 1;
	int dir_y = 0;

	void moveImp() {
		x = (x + dir_x);
		y = (y + dir_y);
	}
	//need to implement borders of dots drawing according to board size.
public:
	enum eKeys { LEFT = 'a', RIGHT = 'd', DOWN = 'x', UP = 'w', STAY = 's', START_GAME = '1', PAUSE_RESUME = '2', SPEED_UP = '3', SPEED_DOWN = '4', EXIT = '9' };
	Point(int x1 = 0, int y1 = 0)//Constructor of point according to int values received.
	{
		x = x1;
		y = y1;
	}
	void draw(char c = '*')const
	{
		gotoxy(x, y);
		cout << c;
		cout.flush();
	}

	Point right() const {
		return Point(x + 1, y);
	}//a function that returns another point object to the right of the original in order to create a shape, according to shape class.
	Point down() const {
		return Point(x, y + 1);
	}//a function that returns another point object to the left of the original in order to create a shape, according to shape class.
	Point up() const {
		return Point(x, y - 1);
	}
	Point left() const {
		return Point(x - 1, y);
	}
	void move(Direction dir)
	{
		changeDir(dir);
		moveImp();
	}
	void changeDir(Direction dir);
	void getXY(int& x, int &y);
	void setXYChange(int _x, int _y);



	void rotateRightALG(int cx, int cy);

	inline void setX(int x) { this->x = x; }
	inline void setY(int y) { this->y = y; }
};