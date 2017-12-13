#include "connect4.h"

void gotoxy(int x, int y){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorCoord;
	cursorCoord.X = y;
	cursorCoord.Y = x;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

void clearScreen(){
	system("cls");
}

void setTextColor(int textColor, int backColor){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

void sleep(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

void printBoard() {

	printf("\n         Connect Four\n\n");
	for (int row = 0; row < BOARD_ROWS; row++) {
		for (int col = 0; col < BOARD_COLS; col++) {
			printf("|   ");
		}
		printf("|\n");
		for (int i = 0; i < BOARD_COLS; i++)
			printf(" %c%c%c", 205, 205, 205);
		printf("\n");
	}
	for (int i = 1; i <= BOARD_COLS; i++)
		printf("%3d ", i);
	printf("\n\n");
}