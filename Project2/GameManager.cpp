#include "GameManager.h"
#include "View.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Pieces.h"

#include <functional>
#include <iostream>

#include <conio.h>

chess::GameManager::GameManager()
{
	_board = new Piece**[8];
	for (int i = 0; i < 8; i++) {
		_board[i] = new Piece*[8];
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
	while (true) {
		_view->SetActive(false);
		_view->Clear();

		std::cout << "NTUST OOP2021 Project2 ¡¹CHESS¡¸ Sample Program" << std::endl;
		std::cout << "Copyright (c) 2021 by ntust gamelab, all rights reserved." << std::endl;
		std::cout << "*********************************************************" << std::endl;
		std::cout << "______ _____ _____ _____ _____               ___     ___" << std::endl;
		std::cout << "|     |  |  |   __|   __|   __|  _ _ ___ ___|_  |   |   |" << std::endl;
		std::cout << "|   --|     |   __|__   |__   |_| | | -_|  _|_| |_ _| | |" << std::endl;
		std::cout << "|_____|__|__|_____|_____|_____|_|\\_/|___|_| |_____|_|___|" << std::endl;
		std::cout << std::endl;
		std::cout << "*********************************************************" << std::endl;
		std::cout << "|            Play : 0                                   |" << std::endl;
		std::cout << "|            CPU  : 1                                   |" << std::endl;
		std::cout << "|            Exit : any key                             |" << std::endl;
		std::cout << std::endl;
		std::cout << "Enter > ";

		std::cin.clear();
		char cmd = _getch();

		// delete last player configs
		for(int i = 0; i < 2; i++)
			if (_players[i] != nullptr) {
				delete _players[i];
			}

		if (cmd == '0') {
			_players[0] = new HumanPlayer(_view);
			_players[1] = new HumanPlayer(_view);
		}
		else if (cmd == '1') {
			_players[0] = new HumanPlayer(_view);
			_players[1] = new AIPlayer();
		}
		else {
			return 0;
		}

		_state = State::START;
		InitBoard();

		_view->SetActive(true);
		_view->Run();

		while (_state != chess::GameManager::State::END);
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
	_view->ClearGizmos();
	_view->UpdateBoard();
}

void chess::GameManager::UpdateState()
{
	char c;
	switch (_state)
	{
	case chess::GameManager::State::START:
		_view->SetText("--PRESS ANY KEY TO START--");
		// wait for any key;
		std::cin.clear(); 
		_getch();

		SetPlayer(0);
		_view->SetText("START");
		_state = State::PLAY;
		break;
	case chess::GameManager::State::PLAY:
		int selected_row, selected_col;
		_players[_playerIdx]->OnSelect(_board, selected_row, selected_col);
		// if avaliable
		//     move
		//     switch player
		// else if not avaliable
		//    hint player to reselect avaliable move
		break;
	case chess::GameManager::State::END:
		break;
	default:
		break;
	}
}

void chess::GameManager::SetPlayer(int idx)
{
	_playerIdx = idx;
}

void chess::GameManager::OnFrameUpdate(int deltaTime)
{
}

void chess::GameManager::OnUpdate(int deltaTime)
{
	UpdateState();
}

void chess::GameManager::OnExit()
{
	_state = chess::GameManager::State::END;
}

