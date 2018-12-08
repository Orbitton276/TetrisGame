#pragma once
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <process.h>

using namespace std;
enum colors { GREEN = 10, RED = 12, YELLOW = 14, WHITE = 7, BLUE = 9, CYAN = 11, MAGENTA = 5, BROWN = 6 };
void setColorGeneral(int value);
enum ShapeTypes { SQUARE, LINE, JOKER, BOMB, BIGL, PLUS, ZED };
enum Direction { LEFT, RIGHT, DOWN, UP, STAY };