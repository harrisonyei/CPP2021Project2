#ifndef CHESS_QUEEN_H_
#define CHESS_QUEEN_H_

#include "Piece.h"

namespace chess {

	class Queen : public Piece {

	public:
		Queen(const PieceColor color) : Piece(color, PieceType::QUEEN) {

		}

		void GetMovements(const Piece* board, const int x, const int y, bool* movements) override {

		}

	};
}

#endif // !CHESS_QUEEN_H_

