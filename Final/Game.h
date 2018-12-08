#pragma once
#include "Line.h"
#include "Square.h"
#include "Bomb.h"
#include "Joker.h"
#include"BigL.h"
#include"Zed.h"
#include"Plus.h"

enum KEYS { ESC = 27 };
class Game {
	Shape *curr;
public:
	void rollShape(bool& Jokerflag, int decideShape = -1);
	void run();
	void gameSession(bool& Exit);
	void printGamePlatform();
	void gameMenu(char keyPressed, int &gameSpeed, bool &pauseFlag, bool &exitFlag, bool &startFlag);
	void printGameStats(int score, int shapes_num);
	static void blowRow(int row);
	static void bombBlow(int &leftBorder, int &rightBorder, int &upperBorder, int &bottomBorder);
	bool manageRows(Board &gameBoard, int &rowElimModifier);
	void GameOver();
	void bombScoreModifier(int &score, int &bombModifier);
	void rowElimScoreModifier(int &score, int &rowElimModifier, bool &jokerFlag, Board &gameBoard);
	void freeShape();
};
