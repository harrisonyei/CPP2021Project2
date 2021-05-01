#include "GameManager.h"
#include "View.h"
#include "Player.h"
#include "Pieces.h"

#include <functional>
#include <iostream>

chess::GameManager::GameManager()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			_board[i][j] = nullptr;
		}
	}

	_state = State::START;
	_view = new View(this);
	_view->RegistMouseClick(std::bind(&GameManager::OnMouseClick, this, std::placeholders::_1, std::placeholders::_2));
}

chess::GameManager::~GameManager()
{
	delete _view;
}

int chess::GameManager::Run()
{
	_state = State::START;

	InitBoard();

	return _view->Run();
}

void chess::GameManager::InitBoard()
{
	for (int i = 0; i < 8; i++) {
		_board[1][i] = new Pawn(Piece::PieceColor::BLACK);
		_board[6][i] = new Pawn(Piece::PieceColor::WHITE);
	}

	_board[0][0] = new Rook(Piece::PieceColor::BLACK);
	_board[0][7] = new Rook(Piece::PieceColor::BLACK);
	_board[0][1] = new Knight(Piece::PieceColor::BLACK);
	_board[0][6] = new Knight(Piece::PieceColor::BLACK);
	_board[0][2] = new Bishop(Piece::PieceColor::BLACK);
	_board[0][5] = new Bishop(Piece::PieceColor::BLACK);
	_board[0][3] = new Queen(Piece::PieceColor::BLACK);
	_board[0][4] = new King(Piece::PieceColor::BLACK);

	_board[7][0] = new Rook(Piece::PieceColor::WHITE);
	_board[7][7] = new Rook(Piece::PieceColor::WHITE);
	_board[7][1] = new Knight(Piece::PieceColor::WHITE);
	_board[7][6] = new Knight(Piece::PieceColor::WHITE);
	_board[7][2] = new Bishop(Piece::PieceColor::WHITE);
	_board[7][5] = new Bishop(Piece::PieceColor::WHITE);
	_board[7][3] = new Queen(Piece::PieceColor::WHITE);
	_board[7][4] = new King(Piece::PieceColor::WHITE);

	_view->UpdateBoard();
}

void chess::GameManager::OnMouseClick(int x, int y)
{

}
