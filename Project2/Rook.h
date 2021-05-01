#ifndef CHESS_ROOK_H_
#define CHESS_ROOK_H_

#include "Piece.h"

namespace chess {

	class Rook : public Piece {

	public:
		Rook(const PieceColor color) : Piece(color, PieceType::ROOK) {

		}

		virtual void GetMovements(const Piece* board, const int x, const int y, bool* movements) {

		}

	};
}

#endif // !CHESS_ROOK_H_

