#ifndef CHESS_PIECE_H_
#define CHESS_PIECE_H_

namespace chess {

	class Piece {
	public:
		enum class PieceType
		{
			PAWN = 0,
			ROOK,
			KNIGHT,
			BISHOP,
			QUEEN,
			KING,
			TMP_PAWN,
		};

		enum class PieceColor
		{
			WHITE = 0,
			BLACK,
		};

	public:
		Piece(const PieceColor color, const PieceType type) : _color(color), _type(type), _moved(false){

		}
		const PieceType GetType() const {
			return _type;
		}
		const PieceColor GetColor() const {
			return _color;
		}
		const bool GetMoved() const {
			return _moved;
		}

		void ResetMoved() {
			_moved = false;
		}
		void SetMoveed() {
			_moved = true;
		}

		virtual void GetMovements(Piece const*const*const* board, const int row, const int col, bool ** movements) const = 0;

	protected:
		PieceColor _color;
		PieceType _type;
		bool _moved;
	};

}

#endif // !CHESS_PIECE_H_

