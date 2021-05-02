#ifndef CHESS_PLAYER_H_
#define CHESS_PLAYER_H_

namespace chess {
	class Piece;

	class Player {
	public:
		virtual void OnSelect(Piece const*const*const* board, int& row, int& col) = 0;
	};

}

#endif // !CHESS_PLAYER_H_
