#ifndef CHESS_HUMAN_PLAYER_H_
#define CHESS_HUMAN_PLAYER_H_

#include "Player.h"
#include <condition_variable>

namespace chess {
	class View;
	class HumanPlayer : public Player{

		enum class SelectState
		{
			SELECT_PIECE,
			SELECT_MOVE,
			END
		};

	public:
		HumanPlayer(View* view);
		void OnSelect(Piece const* const* const* board, int& sourceRow, int& sourceCol, int& targetRow, int& targetCol) override;
		void OnUpgrade(Piece const* const* const* board, const int row, const int col, Piece::PieceType& upgradeType) override;
		void OnMouseClick(int row, int col, int btn);
		void OnExit();
	private:
		View* _view;
		std::condition_variable _cv;
		std::mutex _mtx;

		SelectState _state = SelectState::END;

		int _source_col = 0;
		int _source_row = 0;

		int _target_col = 0;
		int _target_row = 0;
	};

}

#endif // !CHESS_HUMAN_PLAYER_H_
