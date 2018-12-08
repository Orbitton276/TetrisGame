#include "Bomb.h"

Bomb::Bomb(const Point& head)//constructorshape
{
	body[0] = head; //body is a point array, body[0] reference for the upper left corner of the shape in default orientation.
	body[1] = body[2] = body[3] = body[0];
	c = '@';
	shapeColor = RED;
}

bool Bomb::move(Board &gameBoard, char keyPressed, bool &GameOver, int &bombModifier)
{
	Direction dir = getDir(keyPressed);
	Point bodyCpy[4];
	bool newFixedShape = false;
	DEL_FROM_SCR
		for (int i = 0; i < 4; ++i) {
			bodyCpy[i] = body[i];
		}
	for (auto& p : body) {
		p.move(dir);
	}

	if (MOVE_IS_VALID)
	{
		draw(c, shapeColor);
		return true;
	}

	if (GameOver)
	{
		draw(c, shapeColor);
		GAME_OVER;
	}
	else if (newFixedShape == true)
	{
		manageBomb(gameBoard, bombModifier);
		KILL_SHAPE;
	}
	updateBoard(gameBoard, shapeColor);
	draw(c, shapeColor);
	KILL_SHAPE;
}

bool Bomb::checkRestrictions(Board& gameBoard, Point* bodyCpy, Direction dir, bool &newFixedShape, bool &ifGameOver)
{
	int x, y;
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
			}
			newFixedShape = true;
			KILL_SHAPE;
		}
	}

	bodyCpy[0].getXY(x, y);

	if (checkCollisionSides(gameBoard, shapeCollisionSides, borderCollisionSides) == true)
	{
		if (shapeCollisionSides == true || borderCollisionSides == true)
		{
			for (int i = 0; i < 4; ++i) {
				body[i] = bodyCpy[i];
			}
		}
	}
	return true;
}

bool Bomb::checkCollisionSides(Board &gameBoard, bool &shapeCollisionSides, bool &borderCollisionSides) {

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

bool Bomb::checkCollisionBottom(Board &gameBoard, bool &shapeCollision, bool &lowBorderCollision)
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

void Bomb::manageBomb(Board &gameBoard, int &blowedPixles) {

	int leftBorder, rightBorder, upperBorder, bottomBorder;
	getRangeForBomb(leftBorder, rightBorder, upperBorder, bottomBorder);
	Game::bombBlow(leftBorder, rightBorder, upperBorder, bottomBorder);
	gameBoard.resetPixlesInRange(leftBorder, rightBorder, upperBorder, bottomBorder, blowedPixles);
	gameBoard.bombPixelAdjustment(leftBorder, rightBorder, bottomBorder);
	gameBoard.syncBoard();
	/*
	func to get range
	count blowed pixles and update to score
	drop func in range
	draw effect and do not update bomb in board
	*/
}

void Bomb::getRangeForBomb(int &leftBorder, int &rightBorder, int &upperBorder, int &bottomBorder) {
	int x, y;
	body[0].getXY(x, y);
	if (x + 1 <= 10)
		rightBorder = x + 1;
	else
		rightBorder = 10;
	if (x - 1 >= 1)
		leftBorder = x - 1;
	else
		leftBorder = 1;

	if (y - 1 >= 4)
		upperBorder = y - 1;
	else
		upperBorder = 4;
	if (y + 1 <= 18)
		bottomBorder = y + 1;
	else
		bottomBorder = 18;
}

