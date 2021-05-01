#ifndef CHESS_PIECE_H_
#define CHESS_PIECE_H_

namespace chess {

	class Piece {
	public:
		enum class PieceType
		{
			EMPTY = 0,
			PAWN,
			ROOK,
			KNIGHT,
			BISHOP,
			QUEEN,
			KING,
		};

		enum class PieceColor
		{
			BLACK = 0,
			WHITE,
		};

	public:
		Piece(const PieceColor color, const PieceType type) : _color(color), _type(type){

		}
		const PieceType GetType() {
			return _type;
		}
		const PieceColor GetColor() {
			return _color;
		}

		virtual void GetMovements(const Piece* board, const int x, const int y, bool* movements) = 0;

	private:
		PieceColor _color;
		PieceType _type;
	};

}

#endif // !CHESS_PIECE_H_

