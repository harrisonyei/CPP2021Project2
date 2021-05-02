#include "King.h"

chess::King::King(const PieceColor color) : Piece(color, PieceType::KING) {

}

const int DIRS[8][2] = {
		{1,0},
		{-1,0},
		{0,1},
		{0,-1},
		{1,1},
		{1,-1},
		{-1,1},
		{-1,-1},
};

void chess::King::GetMovements(Piece const* const* const* board, const int row, const int col, bool** movements) const {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			movements[i][j] = false;
		}
	}

	// normal move
	for (int i = 0; i < 8; i++) {
		int irow = row + DIRS[i][0];
		int icol = col + DIRS[i][1];

		if (irow >= 0 && irow < 8 && icol >= 0 && icol < 8) {
			if (board[irow][icol] == nullptr || board[irow][icol]->GetColor() != _color) {
				movements[irow][icol] = true;
			}
		}
	}

	// castling
	/*
	王或參與易位的車以前曾移動過（無論是否回到了原來的位置）
	王正在被將軍
	易位時王要經過的格正受到對方的進攻
	易位後王將佔據的格正受到對方的進攻
	王與參與易位的車之間有其他棋子阻隔
	*/
}
