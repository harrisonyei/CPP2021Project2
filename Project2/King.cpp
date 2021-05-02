#include "King.h"

namespace chess {

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

	const int MOVES[8][2] = {
			{2,1},
			{2,-1},
			{-2,1},
			{-2,-1},
			{1,2},
			{1,-2},
			{-1,2},
			{-1,-2},
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
					bool safe = true;
					// check pawn
					if (safe) {
						if (_color == PieceColor::WHITE) {
							for (int i = 6; i < 8; i++) {
								int iirow = irow + DIRS[i][0];
								int iicol = icol + DIRS[i][1];
								if (iirow >= 0 && iirow < 8 && iicol >= 0 && iicol < 8) {
									if (board[iirow][iicol] != nullptr && board[iirow][iicol]->GetColor() != _color
										&& board[iirow][iicol]->GetType() == PieceType::PAWN) {
										safe = false;
										break;
									}
								}
							}
						}
						else {
							for (int i = 4; i < 6; i++) {
								int iirow = irow + DIRS[i][0];
								int iicol = icol + DIRS[i][1];
								if (iirow >= 0 && iirow < 8 && iicol >= 0 && iicol < 8) {
									if (board[iirow][iicol] != nullptr && board[iirow][iicol]->GetColor() != _color
										&& board[iirow][iicol]->GetType() == PieceType::PAWN) {
										safe = false;
										break;
									}
								}
							}
						}
					}
					// check king
					if (safe) {
						for (int i = 0; i < 8; i++) {
							int iirow = irow + DIRS[i][0];
							int iicol = icol + DIRS[i][1];
							if (iirow >= 0 && iirow < 8 && iicol >= 0 && iicol < 8) {
								if (board[iirow][iicol] != nullptr && board[iirow][iicol]->GetColor() != _color
									&& board[iirow][iicol]->GetType() == PieceType::KING) {
									safe = false;
									break;
								}
							}
						}
					}
					// check knight
					if (safe) {
						for (int i = 0; i < 8; i++) {
							int iirow = irow + MOVES[i][0];
							int iicol = icol + MOVES[i][1];
							if (iirow >= 0 && iirow < 8 && iicol >= 0 && iicol < 8) {
								if (board[iirow][iicol] != nullptr && board[iirow][iicol]->GetColor() != _color
									&& board[iirow][iicol]->GetType() == PieceType::KNIGHT) {
									safe = false;
									break;
								}
							}
						}
					}
					// check straight enimes
					if (safe) {
						for (int i = 0; i < 4; i++) {
							int iirow = irow + DIRS[i][0];
							int iicol = icol + DIRS[i][1];
							while (iirow >= 0 && iirow < 8 && iicol >= 0 && iicol < 8) {
								if (board[iirow][iicol] == nullptr || board[iirow][iicol]->GetType() == PieceType::TMP_PAWN 
									|| board[iirow][iicol]->GetType() == PieceType::KING) {
									
								}
								else if (board[iirow][iicol]->GetColor() != _color && 
									(board[iirow][iicol]->GetType() == PieceType::ROOK || board[iirow][iicol]->GetType() == PieceType::QUEEN)) {
									safe = false;
									break;
								}
								else {
									break;
								}
								iirow = iirow + DIRS[i][0];
								iicol = iicol + DIRS[i][1];
							}
						}
					}
					if (safe) {
						// check diagonal enimes
						for (int i = 4; i < 8; i++) {
							int iirow = irow + DIRS[i][0];
							int iicol = icol + DIRS[i][1];
							while (iirow >= 0 && iirow < 8 && iicol >= 0 && iicol < 8) {
								if (board[iirow][iicol] == nullptr || board[iirow][iicol]->GetType() == PieceType::TMP_PAWN
									|| board[iirow][iicol]->GetType() == PieceType::KING) {
									
								}
								else if (board[iirow][iicol]->GetColor() != _color &&
									(board[iirow][iicol]->GetType() == PieceType::BISHOP || board[iirow][iicol]->GetType() == PieceType::QUEEN)) {
									safe = false;
									break;
								}
								else{
									break;
								}

								iirow = iirow + DIRS[i][0];
								iicol = iicol + DIRS[i][1];
							}
						}
					}
					movements[irow][icol] = safe;
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
}
