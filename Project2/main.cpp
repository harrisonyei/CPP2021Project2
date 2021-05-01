#include <iostream>
#include <windows.h> // WinApi header

using namespace std; // std::cout, std::cin

void gotoxy(int x, int y);
void setcolor(WORD color);
void setForeGroundAndBackGroundColor(int ForeGroundColor, int BackGroundColor);
void clrscr();

int main()
{
	const unsigned char CASTLE[5] = {
		0b0101010,
		0b0111110,
		0b0011100,
		0b0111110,
		0b1111111,
	};
	const unsigned char KNIGHT[5] = {
		0b0111110,
		0b1101111,
		0b0011111,
		0b0111110,
		0b1111111,
	};
	const unsigned char BISHOP[5] = {
		0b0001000,
		0b0011100,
		0b0111101,
		0b0011110,
		0b1111111,
	};
	const unsigned char QUEEN[5] = {
		0b1010101,
		0b0101010,
		0b0011100,
		0b0111110,
		0b1111111,
	};
	const unsigned char KING[5] = {
		0b0101010,
		0b1011101,
		0b0101010,
		0b0111110,
		0b1111111,
	};
	const unsigned char PAWN[5] = {
		0b0000000,
		0b0011100,
		0b0111110,
		0b0011100,
		0b1111111,
	};

	unsigned char board[8 * 7][8 * 13] = { 0 };
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 7; k++) {
				for (int l = 0; l < 13; l++) {
					if ((i & 1) ^ (j & 1)) {
						board[i * 7 + k][j * 13 + l] = 119;
					}
					else {
						board[i * 7 + k][j * 13 + l] = 136;
					}
				}
			}
		}
	}

	int offsetX = 3;
	int offsetY = 1;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			if (((CASTLE[i] << j) & 0b1000000)) {
				board[offsetY + i][offsetX + j] = 255;
			}
		}
	}

	offsetX += 13;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			if (((KNIGHT[i] << j) & 0b1000000)) {
				board[offsetY + i][offsetX + j] = 255;
			}
		}
	}

	offsetX += 13;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			if (((BISHOP[i] << j) & 0b1000000)) {
				board[offsetY + i][offsetX + j] = 255;
			}
		}
	}

	offsetX += 13;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			if (((QUEEN[i] << j) & 0b1000000)) {
				board[offsetY + i][offsetX + j] = 255;
			}
		}
	}

	offsetX += 13;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			if (((KING[i] << j) & 0b1000000)) {
				board[offsetY + i][offsetX + j] = 255;
			}
		}
	}

	offsetY += 7;
	offsetX = 3;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			if (((PAWN[i] << j) & 0b1000000)) {
				board[offsetY + i][offsetX + j] = 255;
			}
		}
	}

	while (cin.get())
	{
		for (int i = 0; i < 56; i++) {
			for (int j = 0; j < 104; j++) {
				setcolor(board[i][j]);
				//setcolor(0);//black
				//setcolor(119);//gray
				//setcolor(136);// light gray
				//setcolor(255);//white
				std::cout << " ";
			}
			std::cout << std::endl;
		}
		setcolor(7);// normal
	}
	return 0;
}

void setcolor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return;
}

void setForeGroundAndBackGroundColor(int ForeGroundColor, int BackGroundColor)
{
	int color = 16 * BackGroundColor + ForeGroundColor;
	setcolor(color);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

void clrscr()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
	return;
}