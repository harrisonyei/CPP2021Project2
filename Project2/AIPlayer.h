#ifndef CHESS_AI_PLAYER_H_
#define CHESS_AI_PLAYER_H_

#include "Player.h"

namespace chess {
	class AIPlayer : public Player {
	public:
		AIPlayer();
		void OnSelect(Piece const* const* const*  board, int& row, int& col) override;
	private:
	};

}

#endif // !CHESS_AI_PLAYER_H_
