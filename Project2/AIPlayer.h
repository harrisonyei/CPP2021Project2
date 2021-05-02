#ifndef CHESS_AI_PLAYER_H_
#define CHESS_AI_PLAYER_H_

#include "Player.h"

namespace chess {
	class AIPlayer : public Player {
	public:
		AIPlayer();
		void OnSelect(Piece const* const* const* board, int& sourceRow, int& sourceCol, int& targetRow, int& targetCol) override;
		void OnUpgrade(Piece const* const* const* board, const int row, const int col, Piece::PieceType& upgradeType) override;
	private:
	};

}

#endif // !CHESS_AI_PLAYER_H_
