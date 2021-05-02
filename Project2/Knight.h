#ifndef CHESS_KNIGHT_H_
#define CHESS_KNIGHT_H_

#include "Piece.h"

namespace chess {

	class Knight : public Piece {

	public:
		Knight(const PieceColor color);

		void GetMovements(Piece const* const* const* board, const int x, const int y, bool** movements) const override;

	};
}

#endif // !CHESS_KNIGHT_H_

