#pragma once
#include "Shapes.h"

class Joker :public Shape {

public:
	Joker(const Point& head);
	virtual ~Joker() {};
	virtual Direction getDir(char keyPressed);
	virtual bool move(Board &gameBoard, char keyPressed, bool &GameOver, int &bombModifier);
	virtual bool checkCollisionBottom(Board &gameBoard, bool &shapeCollision, bool &lowBorderCollision);
	virtual bool checkCollisionSides(Board &gameBoard, bool &shapeCollisionSides, bool &borderCollisionSides);
	virtual bool checkRestrictions(Board& gameBoard, Point* bodyCpy, Direction dir, bool &newFixedShape, bool &ifGameOver);

};

