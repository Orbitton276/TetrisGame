#pragma once
#include "Shapes.h"

class Square :public Shape {
public:
	Square(const Point& head);
	virtual ~Square() {};
	virtual bool move(Board &gameBoard, char keyPressed, bool &GameOver, int &bombModifier);
	virtual bool checkCollisionBottom(Board &gameBoard, bool &shapeCollision, bool &lowBorderCollision);
	virtual bool checkCollisionSides(Board &gameBoard, bool &shapeCollisionSides, bool &borderCollisionSides);
	virtual bool checkRestrictions(Board& gameBoard, Point* bodyCpy, Direction dir, bool &newFixedShape, bool &ifGameOver);

};


