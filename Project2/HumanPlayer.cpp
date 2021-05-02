#include "HumanPlayer.h"
#include "View.h"
#include <string>
/*
	_view->RegistMouseClick(std::bind(&GameManager::OnMouseClick, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
*/

chess::HumanPlayer::HumanPlayer(View* view) :Player()
{
	_view = view;
}

void chess::HumanPlayer::OnSelect(Piece const*const*const* board, int& row, int& col)
{
	// run handle with mouse callback
	_view->ReadInput(
		std::bind(&HumanPlayer::OnMouseClick, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
		std::bind(&HumanPlayer::OnExit, this));

	std::unique_lock<std::mutex> lock(_mtx);
	_cv.wait(lock);

	_view->StopReadInput();
	// return result
	row = _select_y;
	col = _select_x;
}

void chess::HumanPlayer::OnMouseClick(int row, int col, int btn)
{
	std::lock_guard<std::mutex> lock(_mtx);
	if (btn == 0) {
		// select piece
		if (row >= 0 && row < 8 && col >= 0 && col < 8) {
			_view->ClearGizmos();
			_view->SetGizmos(row, col, View::GizmosType::SELECT);
			_view->UpdateBoard();
		}
	}
	else if (btn == 1) {
		// back to select piece
		_cv.notify_all();
	}
}

void chess::HumanPlayer::OnExit()
{
	std::lock_guard<std::mutex> lock(_mtx);
	_cv.notify_all();
}
