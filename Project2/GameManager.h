#ifndef CHESS_GAMEMANAGER_H_
#define CHESS_GAMEMANAGER_H_

namespace chess {

	class View;
	class Piece;

	class GameManager
	{
		enum class State {
			START = 0,
			SELECT_PIECE,
			SELECT_MOVE,
			END,
		};

	public:
		GameManager();
		~GameManager();

		int Run();

		friend class View;

	private:

		State _state;
		View* _view;
		Piece* _board[8][8];
		
		void InitBoard();

		void OnMouseClick(int x, int y);

	};

}

#endif // !CHESS_GAMEMANAGER_H_
