#include "Shapes.h"
#include "Utilities.h"
#include "Game.h"

void Shape::draw(char ch, colors color) {
	setShapeColor((int)color);
	for (const auto& p : body) {
		p.draw(ch);
	}
}

char Shape::getSign() {
	return c;
}

Direction Shape::getDir(char keyPressed)
{
	for (const auto& key : dirKeys) {

		if (key == keyPressed) {
			return (Direction)(&key - dirKeys);
		}
	}
	return Direction::DOWN;
}

colors Shape::getShapeColor()
{
	return (colors)shapeColor;
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

void Shape::setShapeColor(int shapeColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shapeColor);
}

