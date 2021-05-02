#include "Knight.h"


namespace chess {
	chess::Knight::Knight(const PieceColor color) : Piece(color, PieceType::KNIGHT) {

	}

	const int MOVES[8][2] = {
		{2,1},
		{2,-1},
		{-2,1},
		{-2,-1},
		{1,2},
		{1,-2},
		{-1,2},
		{-1,-2},
	};

	void chess::Knight::GetMovements(Piece const* const* const* board, const int row, const int col, bool** movements) const {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				movements[i][j] = false;
			}
		}

		for (int i = 0; i < 8; i++) {
			int irow = row + MOVES[i][0];
			int icol = col + MOVES[i][1];

			if (irow >= 0 && irow < 8 && icol >= 0 && icol < 8) {
				if (board[irow][icol] == nullptr || board[irow][icol]->GetColor() != _color) {
					movements[irow][icol] = true;
				}
			}
		}
	}
}
