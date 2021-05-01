#include "View.h"
#include "GameManager.h"
#include <iostream>

using namespace std;

namespace chess {


	const unsigned char IFLAG = 0b1000000;
	const unsigned char IROOK[5] = {
		0b0101010,
		0b0111110,
		0b0011100,
		0b0111110,
		0b1111111,
	};
	const unsigned char IKNIGHT[5] = {
		0b0111110,
		0b1101111,
		0b0011111,
		0b0111110,
		0b1111111,
	};
	const unsigned char IBISHOP[5] = {
		0b0001000,
		0b0011100,
		0b0111101,
		0b0011110,
		0b1111111,
	};
	const unsigned char IQUEEN[5] = {
		0b1010101,
		0b0101010,
		0b0011100,
		0b0111110,
		0b1111111,
	};
	const unsigned char IKING[5] = {
		0b0101010,
		0b1011101,
		0b0101010,
		0b0111110,
		0b1111111,
	};
	const unsigned char IPAWN[5] = {
		0b0000000,
		0b0011100,
		0b0111110,
		0b0011100,
		0b1111111,
	};

	View::View(GameManager* gameManager)
	{
		_gameManager = gameManager;

		// Try get std I/O handle
		_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		_hStdin = GetStdHandle(STD_INPUT_HANDLE);

		if ((_hStdout == INVALID_HANDLE_VALUE) || (_hStdin == INVALID_HANDLE_VALUE))
			ErrorExit(LPSTR("GetStdHandle"));

		// Save the current input mode, to be restored on exit.
		if (!GetConsoleMode(_hStdin, &_fdwSaveOldMode))
			ErrorExit(LPSTR("GetConsoleMode"));

		// Enable the window and mouse input events.
		DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
		if (!SetConsoleMode(_hStdin, fdwMode))
			ErrorExit(LPSTR("SetConsoleMode"));

	}

	View::~View()
	{
		//Set the value in promise
		_exitSignal.set_value();

		//Wait for thread to join
		_handleUpdateThread->join();

		// Restore input mode on exit.
		SetConsoleMode(_hStdin, _fdwSaveOldMode);
	}

	int chess::View::Run()
	{
		try {
			// Clear scream
			clrscr();

			// Create an async object to store shared state
			_futureObj = _exitSignal.get_future();

			// Start a window updating thread
			_handleUpdateThread = new thread(&View::updateWindow, this, std::move(_futureObj));

			// Start handling console input event at this thread
			handleWindow();
		}
		catch (...) {
			return -1;
		}

		return 0;
	}

	int chess::View::RegistMouseClick(std::function<void(int, int)> callback)
	{
		_mouseClickCallback = std::bind(callback, std::placeholders::_1, std::placeholders::_2);

		if (!_mouseClickCallback)
			return -1;

		return 0;
	}

	void View::UpdateBoard()
	{
		std::unique_lock<std::mutex> lock(_stdoutMtx);
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				Draw(row, col);
			}
		}
	}

	void View::UpdateBoard(const int row0, const int col0, const int row1, const int col1)
	{
		std::unique_lock<std::mutex> lock(_stdoutMtx);
		Draw(row0, col0);
		Draw(row1, col1);
	}

	void View::Draw(const int row, const int col)
	{
		if (row < 0 || row >= 8 || col < 0 || col >= 8)
			return;

		DrawBackground(row, col);
		DrawGIZMOS(row, col);
		DrawPiece(row, col);
	}

	void View::DrawPiece(const int row, const int col)
	{
		Piece* piece = _gameManager->_board[row][col];

		if (piece == nullptr)
			return;

		const int offsetX = col * BLOCK_W + 3;
		const int offsetY = row * BLOCK_H + 1;

		const unsigned char color = ((piece->GetColor() == Piece::PieceColor::BLACK) ? 0 : 255);

		const unsigned char* icon;
		switch (piece->GetType())
		{
			case Piece::PieceType::PAWN:
				icon = IPAWN;
				break;
			case Piece::PieceType::ROOK:
				icon = IROOK;
				break;
			case Piece::PieceType::KNIGHT:
				icon = IKNIGHT;
				break;
			case Piece::PieceType::BISHOP:
				icon = IBISHOP;
				break;
			case Piece::PieceType::QUEEN:
				icon = IQUEEN;
				break;
			case Piece::PieceType::KING:
				icon = IKING;
				break;
			default:
				icon = nullptr;
				break;
		}

		if(icon == nullptr)
			return;

		for (int i = 0; i < ICON_H; i++) {
			for (int j = 0; j < ICON_W; j++) {
				if (((icon[i] << j) & IFLAG)) {
					_bitmap[offsetY + i][offsetX + j] = color;
				}
			}
		}

		// Set update window flag to redraw this row
		_updateRowFlag[row] = true;
	}

	void View::DrawGIZMOS(const int row, const int col)
	{
		if (col == _floatCol && row == _floatRow) {
			// color : 68 dark red
			DrawBlock(row, col, 68);
		}
		else if (col == _selectedCol && row == _selectedRow) {
			// color : 238 yellow
			DrawBlock(row, col, 238);
		}
	}

	void chess::View::DrawBackground(const int row, const int col)
	{
		// color : 119 gray
		// color : 136 light gray
		const unsigned char color = (((row & 1) ^ (col & 1)) ? 119 : 136);
		DrawBlock(row, col, color);
	}

	void chess::View::DrawBlock(const int row, const int col, const unsigned char color)
	{
		for (int i = 0; i < BLOCK_H; i++) {
			for (int j = 0; j < BLOCK_W; j++) {
				_bitmap[row * BLOCK_H + i][col * BLOCK_W + j] = color;
			}
		}
		// Set update window flag to redraw this row
		_updateRowFlag[row] = true;
	}

	void chess::View::FloatBlock(const int x, const int y)
	{
		std::unique_lock<std::mutex> lock(_stdoutMtx);

		const int lastCol = _floatCol;
		const int lastRow = _floatRow;

		_floatCol = x / BLOCK_W;
		_floatRow = y / BLOCK_H;

		Draw(lastRow, lastCol);
		Draw(_floatRow, _floatCol);

		//std::cout << _lastSelectX << " " << _lastSelectY << std::endl;
	}

	void chess::View::updateWindow(std::future<void> futureObj)
	{
		while (futureObj.wait_for(std::chrono::milliseconds(100)) == std::future_status::timeout)
		{
			std::unique_lock<std::mutex> lock(_stdoutMtx);
			for (int row = 0; row < 8; row++) {
				if (_updateRowFlag[row]) {
					_updateRowFlag[row] = false;
					const int offsetY = row * BLOCK_H;
					gotoxy(0, offsetY);
					for (int i = 0; i < BLOCK_H; i++) {
						for (int j = 0; j < 8 * BLOCK_W; j++) {
							setcolor(_bitmap[offsetY + i][j]);
							std::cout << ' ';
						}
						std::cout << std::endl;
					}
				}
			}
			gotoxy(0, 8 * BLOCK_H);
			setcolor(7); // normal setting
		}
	}

	void chess::View::handleWindow()
	{
		bool exitFlag = false;
		while (!exitFlag)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(42));

			DWORD cNumRead, i;
			INPUT_RECORD irInBuf[32];

			if (!ReadConsoleInput(
				_hStdin,      // input buffer handle
				irInBuf,     // buffer to read into
				32,         // size of read buffer
				&cNumRead)) // number of records read
				//ErrorExit(LPSTR("ReadConsoleInput"));
				continue;

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
					//gotoxy(0, 8 * BLOCK_H);
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
	}


	void View::setcolor(WORD color)
	{
		//setcolor(0);//black
		//setcolor(119);//gray
		//setcolor(136);// light gray
		//setcolor(255);//white
		SetConsoleTextAttribute(_hStdout, color);
		return;
	}

	void View::gotoxy(int x, int y)
	{
		COORD coord;
		coord.X = x; coord.Y = y;
		SetConsoleCursorPosition(_hStdout, coord);
		return;
	}

	void View::clrscr()
	{
		COORD coordScreen = { 0, 0 };
		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD dwConSize;

		GetConsoleScreenBufferInfo(_hStdout, &csbi);
		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
		FillConsoleOutputCharacter(_hStdout, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
		GetConsoleScreenBufferInfo(_hStdout, &csbi);
		FillConsoleOutputAttribute(_hStdout, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
		SetConsoleCursorPosition(_hStdout, coordScreen);
		return;
	}

	void View::ErrorExit(LPSTR lpszMessage)
	{
		fprintf(stderr, "%s\n", lpszMessage);

		// Restore input mode on exit.
		SetConsoleMode(_hStdin, _fdwSaveOldMode);

		ExitProcess(0);
	}

	void View::KeyEventProc(KEY_EVENT_RECORD ker)
	{

	}

	void View::MouseEventProc(MOUSE_EVENT_RECORD mer)
	{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
		switch (mer.dwEventFlags)
		{
		case 0:
			if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if (_mouseClickCallback) {
					_mouseClickCallback(_floatRow, _floatCol);
				}
			}
			else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				/*printf("right button press ");
				printf("%d, %d     \n", mer.dwMousePosition.X, mer.dwMousePosition.Y);*/
			}
			break;
		case DOUBLE_CLICK:
			//printf("double click\n");
			break;
		case MOUSE_HWHEELED:
			//printf("horizontal mouse wheel\n");
			break;
		case MOUSE_MOVED:
			FloatBlock(mer.dwMousePosition.X, mer.dwMousePosition.Y);
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
		std::unique_lock<std::mutex> lock(_stdoutMtx);
		for (int row = 0; row < 8; row++) {
			_updateRowFlag[row] = true;
		}
		printf("Resize event\n");
		printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
	}
}
