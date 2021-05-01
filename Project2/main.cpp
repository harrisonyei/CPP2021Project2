#include "View.h"

#include <iostream>

int main()
{
	chess::View v;
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	//while (true)
	//{
	//	for (int i = 0; i < 56; i++) {
	//		for (int j = 0; j < 104; j++) {
	//			setcolor(board[i][j]);
	//			
	//			std::cout << " ";
	//		}
	//		std::cout << std::endl;
	//	}
	//	setcolor(7);// normal
	//	gotoxy(0, 0);

	//	if (!ReadConsoleInput(
	//		hStdin,      // input buffer handle
	//		irInBuf,     // buffer to read into
	//		128,         // size of read buffer
	//		&cNumRead)) // number of records read
	//		ErrorExit(LPSTR("ReadConsoleInput"));

	//	// Dispatch the events to the appropriate handler.

	//	for (i = 0; i < cNumRead; i++)
	//	{
	//		switch (irInBuf[i].EventType)
	//		{
	//		case KEY_EVENT: // keyboard input
	//			KeyEventProc(irInBuf[i].Event.KeyEvent);
	//			break;

	//		case MOUSE_EVENT: // mouse input
	//			MouseEventProc(irInBuf[i].Event.MouseEvent);
	//			break;

	//		case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
	//			ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
	//			break;

	//		case FOCUS_EVENT:  // disregard focus events

	//		case MENU_EVENT:   // disregard menu events
	//			break;

	//		default:
	//			ErrorExit(LPSTR("Unknown event type"));
	//			break;
	//		}
	//	}
	//}
	

	return 0;
}

