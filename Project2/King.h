#ifndef CHESS_KING_H_
#define CHESS_KING_H_

#include "Piece.h"

namespace chess {

	class King : public Piece {

	public:
		King(const PieceColor color) : Piece(color, PieceType::KING) {

		}

		virtual void GetMovements(const Piece* board, const int x, const int y, bool* movements) {

		}

	};
}

#endif // !CHESS_KING_H_

