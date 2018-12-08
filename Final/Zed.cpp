#include"Zed.h"

Zed::Zed(const Point& head)//constructorshape
{
	body[0] = head; //body is a point array, body[0] reference for the upper left corner of the shape in default orientation.
	body[1] = head.right();
	body[2] = body[1].down();
	body[3] = body[2].right();
	c = '*';
	shapeColor = BROWN;
}
