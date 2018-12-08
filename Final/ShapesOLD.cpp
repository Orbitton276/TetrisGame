#include "Shapes.h"
#include "Defines.h"
#include "Game.h"

void Shape::draw(char c) {
	for (const auto& p : body) {
		p.draw(c);
	}
}//draw of shape, uses draw of point in order to draw the shape on the screen

Shape::Shape(ShapeType type, const Point& head)//constructorshape
{
	shape = type;
	body[0] = head; //body is a point array, body[0] reference for the upper left corner of the shape in default orientation.
	if (type == SQUARE)
	{
		body[1] = head.right();//creates another point, to the right of the reference;
		body[2] = head.down();//creates another point, below the reference
		body[3] = body[2].right();
		c = '*';
	}
	else if (type == LINE)
	{
		body[1] = head.right();
		body[2] = body[1].right();
		body[3] = body[2].right();
		c = '*';
	}
	else if (type == BOMB)
	{
		body[1] = body[2] = body[3] = body[0];
		c = '@';
	}
	else if (type == JOKER)
	{
		body[1] = body[2] = body[3] = body[0];
		c = 'O';
	}
}

bool Shape::move(Board &gameBoard, char keyPressed, bool &GameOver, int &bombModifier, bool &isJoker)
{
	Direction dir = getDir(keyPressed);
	Point bodyCpy[4];
	Orientation prevOrient;
	bool newFixedShape = false;
	if (shape == JOKER)
		isJoker = true;
	DEL_FROM_SCR

		for (int i = 0; i < 4; ++i) {
			bodyCpy[i] = body[i];
		}
	if (ROTATE_REQUEST)
	{
		prevOrient = mode;
		rotateRight();
	}
	else
	{
		for (auto& p : body) {//saving the upcoming location according to dir (According to key pressed)
			p.move(dir);
		}//UPDATE NEW COORDINATES
	}
	if (STOP_REQUEST)//need to check later if checks are needed before drawing and updating
	{
		setShapeColor(YELLOW);
		Shape::c = '*';
		draw();
		updateBoard(gameBoard, ShapeColorAttribute());
		KILL_SHAPE;
	}


	if (MOVE_IS_VALID)
	{
		draw();
		return true;
	}

	if (GameOver)
	{
		draw();
		GAME_OVER;
	}
	else if (newFixedShape == true)
	{
		if (shape == BOMB)
		{
			manageBomb(gameBoard, bombModifier);
			//reset in range 3x3
			//update score according to blowed pixles
			//drop func in range 3x3
			KILL_SHAPE;
		}
		updateBoard(gameBoard, ShapeColorAttribute());
		if (shape == JOKER) {
			Shape::c = '*';

		}

		draw();
		KILL_SHAPE;
	}
}

bool Shape::checkRestrictions(Board& gameBoard, Point* bodyCpy, Direction dir, bool &newFixedShape, bool &ifGameOver, Orientation &prevOrient)
{
	int x, y;
	setShapeColor(ShapeColorAttribute());//dictates the next drawing color according to the current object.
	bool shapeCollisionBottom, borderCollisionBottom, jokerCollisionWithShapes;
	jokerCollisionWithShapes = shapeCollisionBottom = borderCollisionBottom = false;
	bool shapeCollisionSides, borderCollisionSides;
	shapeCollisionSides = borderCollisionSides = false;

	if (dir == Direction::DOWN)
	{
		if (checkCollisionBottom(gameBoard, jokerCollisionWithShapes, shapeCollisionBottom, borderCollisionBottom) == true)
		{

			if (jokerCollisionWithShapes == true) {//if we are joker and collided because of shape collision and not becuase we reached the bottom

				bodyCpy[0].getXY(x, y);//we check if the previous location of the joker was a shape and we re-draw *.
				if (JOKER_PREV_LOC_OVERRUN)//previous joker location which caused overrun, over a shape. need to re-draw shape.
				{
					gotoxy(x, y);
					setShapeColor(gameBoard.boardPixelColor(x, y));//to ensure we draw in the previous pixel relevant color.
					cout << "*";
					setShapeColor(YELLOW);//now we just draw the joker, color always yellow.
					return true;//if joker collides with a shape but still didnt reached buttom or didnt get stay request then we return to run func, joker still alive.
				}
				else//we reach here if the joker didn't colilded with a shape in the previous location, then we just need to draw the joker on the board.
				{
					setShapeColor(CHECK_OVERRUN_JOKER_COLOR);
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

	if (checkCollisionSides(gameBoard, jokerCollisionWithShapes, shapeCollisionSides, borderCollisionSides) == true)
	{
		if (jokerCollisionWithShapes == true)
		{
			bodyCpy[0].getXY(x, y);
			if (JOKER_PREV_LOC_OVERRUN)
			{
				gotoxy(x, y);
				setShapeColor(gameBoard.boardPixelColor(x, y));
				cout << "*";
				setShapeColor(YELLOW);
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
			if (ROTATE_REQUEST)
			{
				mode = prevOrient;
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
		setShapeColor(YELLOW);
		return true;
	}
	return true;
}

bool Shape::checkCollisionSides(Board &gameBoard, bool &jokerCollisionWithShapes, bool &shapeCollisionSides, bool &borderCollisionSides) {

	int x, y;
	for (auto& p : body) {
		p.getXY(x, y);
		if (SIDE_LIMIT_REACHED) {
			borderCollisionSides = true;
			return true;
		}
		if (SHAPE_COLLISION) {
			if (shape == JOKER)
			{
				jokerCollisionWithShapes = true;
				return true;
			}
			shapeCollisionSides = true;
			return true;
		}
	}
	return false;//if we passed all the tests then side movement is valid and we return false hence no collision.
}

bool Shape::checkCollisionBottom(Board &gameBoard, bool &shapeCollision, bool &lowBorderCollision)
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

Direction Shape::getDir(char keyPressed)
{
	for (const auto& key : dirKeys) {

		if (key == keyPressed) {
			if (keyPressed == 's'&&shape != JOKER) {//only joker is allowed to STAY
				return DOWN;
			}
			return (Direction)(&key - dirKeys);//
		}
	}
	return Direction::DOWN;
}

void Shape::rotateRight() {
	switch (shape)
	{

	case LINE:
	{
		if (mode == Orientation::DEFAULT)
		{
			body[0].setXYChange(1, -1);//means add 1 to x value and reduct 1 from y value
			body[2].setXYChange(-1, 1);
			body[3].setXYChange(-2, 2);
			mode = Orientation::FIRST_TURN;
		}
		else if (mode == Orientation::FIRST_TURN)
		{
			body[0].setXYChange(1, 1);
			body[2].setXYChange(-1, -1);
			body[3].setXYChange(-2, -2);
			mode = Orientation::SECOND_TURN;
		}
		else if (mode == Orientation::SECOND_TURN)
		{
			body[0].setXYChange(-1, 1);
			body[2].setXYChange(1, -1);
			body[3].setXYChange(2, -2);
			mode = Orientation::THIRD_TURN;
		}
		else if (mode = Orientation::THIRD_TURN)
		{
			body[0].setXYChange(-1, -1);
			body[2].setXYChange(1, 1);
			body[3].setXYChange(2, 2);
			mode = Orientation::DEFAULT;
		}
		checkBordersAndCorrect();

	}
	}
}

void Shape::checkBordersAndCorrect() {
	int maxX, minX, maxY, minY;
	getMinMaxPointValues(maxX, minX, maxY, minY);

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

void Shape::updateBoard(Board &gameBoard, int numColor) {
	int x, y;
	for (auto& p : body) {

		p.getXY(x, y);
		gameBoard.updateShapeInBoard(x, y, numColor);
	}
}

void Shape::getMinMaxPointValues(int &max_x, int &min_x, int &max_y, int &min_y)
{
	int currX = 0, currY = 0;
	body[0].getXY(max_x, max_y);
	body[0].getXY(min_x, min_y);
	for (size_t i = 0; i < 4; i++)
	{
		body[i].getXY(currX, currY);

		if (currX > max_x)
			max_x = currX;
		if (currX < min_x)
			min_x = currX;

		if (currY > max_y)
			max_y = currY;
		if (currY < min_y)
			min_y = currY;
	}
}

int Shape::ShapeColorAttribute() {
	if (shape == SQUARE)
		return GREEN;
	else if (shape == LINE)
		return BLUE;
	else if (shape == JOKER)
		return YELLOW;
}

void Shape::setShapeColor(int value) {

	switch (value)
	{
	case GREEN:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);//square
		break;
	case BLUE:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);//line
		break;
	case YELLOW:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);//joker
		break;

	}

}

void Shape::manageBomb(Board &gameBoard, int &blowedPixles) {

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

void Shape::getRangeForBomb(int &leftBorder, int &rightBorder, int &upperBorder, int &bottomBorder) {
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