#ifndef CHESS_PLAYER_H_
#define CHESS_PLAYER_H_

#include "Piece.h"

namespace chess {
	class Player {
	protected:
		Piece::PieceColor _color;
	public:
		virtual void OnSelect(Piece const* const* const* board, int & sourceRow, int & sourceCol, int& targetRow, int& targetCol) = 0;
		virtual void OnUpgrade(Piece const*const*const* board, const int row, const int col, Piece::PieceType& upgradeType) = 0;
		inline const Piece::PieceColor& GetColor() { return _color; };
		inline void SetColor(const Piece::PieceColor color) { _color = color; };
	};

}

#endif // !CHESS_PLAYER_H_
