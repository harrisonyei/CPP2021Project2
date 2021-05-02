#ifndef CHESS_PLAYER_H_
#define CHESS_PLAYER_H_

#include "Piece.h"

namespace chess {
	class Player {
	public:
		virtual void OnSelect(Piece const* const* const* board, int & sourceRow, int & sourceCol, int& targetRow, int& targetCol) = 0;
		virtual void OnUpgrade(Piece const*const*const* board, const int row, const int col, Piece::PieceType& upgradeType) = 0;
	};

}

#endif // !CHESS_PLAYER_H_
