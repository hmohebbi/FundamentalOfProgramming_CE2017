#ifndef CONNECT4_H
#define CONNECT4_H

#define BOARD_ROWS 6
#define BOARD_COLS 7

#include <stdio.h> 
#include <windows.h>
#include <time.h>

void gotoxy(int x, int y);
void clearScreen();
void setTextColor(int textColor, int backColor = 0);
void sleep(unsigned int mseconds);
void printBoard();

#endif
