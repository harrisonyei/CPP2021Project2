#ifndef CHESS_PAWN_H_
#define CHESS_PAWN_H_

#include "Piece.h"

namespace chess {

	class Pawn : public Piece {

	public:
		Pawn(const PieceColor color) : Piece(color, PieceType::PAWN){

		}

		void GetMovements(const Piece* board, const int x, const int y, bool* movements) override {

		}

	};
}

#endif // !CHESS_PAWN_H_

