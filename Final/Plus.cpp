#include"Plus.h"

Plus::Plus(const Point& head)//constructorshape
{
	body[0] = head; //body is a point array, body[0] reference for the upper left corner of the shape in default orientation.
	body[2] = body[0].down();
	body[1] = body[2].left();
	body[3] = body[2].right();
	c = '*';
	shapeColor = MAGENTA;

}
