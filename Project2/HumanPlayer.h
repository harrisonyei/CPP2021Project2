#ifndef CHESS_HUMAN_PLAYER_H_
#define CHESS_HUMAN_PLAYER_H_

#include "Player.h"

namespace chess {
	class View;
	class HumanPlayer : public Player{
	public:
		HumanPlayer(View* view);
		void OnSelect(const Piece*** board, int& row, int& col) override;
		void OnMouseClick(int x, int y, int btn);
	private:
		View* _view;
	};

}

#endif // !CHESS_HUMAN_PLAYER_H_
