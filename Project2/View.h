#ifndef CHESS_RENDERER_H_
#define CHESS_RENDERER_H_

#include <windows.h>
#include <thread>
#include <mutex>
#include <future>
#include <functional>

#include "Piece.h"

namespace chess {
	class GameManager;

	static const int BLOCK_H = 7;
	static const int BLOCK_W = 13;

	static const int ICON_H = 5;
	static const int ICON_W = 7;

	class View {
		enum class GizmosType {
			EMPTY = 0,
			SELECT,
			HINT,
			CHECK
		};

	public:
		View(GameManager* );
		~View();

		void Clear();

		void SetActive(bool active);

		void HandleMouseSelect(int& row, int& col);

		int Run();
		int Stop();
		int RegistMouseClick(std::function<void(int, int, int)> callback);

		void SetHints(const int* rows, const int* cols, const int size);
		void SetSelect(const int row, const int col);
		void SetCheck(const int row, const int col);
		void ClearGizmos();

		void UpdateBoard();
		void UpdateBoard(const int row0, const int col0, const int row1, const int col1);

	private:
		unsigned char _bitmap[8 * BLOCK_H][8 * BLOCK_W] = { 0 };
		GizmosType _gizmos[8][8];
		GameManager* _gameManager;

		std::function<void(int, int, int)> _mouseClickCallback;

		bool _active = false;
		bool _exitFlag = false;
		bool _updateRowFlag[8] = { false };
		HANDLE _hStdin;
		HANDLE _hStdout;
		DWORD _fdwSaveOldMode;

		std::thread* _handleUpdateThread;
		std::promise<void> _exitSignal;
		std::future<void> _futureObj;
		std::mutex _stdoutMtx;

		// update board content
		void Draw(const int row, const int col);
		void DrawPiece(const int row, const int col);
		void DrawGIZMOS(const int row, const int col);
		void DrawBackground(const int row, const int col);
		void DrawBlock(const int row, const int col, const unsigned char color);

		// update window content
		void updateWindow(std::future<void> futureObj);

		// handle window event
		void handleWindow();

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
