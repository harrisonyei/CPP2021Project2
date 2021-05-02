#include "Pawn.h"

chess::Pawn::Pawn(const PieceColor color) : Piece(color, PieceType::PAWN) {

}

void chess::Pawn::GetMovements(Piece const* const* const* board, const int row, const int col, bool** movements) const {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			movements[i][j] = false;
		}
	}

	if (_color == PieceColor::BLACK) {
		// go down 0 to 8
		for (int i = row + 1; i < 8 && i <= row + 2; i++) {
			movements[i][col] = true;
		}
	}
	else {
		// go up 8 to 0
		for (int i = row - 1; i >= 0 && i >= row - 2; i--) {
			movements[i][col] = true;
		}
	}
}
