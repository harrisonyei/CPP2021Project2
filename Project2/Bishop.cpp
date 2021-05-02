#include "Bishop.h"

chess::Bishop::Bishop(const PieceColor color) : Piece(color, PieceType::BISHOP) {

}

const int DIRS[4][2] = {
		{1,1},
		{-1,1},
		{1,-1},
		{-1,-1},
};

void chess::Bishop::GetMovements(Piece const* const* const* board, const int row, const int col, bool** movements) const {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			movements[i][j] = false;
		}
	}

	// normal move
	for (int i = 0; i < 4; i++) {
		int irow = row + DIRS[i][0];
		int icol = col + DIRS[i][1];

		while (irow >= 0 && irow < 8 && icol >= 0 && icol < 8) {
			if (board[irow][icol] == nullptr || board[irow][icol]->GetType() == PieceType::TMP_PAWN) {
				movements[irow][icol] = true;
			}
			else if (board[irow][icol]->GetColor() != _color) {
				movements[irow][icol] = true;
				break;
			}
			else if (board[irow][icol]->GetColor() == _color) {
				break;
			}
			irow = irow + DIRS[i][0];
			icol = icol + DIRS[i][1];
		}
	}
}
