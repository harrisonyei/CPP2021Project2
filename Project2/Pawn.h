#ifndef CHESS_PAWN_H_
#define CHESS_PAWN_H_

#include "Piece.h"

namespace chess {

	class Pawn : public Piece {

	public:
		Pawn(const PieceColor color);

		void GetMovements(Piece const* const* const* board, const int x, const int y, bool** movements) const override;

	};
}

#endif // !CHESS_PAWN_H_

