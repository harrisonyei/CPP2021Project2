#ifndef CHESS_KNIGHT_H_
#define CHESS_KNIGHT_H_

#include "Piece.h"

namespace chess {

	class Knight : public Piece {

	public:
		Knight(const PieceColor color) : Piece(color, PieceType::KNIGHT) {

		}

		void GetMovements(const Piece* board, const int x, const int y, bool* movements) override {

		}

	};
}

#endif // !CHESS_KNIGHT_H_

