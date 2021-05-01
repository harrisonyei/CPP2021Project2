#ifndef CHESS_GAMEMANAGER_H_
#define CHESS_GAMEMANAGER_H_

namespace chess {

	class View;
	class Piece;
	class Player;

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
		Player* player[2];

		State _state;
		View* _view;
		Piece* _board[8][8];
		Piece* _pieces[2][16];
		
		void InitBoard();


	};

}

#endif // !CHESS_GAMEMANAGER_H_
