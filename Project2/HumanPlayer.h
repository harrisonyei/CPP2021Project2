#ifndef CHESS_HUMAN_PLAYER_H_
#define CHESS_HUMAN_PLAYER_H_

#include "Player.h"
#include <condition_variable>

namespace chess {
	class View;
	class HumanPlayer : public Player{
	public:
		HumanPlayer(View* view);
		void OnSelect(Piece const* const* const*  board, int& row, int& col) override;
		void OnMouseClick(int row, int col, int btn);
		void OnExit();
	private:
		View* _view;
		std::condition_variable _cv;
		std::mutex _mtx;

		int _select_x = 0;
		int _select_y = 0;
	};

}

#endif // !CHESS_HUMAN_PLAYER_H_
