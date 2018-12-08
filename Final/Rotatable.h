#pragma once
#include "Shapes.h"
class RotatableShape :
	public Shape
{
public:
	virtual ~RotatableShape() {};
	bool move(Board &gameBoard, char keyPressed, bool &GameOver, int &bombModifier);
	bool checkCollisionBottom(Board &gameBoard, bool &shapeCollision, bool &lowBorderCollision); //when implementing joker, we will add the relevant condition.
	bool checkCollisionSides(Board &gameBoard, bool &shapeCollisionSides, bool &borderCollisionSides);
	bool checkRestrictions(Board& gameBoard, Point* bodyCpy, Direction dir, bool &newFixedShape, bool &ifGameOver);
	void checkBordersAndCorrect();
	void rotateRight();
};


