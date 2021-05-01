#ifndef CHESS_RENDERER_H_
#define CHESS_RENDERER_H_

#include <windows.h>
#include <thread>
#include <mutex>
#include <future>

namespace chess {

	const int BLOCK_H = 7;
	const int BLOCK_W = 13;

	const int ICON_H = 5;
	const int ICON_W = 7;

	const unsigned char DFLAG = 0b1000000;
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

	class View {
	public:
		View();
		~View();

	private:
		unsigned char board[8 * BLOCK_H][8 * BLOCK_W] = { 0 };

		bool updateRowFlag[8];
		HANDLE hStdin;
		HANDLE hStdout;
		DWORD fdwSaveOldMode;

		std::thread* handleUpdateThread;
		std::promise<void> exitSignal;
		std::future<void> futureObj;

		void InitBoard();
		void DrawPiece(unsigned char* icon, int col, int row, unsigned char color);

		void thread_update(std::future<void> futureObj);

		// window utils
		void gotoxy(int x, int y);
		void setcolor(WORD color);
		void clrscr();

		// window events
		void ErrorExit(LPSTR);
		void KeyEventProc(KEY_EVENT_RECORD);
		void MouseEventProc(MOUSE_EVENT_RECORD);
		void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

	};

}

#endif // !CHESS_RENDERER_H_
