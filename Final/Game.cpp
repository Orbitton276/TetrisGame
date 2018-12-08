#include "Shapes.h"
#include "Game.h"
#include "Board.h"
#include "Utilities.h"
#include "Defines.h"

void Game::run() {
	bool exit = false;
	while (exit != true)
	{
		Game::gameSession(exit);
	}
	return;
}

void Game::printGameStats(int score, int shapes_num)
{
	gotoxy(0, 0);
	setColorGeneral(WHITE);
	cout << "Score: " << "     " << endl << endl << "Shapes: " << "      ";
	gotoxy(0, 0);
	cout << "Score: " << score << endl << endl << "Shapes: " << shapes_num;
}

void Game::printGamePlatform() {
	int i;
	setColorGeneral(WHITE);
	gotoxy(30, 3);
	cout << "Menu";
	for (i = 4; i < 7; i++)
	{
		gotoxy(GAME_NUM_ROWS, i);
		switch (i)
		{
		case 4:
		{
			cout << "1. Start Game       3. Speed up";
			break;
		}
		case 5:
		{
			cout << "2. Pause / Resume   4. Speed down";
			break;
		}
		case 6:
		{
			cout << "9. Exit";
			break;
		}
		default:
			break;
		}
	}
	for (int i = 4; i < 20; i++) {
		gotoxy(0, i);
		cout << '|';
		gotoxy(RIGHT_BORDER, i);
		cout << '|';
		cout.flush();
	}
	for (int i = 0; i < 12; i++) {
		gotoxy(i, 19);
		cout << '=';
		cout.flush();
		gotoxy(i, 3);
		cout << '=';
		cout.flush();

	}

	gotoxy(0, 21);
	cout << "Controllers: \nW-spin shape \nA-move left \nD-move right \nS-stop the joker brick \nX-fast shape lowering";
}

void Game::gameMenu(char keyPressed, int &gameSpeed, bool &pauseFlag, bool &exitFlag, bool &startFlag)
{
	while (startFlag == false) {
		if (KEY_IS_PRESSED) {
			keyPressed = _getch();
			if (keyPressed == Point::eKeys::START_GAME)
			{
				startFlag = true;
				break;
			}
			else if (keyPressed == Point::eKeys::EXIT)
			{
				exitFlag = true;
				for (int i = 2; i < 10; i++)
				{
					gotoxy(i, 10);
					cout << '=';
					cout.flush();
					gotoxy(i, 12);
					cout << '=';
					cout.flush();
				}
				gotoxy(2, RIGHT_BORDER);
				setColorGeneral(WHITE);
				cout << "GOODBYE" << endl;
				gotoxy(3, 20);
				break;

			}
		}
	}
	switch (keyPressed)
	{
	case Point::eKeys::PAUSE_RESUME: {

		pauseFlag = true;
		while (pauseFlag) {
			if (KEY_IS_PRESSED) {
				keyPressed = _getch();
				if (keyPressed == Point::eKeys::PAUSE_RESUME)
				{
					startFlag = true;
					break;
				}

			}
		}


		pauseFlag = !pauseFlag;
		break;
	}
	case Point::eKeys::SPEED_UP: {
		if ((gameSpeed - SPEED_INTERVAL) > MIN_GAME_SPEED) {
			gameSpeed -= SPEED_INTERVAL;
		}
		break;
	}
	case Point::eKeys::SPEED_DOWN: {
		if ((gameSpeed + SPEED_INTERVAL) < MAX_GAME_SPEED) {
			gameSpeed += SPEED_INTERVAL;
		}
		break;
	}
	case Point::eKeys::EXIT: {
		exitFlag = true;
		setColorGeneral(WHITE);
		for (int i = 2; i < 10; i++)
		{
			gotoxy(i, 10);
			cout << '=';
			cout.flush();
			gotoxy(i, 12);
			cout << '=';
			cout.flush();
		}

		gotoxy(2, RIGHT_BORDER);
		cout << "GOODBYE" << endl;
		gotoxy(3, 20);
		break;
	}
	}
}

void Game::rollShape(bool& Jokerflag, int decideShape)
{//the "decideShape" is for debugging.
	time_t value;
	srand((unsigned)time(&value));
	int roll;
	if (decideShape == -1) {
		roll = value % 7;
	}
	else
	{
		roll = decideShape;
	}
	switch (roll) {
	case SQUARE:
	{
		curr = new Square(START_COORD);
		curr->setShapeColor(GREEN);
		break;
	}
	case LINE:
	{
		curr = new Line(START_COORD);
		curr->setShapeColor(BLUE);
		break;
	}
	case JOKER:
	{
		Jokerflag = true;
		curr = new Joker(START_COORD);
		curr->setShapeColor(YELLOW);
		break;
	}
	case BOMB:
	{
		curr = new Bomb(START_COORD);
		curr->setShapeColor(RED);
		break;
	}
	case BIGL:
	{
		curr = new BigL(START_COORD);
		curr->setShapeColor(CYAN);
		break;
	}
	case PLUS:
	{
		curr = new Plus(START_COORD);
		curr->setShapeColor(MAGENTA);
		break;
	}
	case ZED:
	{
		curr = new Zed(START_COORD);
		curr->setShapeColor(BROWN);
		break;
	}
	}
}

bool Game::manageRows(Board &gameBoard, int &rowElimModifier) {
	bool rowsToEliminate[15] = { 0 };
	int rowIndex = 0;
	int numRowsToReduct;
	int upperRowToBlow = 14;
	numRowsToReduct = gameBoard.newFilledRows(rowsToEliminate, upperRowToBlow);
	rowElimModifier = numRowsToReduct;
	if (numRowsToReduct != 0)
	{
		for (int rowIndex = 14; rowIndex >= 0; rowIndex--)
		{

			if (rowsToEliminate[rowIndex] == true)
			{
				blowRow(rowIndex);
				gameBoard.resetRowInBoard(rowIndex);
				//above the rowIndex we will lower every "false" cell by -1, and will update its color attribute according to the cell above.
			}
		}
		gameBoard.SpotsReduction(upperRowToBlow, numRowsToReduct);
	}
	return numRowsToReduct > 0 ? true : false;
}

void Game::blowRow(int row) {

	for (int i = 1; i < RIGHT_BORDER; i++)
	{
		Sleep(25);
		gotoxy(i, row + 4);
		setColorGeneral(RED);
		cout << 'x';
	}

	for (int i = 1; i < RIGHT_BORDER; i++)
	{
		Sleep(25);
		gotoxy(i, row + 4);
		cout << " ";
	}
	//gameBoard.resetRowInBoard(row);
}//efect func

void Game::bombBlow(int &leftBorder, int &rightBorder, int &upperBorder, int &bottomBorder) {

	for (int xCoord = leftBorder; xCoord <= rightBorder; xCoord++)
	{
		for (int yCoord = upperBorder; yCoord <= bottomBorder; yCoord++)
		{
			Sleep(25);
			gotoxy(xCoord, yCoord);
			setColorGeneral(RED);
			cout << '#';
		}
	}
	for (int xCoord = leftBorder; xCoord <= rightBorder; xCoord++)
	{
		for (int yCoord = upperBorder; yCoord <= bottomBorder; yCoord++)
		{
			Sleep(25);
			gotoxy(xCoord, yCoord);
			setColorGeneral(RED);
			cout << ' ';
		}
	}
	for (int xCoord = leftBorder; xCoord <= rightBorder; xCoord++)
	{
		for (int yCoord = upperBorder; yCoord <= bottomBorder; yCoord++)
		{
			Sleep(25);
			gotoxy(xCoord, yCoord);
			setColorGeneral(RED);
			cout << '#';
		}
	}
	for (int xCoord = leftBorder; xCoord <= rightBorder; xCoord++)
	{
		for (int yCoord = upperBorder; yCoord <= bottomBorder; yCoord++)
		{
			Sleep(25);
			gotoxy(xCoord, yCoord);
			setColorGeneral(RED);
			cout << ' ';
		}
	}
}

void Game::gameSession(bool& Exit) {
	Board gameBoard;
	char keyPressed = 0;
	int shapeCounter;
	int score = 0;
	int bombModifier = 0, rowElimModifier = 0;
	bool startGame, pause, gameOver, jokerFlag;
	int speed = DEFAULT_SPEED
		startGame = pause = gameOver = false;
	gameBoard.syncBoard();
	PRINT_MENU
		while (Exit == false && gameOver == false)
		{
			startGame = false;
			Game::gameMenu(keyPressed, speed, pause, Exit, startGame);
			shapeCounter = 1;
			score = 0;
			while (GAME_ON)//the loop controls a single shape untill it goes down.
			{
				PRINT_STATS
					jokerFlag = false;
				DROP_SHAPE
					shapeCounter++;
				DRAW_SHAPE
					NO_KEY
					bool shapeLives = true;
				while (shapeLives == true)
				{
					if (KEY_IS_PRESSED) {
						keyPressed = _getch();
						CHECK_IF_MENU
							if (Exit == true) {
								STOP_GAME;
							}
					}
					else
						NO_KEY

						shapeLives = curr->move(gameBoard, Direction::DOWN, gameOver, bombModifier);//move according to keyPressed
					if (SHAPE_KEY_MOVE) {
						shapeLives = curr->move(gameBoard, keyPressed, gameOver, bombModifier);//move according to keyPressed
					}
					Sleep(GAME_SPEED);

				}
				freeShape();
				EAT_BUFFER
					if (END_SESSION)
					{
						//print the relevant message in a function
						GameOver();
						return;
					}
				if (BOMB_EXPLOSION)//defines for score and modifiers
				{
					bombScoreModifier(score, bombModifier);
				}
				if (ROW_ELIMINATION)
				{
					rowElimScoreModifier(score, rowElimModifier, jokerFlag, gameBoard);
				}
			}
		}
}

void Game::GameOver() {
	gotoxy(2, RIGHT_BORDER);
	setColorGeneral(RED);
	cout << "GAME OVER" << endl;
	Sleep(3000);
}

void Game::bombScoreModifier(int &score, int &bombModifier)
{
	if (score >= 50 * bombModifier)
	{
		score -= (50 * bombModifier);
	}
	else {
		score = 0;
	}
	bombModifier = 0;
}

void Game::rowElimScoreModifier(int &score, int &rowElimModifier, bool &jokerFlag, Board &gameBoard)
{
	if (jokerFlag == true)
		score -= SCORE_JOKER_INTERVAL;
	score += (SCORE_INTERVAL * rowElimModifier);
	rowElimModifier = 0;
	gameBoard.syncBoard();
}

void Game::freeShape() {
	delete curr;
}