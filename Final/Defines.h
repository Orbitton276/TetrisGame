#pragma once

#define GAME_ON startGame == true
#define DROP_SHAPE rollShape(jokerFlag, -1);
#define DRAW_SHAPE curr->draw(curr->getSign(),curr->getShapeColor());
#define PRINT_STATS Game::printGameStats(score, shapeCounter);
#define PRINT_MENU Game::printGamePlatform();
#define SHAPE_FALLS shapeLives==true
#define START_COORD {4,4}
#define KEY_IS_PRESSED _kbhit()
#define CHECK_IF_MENU Game::gameMenu(keyPressed,speed,pause,Exit,startGame);
#define STOP_GAME startGame = false; return;
#define SHAPE_KEY_MOVE keyPressed != 0 && shapeLives == true
#define SHAPE_DEFAULT_MOVE shapeLives = curr.move(gameBoard, 0);
#define MOVE_BY_KEY shapeLives = curr.move(gameBoard, keyPressed);
#define EAT_BUFFER while (_kbhit()) _getch();
#define SHAPE_DIES shapeLives==false
#define NO_KEY keyPressed = 0;
#define GAME_SPEED speed
#define END_SESSION gameOver == true
#define DEFAULT_SPEED 150;
#define BOMB_EXPLOSION bombModifier!=0
#define ROW_ELIMINATION manageRows(gameBoard,rowElimModifier)==true


//move function defines
//------------------------
#define DEL_FROM_SCR draw(' ', WHITE);
#define ROTATE_REQUEST dir == Direction::UP
#define STOP_REQUEST dir==Direction::STAY
#define KILL_SHAPE return false
#define GAME_OVER return false
#define LOW_LIMIT_REACHED y>18
#define SHAPE_COLLISION gameBoard.isBoardFree(x, y)==false
#define JOKER_PREV_LOC_OVERRUN gameBoard.isBoardFree(x, y) == false
#define SIDE_LIMIT_REACHED x < 1 || x>10
#define CHECK_OVERRUN_JOKER_COLOR gameBoard.boardPixelColor(x, y)
#define MOVE_IS_VALID checkRestrictions(gameBoard, bodyCpy, dir, newFixedShape,GameOver)==true 
#define JOKER_SPECIAL_EVENT gameBoard.isBoardFree(x, y) == false

//Board defines

#define SPEED_INTERVAL 100
#define SCORE_INTERVAL 100
#define SCORE_JOKER_INTERVAL 50
#define MAX_GAME_SPEED 700
#define MIN_GAME_SPEED 100
#define GAME_NUM_ROWS 15
#define GAME_NUM_COLS 10
#define XBoard xCoord-1
#define YBoard yCoord-4
#define inverseXBoard xCoord+1
#define inverseYBoard yCoord+4
#define UPPER_BORDER 4
#define LOWER_BORDER 20
#define RIGHT_BORDER 11
#define LEFT_BORDER 0





