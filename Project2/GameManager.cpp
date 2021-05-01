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
	
	_pieces[0][0] = new Rook(Piece::PieceColor::BLACK);
	_pieces[0][7] = new Rook(Piece::PieceColor::BLACK);
	_pieces[0][1] = new Knight(Piece::PieceColor::BLACK);
	_pieces[0][6] = new Knight(Piece::PieceColor::BLACK);
	_pieces[0][2] = new Bishop(Piece::PieceColor::BLACK);
	_pieces[0][5] = new Bishop(Piece::PieceColor::BLACK);
	_pieces[0][3] = new Queen(Piece::PieceColor::BLACK);
	_pieces[0][4] = new King(Piece::PieceColor::BLACK);
	_pieces[1][0] = new Rook(Piece::PieceColor::WHITE);
	_pieces[1][7] = new Rook(Piece::PieceColor::WHITE);
	_pieces[1][1] = new Knight(Piece::PieceColor::WHITE);
	_pieces[1][6] = new Knight(Piece::PieceColor::WHITE);
	_pieces[1][2] = new Bishop(Piece::PieceColor::WHITE);
	_pieces[1][5] = new Bishop(Piece::PieceColor::WHITE);
	_pieces[1][3] = new Queen(Piece::PieceColor::WHITE);
	_pieces[1][4] = new King(Piece::PieceColor::WHITE);
	for (int i = 8; i < 16; i++) {
		_pieces[0][i] = new Pawn(Piece::PieceColor::BLACK);
		_pieces[1][i] = new Pawn(Piece::PieceColor::WHITE);
	}
}

chess::GameManager::~GameManager()
{
	delete _view;
}

int chess::GameManager::Run()
{
	_view->SetActive(false);
	_view->Run();

	while (true) {
		_view->Clear();

		std::cout << "Play : 0" << std::endl;
		std::cout << "CPU  : 1" << std::endl;
		std::cout << "Exit : any key" << std::endl;

		char cmd;
		std::cin >> cmd;

		if (cmd == '0') {

		}
		else if (cmd == '1') {

		}
		else {
			return 0;
		}

		_state = State::START;
		InitBoard();
		_view->SetActive(true);

		std::this_thread::sleep_for(std::chrono::milliseconds(10000));

		_view->SetActive(false);
	}

	return 0;
}

void chess::GameManager::InitBoard()
{
	for (int i = 0; i < 8; i++) {
		_board[0][i] = _pieces[0][i];
		_board[7][i] = _pieces[1][i];
		_board[1][i] = _pieces[0][8 + i];
		_board[6][i] = _pieces[1][8 + i];
	}
	_view->UpdateBoard();
}
