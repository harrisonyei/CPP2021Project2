#ifndef CHESS_QUEEN_H_
#define CHESS_QUEEN_H_

#include "Piece.h"

namespace chess {

	class Queen : public Piece {

	public:
		Queen(const PieceColor color);

		void GetMovements(Piece const* const* const* board, const int x, const int y, bool** movements) const override;

	};
}

#endif // !CHESS_QUEEN_H_

