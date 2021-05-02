#ifndef CHESS_ROOK_H_
#define CHESS_ROOK_H_

#include "Piece.h"

namespace chess {

	class Rook : public Piece {

	public:
		Rook(const PieceColor color);

		void GetMovements(Piece const* const* const* board, const int x, const int y, bool** movements) const override;

	};
}

#endif // !CHESS_ROOK_H_

