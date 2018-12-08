#include "Joker.h"

Joker::Joker(const Point& head)
{
	body[0] = head;
	body[1] = body[2] = body[3] = body[0];
	c = 'O';
	shapeColor = YELLOW;
}

Direction Joker::getDir(char keyPressed)
{
	for (const auto& key : dirKeys) {

		if (key == keyPressed) {
			if (keyPressed == 's') {
				return STAY;
			}
			return (Direction)(&key - dirKeys);
		}
	}
	return Direction::DOWN;
}

bool Joker::move(Board &gameBoard, char keyPressed, bool &GameOver, int &bombModifier)
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

	if (STOP_REQUEST)
	{
		Joker::c = '*';
		draw(c, shapeColor);
		updateBoard(gameBoard, shapeColor);
		KILL_SHAPE;
	}
	if (MOVE_IS_VALID)
	{
		draw(c, shapeColor);
	}
	else if (newFixedShape == true)
	{
		updateBoard(gameBoard, shapeColor);
		Joker::c = '*';
		draw(c, shapeColor);
		KILL_SHAPE;
	}
	return true;
}

bool Joker::checkRestrictions(Board& gameBoard, Point* bodyCpy, Direction dir, bool &newFixedShape, bool &ifGameOver)
{
	int x, y;
	bool shapeCollisionBottom, borderCollisionBottom, jokerCollisionWithShapes;
	jokerCollisionWithShapes = shapeCollisionBottom = borderCollisionBottom = false;
	bool shapeCollisionSides, borderCollisionSides;
	shapeCollisionSides = borderCollisionSides = false;

	if (dir == Direction::DOWN)
	{
		if (checkCollisionBottom(gameBoard, shapeCollisionBottom, borderCollisionBottom) == true)
		{

			if (shapeCollisionBottom == true) {//if we are joker and collided because of shape collision and not becuase we reached the bottom

				bodyCpy[0].getXY(x, y);//we check if the previous location of the joker was a shape and we re-draw *.
				if (JOKER_PREV_LOC_OVERRUN)//previous joker location which caused overrun, over a shape. need to re-draw shape.
				{
					gotoxy(x, y);
					setShapeColor(CHECK_OVERRUN_JOKER_COLOR);//to ensure we draw in the previous pixel relevant color.
					cout << "*";
					setShapeColor(shapeColor);//now we just draw the joker, color always yellow.
					return true;//if joker collides with a shape but still didnt reached buttom or didnt get stay request then we return to run func, joker still alive.
				}
				else//we reach here if the joker didn't colilded with a shape in the previous location, then we just need to draw the joker on the board.
				{
					setShapeColor(shapeColor);
					return true;//return im still alive to run function and starts new move iteration.
				}
			}
			else if (shapeCollisionBottom == true || borderCollisionBottom == true)//if not a joker and collision is true we return to previous location and update board.
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
		if (jokerCollisionWithShapes == true)
		{
			bodyCpy[0].getXY(x, y);
			if (JOKER_PREV_LOC_OVERRUN)
			{
				gotoxy(x, y);
				setShapeColor(gameBoard.boardPixelColor(x, y));
				cout << "*";
				setShapeColor(shapeColor);
				return true;//if joker collides with a shape then we return here to run.
			}
			else
			{
				setShapeColor(CHECK_OVERRUN_JOKER_COLOR);
				return true;
			}
		}
		else if (shapeCollisionSides == true || borderCollisionSides == true)
		{
			for (int i = 0; i < 4; ++i) {//returning body to original points location.
				body[i] = bodyCpy[i];
			}
		}
	}
	//joker_special_event
	//------------------------------
	//if we were moving to the sides from a shape to empty space
	//we will pass all tests because to the left/right
	//of the shape there is nothing blocking us, and we are not in the bottom.
	//but we still need to check if the previous location was a shape, if so, we draw it back,
	//according to boardPixelColor.

	if (JOKER_SPECIAL_EVENT)
	{
		gotoxy(x, y);
		setShapeColor(gameBoard.boardPixelColor(x, y));
		cout << "*";
		setShapeColor(shapeColor);
		return true;
	}
	return true;
}

bool Joker::checkCollisionSides(Board &gameBoard, bool &shapeCollisionSides, bool &borderCollisionSides) {

	int x, y;
	for (auto& p : body) {
		p.getXY(x, y);
		if (SIDE_LIMIT_REACHED) {
			borderCollisionSides = true;
			return true;
		}
		if (SHAPE_COLLISION) {
			return true;
		}
	}
	return false;//if we passed all the tests then side movement is valid and we return false hence no collision.
}

bool Joker::checkCollisionBottom(Board &gameBoard, bool &shapeCollision, bool &lowBorderCollision)
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
			return true;//no need to check other points.
		}
	}
	return false;
}

