#include "Square.h"
#include "Defines.h"
#include "Game.h"

Square::Square(const Point& head)//constructorshape
{
	body[0] = head; //body is a point array, body[0] reference for the upper left corner of the shape in default orientation.
	body[1] = head.right();
	body[2] = head.down();
	body[3] = body[2].right();
	c = '*';
	shapeColor = GREEN;
}

bool Square::move(Board &gameBoard, char keyPressed, bool &GameOver, int &bombModifier)
{
	Direction dir = getDir(keyPressed);
	Point bodyCpy[4];
	bool newFixedShape = false;
	DEL_FROM_SCR
		for (int i = 0; i < 4; ++i) {
			bodyCpy[i] = body[i];
		}
	for (auto& p : body) {//saving the upcoming location according to dir (According to key pressed)
		p.move(dir);
	}//UPDATE NEW COORDINATES

	if (MOVE_IS_VALID)
	{
		draw(c, shapeColor);
	}

	if (GameOver)
	{
		draw(c, shapeColor);
		GAME_OVER;
	}
	else if (newFixedShape == true)
	{
		updateBoard(gameBoard, shapeColor);
		draw(c, shapeColor);
		KILL_SHAPE;
	}
	return true;
}

bool Square::checkRestrictions(Board& gameBoard, Point* bodyCpy, Direction dir, bool &newFixedShape, bool &ifGameOver)
{
	int x, y;
	setShapeColor(GREEN);//dictates the next drawing color according to the current object.
	bool shapeCollisionBottom, borderCollisionBottom;
	shapeCollisionBottom = borderCollisionBottom = false;
	bool shapeCollisionSides, borderCollisionSides;
	shapeCollisionSides = borderCollisionSides = false;

	if (dir == Direction::DOWN)
	{
		if (checkCollisionBottom(gameBoard, shapeCollisionBottom, borderCollisionBottom) == true)
		{
			if (shapeCollisionBottom == true || borderCollisionBottom == true)//if not a joker and collision is true we return to previous location and update board.
			{
				for (int i = 0; i < 4; ++i) {//returning body to original points location.
					body[i] = bodyCpy[i];
				}
				bodyCpy[0].getXY(x, y);
				if (y == 4)
				{
					ifGameOver = true;
					GAME_OVER;
				}
			}
			newFixedShape = true;
			KILL_SHAPE;
		}
	}

	bodyCpy[0].getXY(x, y);//we check if the previous location of the joker was a shape and we re-draw *.

	if (checkCollisionSides(gameBoard, shapeCollisionSides, borderCollisionSides) == true)
	{
		if (shapeCollisionSides == true || borderCollisionSides == true)
		{
			for (int i = 0; i < 4; ++i) {//returning body to original points location.
				body[i] = bodyCpy[i];
			}
		}
	}
	return true;
}

bool Square::checkCollisionSides(Board &gameBoard, bool &shapeCollisionSides, bool &borderCollisionSides) {

	int x, y;
	for (auto& p : body) {
		p.getXY(x, y);
		if (SIDE_LIMIT_REACHED) {
			borderCollisionSides = true;
			return true;
		}
		if (SHAPE_COLLISION) {
			shapeCollisionSides = true;
			return true;
		}
	}
	return false;//if we passed all the tests then side movement is valid and we return false hence no collision.
}

bool Square::checkCollisionBottom(Board &gameBoard, bool &shapeCollision, bool &lowBorderCollision)
{
	int x, y;
	for (auto& p : body) {
		p.getXY(x, y);
		if (LOW_LIMIT_REACHED) {
			lowBorderCollision = true;
			return true;
		}
		else if (SHAPE_COLLISION) {
			shapeCollision = true;
			return true;
		}
	}
	return false;
}
