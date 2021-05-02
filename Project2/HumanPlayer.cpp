#include "HumanPlayer.h"
#include "View.h"
//#include "Pieces.h"
#include <string>

chess::HumanPlayer::HumanPlayer(View* view) :Player()
{
	_board = nullptr;

	_moves = new bool* [8];
	for (int i = 0; i < 8; i++)
		_moves[i] = new bool[8];

	_view = view;
}

chess::HumanPlayer::~HumanPlayer()
{
	for (int i = 0; i < 8; i++)
		delete[] _moves[i];
	delete[] _moves;
}

void chess::HumanPlayer::OnSelect(Piece const* const* const* board, int & sourceRow, int & sourceCol, int& targetRow, int& targetCol)
{
	_board = board;

	_state = SelectState::SELECT_PIECE;
	// run handle with mouse callback
	_view->ReadInput(
		std::bind(&HumanPlayer::OnMouseClick, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
		std::bind(&HumanPlayer::OnExit, this));

	std::unique_lock<std::mutex> lock(_mtx);
	_cv.wait(lock);

	_view->StopReadInput();

	_view->ClearGizmos();
	_view->UpdateBoard();

	// return result
	sourceRow = _source_row;
	sourceCol = _source_col;

	targetRow = _target_row;
	targetCol = _target_col;
}

void chess::HumanPlayer::OnUpgrade(Piece const* const* const* board, const int row, const int col, Piece::PieceType& upgradeType)
{
	upgradeType = Piece::PieceType::QUEEN;
}

void chess::HumanPlayer::OnMouseClick(int row, int col, int btn)
{
	std::lock_guard<std::mutex> lock(_mtx);
	if (btn == 0) {

		// select piece
		if (row >= 0 && row < 8 && col >= 0 && col < 8) {
			switch (_state)
			{
			case chess::HumanPlayer::SelectState::SELECT_PIECE:
				
				if (_board[row][col] != nullptr) {
					_view->ClearGizmos();
					_view->SetGizmos(row, col, View::GizmosType::SELECT);

					_board[row][col]->GetMovements(_board, row, col, _moves);

					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++)
						{
							if(_moves[i][j])
								_view->SetGizmos(row, col, View::GizmosType::HINT);
						}
					}
					_view->UpdateBoard();

					_state = SelectState::SELECT_MOVE;

					_source_row = row;
					_source_col = col;
				}
				break;
			case chess::HumanPlayer::SelectState::SELECT_MOVE:

				_state = SelectState::END;

				_target_row = row;
				_target_col = col;

				_cv.notify_all();
				break;
			default:
				_cv.notify_all();
				break;
			}
		}
	}
	else if (btn == 1) {
		// back to select piece
		_state = SelectState::SELECT_PIECE;
		_view->ClearGizmos();
		_view->UpdateBoard();
	}
}

void chess::HumanPlayer::OnExit()
{
	std::lock_guard<std::mutex> lock(_mtx);
	_cv.notify_all();
}
