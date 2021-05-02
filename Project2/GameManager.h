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
			PLAY,
			END,
		};

	public:

		GameManager();
		~GameManager();

		int Run();

		friend class View;

	private:

		int _playerIdx = 0;

		Player* _players[2] = {nullptr, nullptr};

		State _state;
		View* _view;
		Piece* _board[8][8];
		Piece* _pieces[2][16];
		
		void InitBoard();
		void UpdateState();

		void SetPlayer(int idx);
		void OnFrameUpdate(int deltaTime);
		void OnEventUpdate();
	};

}

#endif // !CHESS_GAMEMANAGER_H_
