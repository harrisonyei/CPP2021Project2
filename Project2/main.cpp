#include <iostream>
#include <windows.h> // WinApi header

using namespace std; // std::cout, std::cin

void gotoxy(int x, int y);
void setcolor(WORD color);
void setForeGroundAndBackGroundColor(int ForeGroundColor, int BackGroundColor);
void clrscr();

HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

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

	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;

	// Get the standard input handle.

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit(LPSTR("GetStdHandle"));

	// Save the current input mode, to be restored on exit.

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit(LPSTR("GetConsoleMode"));

	// Enable the window and mouse input events.
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit(LPSTR("SetConsoleMode"));
	while (true)
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
		gotoxy(0, 0);

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle
			irInBuf,     // buffer to read into
			128,         // size of read buffer
			&cNumRead)) // number of records read
			ErrorExit(LPSTR("ReadConsoleInput"));

		// Dispatch the events to the appropriate handler.

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT: // mouse input
				MouseEventProc(irInBuf[i].Event.MouseEvent);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
				ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;

			case FOCUS_EVENT:  // disregard focus events

			case MENU_EVENT:   // disregard menu events
				break;

			default:
				ErrorExit(LPSTR("Unknown event type"));
				break;
			}
		}


	}
	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);

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

VOID ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
	printf("Key event: ");

	if (ker.bKeyDown)
		printf("key pressed\n");
	else printf("key released\n");
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	//printf("Mouse event: ");

	switch (mer.dwEventFlags)
	{
	case 0:
		
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			printf("left button press \n");
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			printf("right button press \n");
		}
		else
		{
			printf("button press\n");
		}
		break;
	case DOUBLE_CLICK:
		printf("double click\n");
		break;
	case MOUSE_HWHEELED:
		printf("horizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
		printf("%d, %d\n", mer.dwMousePosition.X, mer.dwMousePosition.Y);
		//printf("mouse moved\n");
		break;
	case MOUSE_WHEELED:
		printf("vertical mouse wheel\n");
		break;
	default:
		printf("unknown\n");
		break;
	}
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}