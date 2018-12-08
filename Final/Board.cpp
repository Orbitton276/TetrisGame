#include "Board.h"
#include "Game.h"


void Board::updateShapeInBoard(int xCoord, int yCoord, int numColor) {
	if (SpotsManagment[XBoard][YBoard].PixelAvailable == true)
	{
		rowsBuckets[yCoord - 4]++;
	}
	SpotsManagment[XBoard][YBoard].PixelAvailable = false;
	SpotsManagment[XBoard][YBoard].numColor = numColor;

}

Board::Board()
{
	for (int i = 0; i < GAME_NUM_COLS; i++)
	{
		for (int j = 0; j < GAME_NUM_ROWS; j++)
		{
			SpotsManagment[i][j].PixelAvailable = true;
			SpotsManagment[i][j].numColor = -1;

		}
	}
}

int Board::boardPixelColor(int xCoord, int yCoord) {
	if (xCoord == 0) {
		return SpotsManagment[xCoord][yCoord - 1].numColor;
	}
	return SpotsManagment[XBoard][YBoard].numColor;
}

bool Board::isBoardFree(int xCoord, int yCoord) {
	if (xCoord == 0) {
		return SpotsManagment[xCoord][yCoord - 1].PixelAvailable;
	}
	return SpotsManagment[XBoard][YBoard].PixelAvailable;
}

void Board::resetRowInBoard(int rowNum)
{
	rowsBuckets[rowNum] = 0;
	for (int colNum = 0; colNum < GAME_NUM_COLS; colNum++)
	{
		SpotsManagment[colNum][rowNum].PixelAvailable = true;
		SpotsManagment[colNum][rowNum].numColor = -1;
	}
}

int Board::newFilledRows(bool *rowsToEliminate, int& upperRowToBlow)
{
	int res = 0;
	bool isFirst = true;
	for (int i = 0; i < GAME_NUM_ROWS; i++)
	{

		if (rowsBuckets[i] == GAME_NUM_COLS)
		{
			rowsToEliminate[i] = true;
			res++;
			if (isFirst)
			{
				upperRowToBlow = i;
				isFirst = false;
			}


		}

	}
	return res;
}

void Board::bombPixelAdjustment(int &leftBorder, int &rightBorder, int &bottomBorder) {
	int xCoord, yCoord, count;

	for (yCoord = bottomBorder; yCoord > UPPER_BORDER; yCoord--)
	{
		count = 1;
		for (xCoord = leftBorder; xCoord <= rightBorder; xCoord++)
		{
			if (SpotsManagment[XBoard][YBoard].PixelAvailable == false)
			{
				while (SpotsManagment[XBoard][YBoard + count].PixelAvailable == true && YBoard + count<GAME_NUM_ROWS)
				{
					count++;
				}
				count--;

				SpotsManagment[XBoard][YBoard + count].PixelAvailable = false;
				SpotsManagment[XBoard][YBoard + count].numColor = SpotsManagment[XBoard][YBoard].numColor;
				//same process as updateShape need to check if call the function or not
				SpotsManagment[XBoard][YBoard].PixelAvailable = true;
				SpotsManagment[XBoard][YBoard].numColor = -1;
				rowsBuckets[YBoard]--;
				rowsBuckets[YBoard + count]++;
			}
		}
	}
	for (yCoord = 0; yCoord < GAME_NUM_COLS; yCoord++)
	{
		for (xCoord = 0; xCoord < GAME_NUM_COLS; xCoord++)
		{
			if (SpotsManagment[xCoord][yCoord].numColor == YELLOW)
			{
				count = 1;
				while (SpotsManagment[xCoord][yCoord + count].PixelAvailable == true && yCoord + count<GAME_NUM_ROWS)
				{
					count++;
				}
				count--;

				SpotsManagment[xCoord][yCoord + count].PixelAvailable = false;
				SpotsManagment[xCoord][yCoord + count].numColor = YELLOW;
				//same process as updateShape need to check if call the function or not
				SpotsManagment[xCoord][yCoord].PixelAvailable = true;
				SpotsManagment[xCoord][yCoord].numColor = -1;
				rowsBuckets[yCoord]--;
				rowsBuckets[yCoord + count]++;
			}
		}
	}
}

void Board::syncBoard() {
	for (int xCoord = 0; xCoord < GAME_NUM_COLS; xCoord++)
	{
		for (int yCoord = 0; yCoord < GAME_NUM_ROWS; yCoord++)
		{
			if (SpotsManagment[xCoord][yCoord].PixelAvailable == false)
			{
				gotoxy(inverseXBoard, inverseYBoard);
				setColorGeneral(SpotsManagment[xCoord][yCoord].numColor);
				cout << "*";
			}
			else
			{
				gotoxy(inverseXBoard, inverseYBoard);
				cout << " ";
			}
		}
	}

}

void Board::SpotsReduction(int upperRow, int numRowsToReduct) {
	int xCoords, yCoords;
	for (yCoords = upperRow; yCoords > 0; yCoords--)
	{
		for (xCoords = 0; xCoords <GAME_NUM_COLS; xCoords++)//we only look above the row we want to delete
		{
			if (SpotsManagment[xCoords][yCoords].PixelAvailable == false)//if we detected a shape pixel
			{
				SpotsManagment[xCoords][yCoords + numRowsToReduct].PixelAvailable = false;
				SpotsManagment[xCoords][yCoords + numRowsToReduct].numColor = SpotsManagment[xCoords][yCoords].numColor;
				//same process as updateShape need to check if call the function or not
				SpotsManagment[xCoords][yCoords].PixelAvailable = true;
				SpotsManagment[xCoords][yCoords].numColor = -1;
				rowsBuckets[yCoords]--;
				rowsBuckets[yCoords + numRowsToReduct]++;

			}
		}
	}
}

void Board::resetPixlesInRange(int &leftBorder, int &rightBorder, int &upperBorder, int &bottomBorder, int &blowedPixles) {

	int xCoord, yCoord;
	for (xCoord = leftBorder; xCoord <= rightBorder; xCoord++)
	{
		for (yCoord = upperBorder; yCoord <= bottomBorder; yCoord++)
		{
			if (SpotsManagment[XBoard][YBoard].PixelAvailable == false)
			{
				SpotsManagment[XBoard][YBoard].PixelAvailable = true;
				SpotsManagment[XBoard][YBoard].numColor = -1;
				blowedPixles++;
				rowsBuckets[YBoard]--;
			}
		}
	}
}

