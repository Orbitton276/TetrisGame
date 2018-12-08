#pragma once
#include "Shapes.h"
class rotatableShape :
	public Shape
{
public:
	enum Orientation { DEFAULT, FIRST_TURN, SECOND_TURN, THIRD_TURN };
protected:
	Orientation mode = DEFAULT;
public:
	virtual ~rotatableShape() {};
	virtual void rotateRight() = 0;
	Direction getDir(char keyPressed);
	bool move(Board &gameBoard, char keyPressed, bool &GameOver, int &bombModifier);
	bool checkCollisionBottom(Board &gameBoard, bool &shapeCollision, bool &lowBorderCollision); //when implementing joker, we will add the relevant condition.
	bool checkCollisionSides(Board &gameBoard, bool &shapeCollisionSides, bool &borderCollisionSides);
	bool checkRestrictions(Board& gameBoard, Point* bodyCpy, Direction dir, bool &newFixedShape, bool &ifGameOver); //different implementation for joker and rotatable shapes
	rotatableShape::Orientation getPrevOrient();
};

