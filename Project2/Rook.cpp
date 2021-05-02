#include "Rook.h"

chess::Rook::Rook(const PieceColor color) : Piece(color, PieceType::ROOK) {

}

const int DIRS[4][2] = {
		{1,0},
		{-1,0},
		{0,1},
		{0,-1},
};

void chess::Rook::GetMovements(Piece const* const* const* board, const int row, const int col, bool** movements) const {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			movements[i][j] = false;
		}
	}

	// normal move
	for (int i = 0; i < 4; i++) {
		int irow = row + DIRS[i][0];
		int icol = col + DIRS[i][1];
		
		while (irow >= 0 && irow < 8 && icol >= 0 && icol < 8) {
			if (board[irow][icol] == nullptr || board[irow][icol]->GetType() == PieceType::TMP_PAWN) {
				movements[irow][icol] = true;
			}
			else if (board[irow][icol]->GetColor() != _color) {
				movements[irow][icol] = true;
				break;
			}
			else if (board[irow][icol]->GetColor() == _color) {
				break;
			}
			irow = irow + DIRS[i][0];
			icol = icol + DIRS[i][1];
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
