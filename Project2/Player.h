#ifndef CHESS_PLAYER_H_
#define CHESS_PLAYER_H_

#include <functional>

namespace chess {
	class Piece;

	class Player {
	public:
		virtual void OnSelect(const Piece*** board, int& row, int& col) = 0;
	};

}

#endif // !CHESS_PLAYER_H_
