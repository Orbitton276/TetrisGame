#include "Rotatable.h"

bool RotatableShape::move(Board &gameBoard, char keyPressed, bool &GameOver, int &bombModifier)
{
	Direction dir = getDir(keyPressed);
	Point bodyCpy[4];
	bool flag = false;
	bool newFixedShape = false;
	DEL_FROM_SCR
		for (int i = 0; i < 4; ++i) {
			bodyCpy[i] = body[i];
		}
	if (ROTATE_REQUEST)
	{
		rotateRight();
	}
	else
	{
		for (auto& p : body) {
			p.move(dir);
		}
	}

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

bool RotatableShape::checkRestrictions(Board& gameBoard, Point* bodyCpy, Direction dir, bool &newFixedShape, bool &ifGameOver)
{
	int x, y;
	bool shapeCollisionBottom, borderCollisionBottom;
	shapeCollisionBottom = borderCollisionBottom = false;
	bool shapeCollisionSides, borderCollisionSides;
	shapeCollisionSides = borderCollisionSides = false;
	if (dir == Direction::DOWN)
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

bool RotatableShape::checkCollisionSides(Board &gameBoard, bool &shapeCollisionSides, bool &borderCollisionSides) {

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

bool RotatableShape::checkCollisionBottom(Board &gameBoard, bool &shapeCollision, bool &lowBorderCollision)
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

void RotatableShape::rotateRight() {
	int x, y;
	body[2].getXY(x, y);

	for (auto& p : body) {
		p.rotateRightALG(x, y);
	}
	checkBordersAndCorrect();
}

void RotatableShape::checkBordersAndCorrect() {
	int maxX, minX, maxY, minY;

	getMinMaxPointValues(maxX, minX, maxY, minY);
	bool flag = true;
	if (maxX > 10)
	{
		for (auto& p : body) {
			p.setXYChange((10 - maxX), 0);
		}
	}
	else if (minY < 4)
	{
		for (auto& p : body) {
			p.setXYChange(0, 1);
		}
	}
	else if (minX < 1) {
		for (auto& p : body) {
			p.setXYChange(((minX*(-1)) + 1), 0);
		}
	}
	else if (maxY>18) {
		for (auto& p : body) {
			p.setXYChange(0, (18 - maxY));
		}

	}
}

