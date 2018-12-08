#pragma once
#include "Point.h"
//#include "Game.h"
#include "Defines.h"
#include "Board.h"
#include "Utilities.h"

class Shape {
protected:
	Point body[4];
	char c;
	char dirKeys[5] = { 'a','d','x','w','s' };
	colors shapeColor;
public:
	virtual ~Shape() {};
	virtual Direction getDir(char keyPressed);
	virtual bool move(Board &gameBoard, char keyPressed, bool &GameOver, int &bombModifier) = 0;
	virtual bool checkCollisionBottom(Board &gameBoard, bool &shapeCollision, bool &lowBorderCollision) = 0;
	virtual bool checkCollisionSides(Board &gameBoard, bool &shapeCollisionSides, bool &borderCollisionSides) = 0;
	virtual bool checkRestrictions(Board& gameBoard, Point* bodyCpy, Direction dir, bool &newFixedShape, bool &ifGameOver) = 0;

	void draw(char ch, colors color);
	char getSign();
	colors getShapeColor();
	void setShapeColor(int shapeColor);
	void getMinMaxPointValues(int &max_x, int &min_x, int &max_y, int &min_y);
	void updateBoard(Board &gameBoard, int colorNum);

};


