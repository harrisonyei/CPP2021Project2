#ifndef CHESS_KING_H_
#define CHESS_KING_H_

#include "Piece.h"

namespace chess {

	class King : public Piece {

	public:
		King(const PieceColor color);

		void GetMovements(Piece const* const* const* board, const int x, const int y, bool** movements) const override;

	};
}

#endif // !CHESS_KING_H_

