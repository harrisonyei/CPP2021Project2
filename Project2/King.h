#ifndef CHESS_KING_H_
#define CHESS_KING_H_

#include "Piece.h"

namespace chess {

	class King : public Piece {

	public:
		friend class Pawn;
		friend class Rook;
		friend class Knight;
		friend class Bishop;
		friend class Queen;
		friend class GameManager;

		King(const PieceColor color);

		void GetMovements(Piece const* const* const* board, const int x, const int y, bool** movements) const override;

	private:
		bool isSafe(Piece const* const* const* board, const int irow, const int icol) const;
	};
}

#endif // !CHESS_KING_H_

