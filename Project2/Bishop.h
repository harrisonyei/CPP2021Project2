#ifndef CHESS_BISHOP_H_
#define CHESS_BISHOP_H_

#include "Piece.h"

namespace chess {

	class Bishop : public Piece {

	public:
		Bishop(const PieceColor color) : Piece(color, PieceType::BISHOP) {

		}

		virtual void GetMovements(const Piece* board, const int x, const int y, bool* movements) {

		}

	};
}

#endif // !CHESS_BISHOP_H_

