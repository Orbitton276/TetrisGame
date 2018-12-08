#pragma once
#include "Defines.h"
typedef struct boardPixel {
	bool PixelAvailable;
	int numColor;
}BoardPixel;

class Board {
	BoardPixel SpotsManagment[GAME_NUM_COLS][GAME_NUM_ROWS];
	int rowsBuckets[GAME_NUM_ROWS] = { 0 };

public:
	void updateShapeInBoard(int x, int y, int numColor);
	Board();
	bool isBoardFree(int x, int y);
	int boardPixelColor(int x, int y);
	void resetRowInBoard(int rowNum);
	int newFilledRows(bool *rowsToEliminate, int& upperRowToBlow);
	void SpotsReduction(int upperRow, int numRowsToReduct);
	void resetPixlesInRange(int &leftBorder, int &rightBorder, int &upperBorder, int &bottomBorder, int &blowedPixles);
	void bombPixelAdjustment(int &leftBorder, int &rightBorder, int &bottomBorder);
	void syncBoard();


};