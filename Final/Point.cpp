#include "Point.h"

void Point::changeDir(Direction dir)
{
	switch (dir)
	{
	case Direction::LEFT:
		dir_x = -1;
		dir_y = 0;
		break;
	case Direction::RIGHT:
		dir_x = 1;
		dir_y = 0;
		break;
	case Direction::UP:
		dir_x = 0;
		dir_y = 0;
		break;
	case Direction::DOWN:
		dir_x = 0;
		dir_y = 1;
		break;
	case Direction::STAY:
		dir_x = 0;
		dir_y = 0;
		break;
	}
}

void Point::getXY(int& x, int &y) {
	x = this->x;
	y = this->y;
}

void Point::setXYChange(int _x, int _y)
{
	this->x += _x;
	this->y += _y;
}

void Point::rotateRightALG(int cx, int cy)
{
	//we get x,y as Point
	int tmpx = x - cx;
	int tmpy = y - cy;

	int vxnew = ((-1)*tmpy);
	int vynew = ((1)*tmpx);

	this->setX(cx + vxnew);
	this->setY(cy + vynew);

}




