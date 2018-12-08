#include "BigL.h"

BigL::BigL(const Point& head) {//constructor
	body[0] = head; //body is a point array, body[0] reference for the upper left corner of the shape in default orientation.
	body[1] = head.down();
	body[2] = body[1].right();
	body[3] = body[2].right();
	c = '*';
	shapeColor = CYAN;
}






