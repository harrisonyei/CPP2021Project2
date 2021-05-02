#include "Pawn.h"

namespace chess {


	chess::Pawn::Pawn(const PieceColor color) : Piece(color, PieceType::PAWN) {

	}

	void chess::Pawn::GetMovements(Piece const* const* const* board, const int row, const int col, bool** movements) const {

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				movements[i][j] = false;
			}
		}

		if (_color == PieceColor::BLACK) {

			// line
			if (row == 1) {
				movements[2][col] = (board[2][col] == nullptr);
				movements[3][col] = (board[3][col] == nullptr);
			}
			else if (row < 7) {
				movements[row + 1][col] = (board[row + 1][col] == nullptr);
			}

			// diagonal
			if (row < 7) {
				if (col > 0 && board[row + 1][col - 1] != nullptr && board[row + 1][col - 1]->GetColor() != _color) {
					movements[row + 1][col - 1] = true;
				}
				if (col < 7 && board[row + 1][col + 1] != nullptr && board[row + 1][col + 1]->GetColor() != _color) {
					movements[row + 1][col + 1] = true;
				}
			}
		}
		else {
			// line
			if (row == 6) {
				movements[5][col] = (board[5][col] == nullptr);
				movements[4][col] = (board[4][col] == nullptr);
			}
			else if (row > 0) {
				movements[row - 1][col] = (board[row - 1][col] == nullptr);
			}

			// diagonal
			if (row > 0) {
				if (col > 0 && board[row - 1][col - 1] != nullptr && board[row - 1][col - 1]->GetColor() != _color) {
					movements[row - 1][col - 1] = true;
				}
				if (col < 7 && board[row - 1][col + 1] != nullptr && board[row - 1][col + 1]->GetColor() != _color) {
					movements[row - 1][col + 1] = true;
				}
			}
		}
	}

	chess::TempPawn::TempPawn(const PieceColor color) : Piece(color, PieceType::TMP_PAWN)
	{
	}

	void chess::TempPawn::GetMovements(Piece const* const* const* board, const int x, const int y, bool** movements) const
	{
	}
}
