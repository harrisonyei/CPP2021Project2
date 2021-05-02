#ifndef CHESS_BISHOP_H_
#define CHESS_BISHOP_H_

#include "Piece.h"

namespace chess {

	class Bishop : public Piece {
	public:
		Bishop(const PieceColor color);
		void GetMovements(Piece const* const* const* board, const int x, const int y, bool** movements) const override;
	};
}

#endif // !CHESS_BISHOP_H_

