#include "View.h"
#include <iostream>

using namespace std;
using namespace chess;

View::View()
{
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit(LPSTR("GetStdHandle"));

	// Save the current input mode, to be restored on exit.
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit(LPSTR("GetConsoleMode"));

	// Enable the window and mouse input events.
	DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit(LPSTR("SetConsoleMode"));

	clrscr();
	InitBoard();

	// start game
	futureObj = exitSignal.get_future();
	// Starting Thread & move the future object in lambda function by reference
	handleUpdateThread = new thread(&View::updateWindow, this, std::move(futureObj));

	handleWindow();

}

View::~View()
{
	//Set the value in promise
	exitSignal.set_value();
	//Wait for thread to join
	handleUpdateThread->join();
	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
}

void View::InitBoard()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < BLOCK_H; k++) {
				for (int l = 0; l < BLOCK_W; l++) {
					if ((i & 1) ^ (j & 1)) {
						board[i * 7 + k][j * 13 + l] = 119;
					}
					else {
						board[i * 7 + k][j * 13 + l] = 136;
					}
				}
			}
		}
		updateRowFlag[i] = true;
	}
}

void View::DrawPiece(unsigned char* icon, int col, int row, unsigned char color)
{
	const int offsetX = col * BLOCK_W + 3;
	const int offsetY = row * BLOCK_H + 1;

	for (int i = 0; i < ICON_H; i++) {
		for (int j = 0; j < ICON_W; j++) {
			if (((icon[i] << j) & DFLAG)) {
				board[offsetY + i][offsetX + j] = color;
			}
		}
	}
	updateRowFlag[row] = true;
}

void chess::View::updateWindow(std::future<void> futureObj)
{
	//std::cout << "Thread Start" << std::endl;
	while (futureObj.wait_for(std::chrono::milliseconds(300)) == std::future_status::timeout)
	{
		stdoutMtx.lock();
		for (int row = 0; row < 8; row++) {
			if (updateRowFlag[row]) {
				updateRowFlag[row] = false;
				const int offsetY = row * BLOCK_H;
				gotoxy(0, offsetY);
				for (int i = 0; i < BLOCK_H; i++) {
					for (int j = 0; j < 8 * BLOCK_W; j++) {
						setcolor(board[offsetY + i][j]);
						std::cout << " ";
					}
					std::cout << std::endl;
				}
			}
		}
		gotoxy(0, 8 * BLOCK_H);
		setcolor(7); // normal setting
		stdoutMtx.unlock();
	}
	//std::cout << "Thread End" << std::endl;
}

void chess::View::handleWindow()
{
	bool exitFlag = false;
	while (!exitFlag)
	{
		DWORD cNumRead, i;
		INPUT_RECORD irInBuf[32];

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle
			irInBuf,     // buffer to read into
			32,         // size of read buffer
			&cNumRead)) // number of records read
			ErrorExit(LPSTR("ReadConsoleInput"));

		// Dispatch the events to the appropriate handler.
		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input
				//KeyEventProc(irInBuf[i].Event.KeyEvent);
				exitFlag = true;
				break;

			case MOUSE_EVENT: // mouse input
				stdoutMtx.lock();
				gotoxy(0, 8 * BLOCK_H);
				MouseEventProc(irInBuf[i].Event.MouseEvent);
				stdoutMtx.unlock();
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
}


void View::setcolor(WORD color)
{
	//setcolor(0);//black
	//setcolor(119);//gray
	//setcolor(136);// light gray
	//setcolor(255);//white
	SetConsoleTextAttribute(hStdout, color);
	return;
}

void View::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(hStdout, coord);
	return;
}

void View::clrscr()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	GetConsoleScreenBufferInfo(hStdout, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hStdout, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hStdout, &csbi);
	FillConsoleOutputAttribute(hStdout, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hStdout, coordScreen);
	return;
}

void View::ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

void View::KeyEventProc(KEY_EVENT_RECORD ker)
{
	//printf("Key event: ");

	/*if (ker.bKeyDown)
		printf("key pressed\n");
	else 
		printf("key released\n");*/
}

void View::MouseEventProc(MOUSE_EVENT_RECORD mer)
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
			printf("left button press ");
			printf("%d, %d     \n", mer.dwMousePosition.X, mer.dwMousePosition.Y);
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			printf("right button press ");
			printf("%d, %d     \n", mer.dwMousePosition.X, mer.dwMousePosition.Y);
		}
		else
		{
			//printf("button press\n");
		}
		break;
	case DOUBLE_CLICK:
		//printf("double click\n");
		break;
	case MOUSE_HWHEELED:
		//printf("horizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
		//printf("%d, %d     \n", mer.dwMousePosition.X, mer.dwMousePosition.Y);
		//printf("mouse moved\n");
		break;
	case MOUSE_WHEELED:
		//printf("vertical mouse wheel\n");
		break;
	default:
		//printf("unknown\n");
		break;
	}
}

void View::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}