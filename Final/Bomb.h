#pragma once
#include "Shapes.h"
#include "Game.h"


class Bomb :public Shape {
public:
	Bomb(const Point& head);
	virtual ~Bomb() {};
	virtual bool move(Board &gameBoard, char keyPressed, bool &GameOver, int &bombModifier);
	virtual bool checkCollisionBottom(Board &gameBoard, bool &shapeCollision, bool &lowBorderCollision);
	virtual bool checkCollisionSides(Board &gameBoard, bool &shapeCollisionSides, bool &borderCollisionSides);
	virtual bool checkRestrictions(Board& gameBoard, Point* bodyCpy, Direction dir, bool &newFixedShape, bool &ifGameOver);
	void manageBomb(Board &gameBoard, int &blowedPixles);
	void getRangeForBomb(int &leftBorder, int &rightBorder, int &upperBorder, int &bottomBorder);
};


