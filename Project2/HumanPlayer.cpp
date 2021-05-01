#include "HumanPlayer.h"
/*
	_view->RegistMouseClick(std::bind(&GameManager::OnMouseClick, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
*/

chess::HumanPlayer::HumanPlayer(View* view) :Player()
{
	_view = view;
}

void chess::HumanPlayer::OnSelect(const Piece*** board, int& row, int& col)
{
	// regist callback

	// run handle

	// return result
}

void chess::HumanPlayer::OnMouseClick(int x, int y, int btn)
{

}
