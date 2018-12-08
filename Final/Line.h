#pragma once
#include "Rotatable.h"

class Line :public RotatableShape {
public:
	Line(const Point& head);
	~Line() {};
};
