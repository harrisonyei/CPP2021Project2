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
	���ΰѻP���쪺���H�e�����ʹL�]�L�׬O�_�^��F��Ӫ���m�^
	�����b�Q�N�x
	����ɤ��n�g�L���楿�����誺�i��
	�������N���ڪ��楿�����誺�i��
	���P�ѻP���쪺����������L�Ѥl���j
	*/
}
