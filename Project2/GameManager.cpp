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
	_pieces[0][0] = new Pawn(Piece::PieceColor::WHITE);
	_pieces[0][1] = new Rook(Piece::PieceColor::WHITE);
	_pieces[0][2] = new Knight(Piece::PieceColor::WHITE);
	_pieces[0][3] = new Bishop(Piece::PieceColor::WHITE);
	_pieces[0][4] = new Queen(Piece::PieceColor::WHITE);
	_pieces[0][5] = new King(Piece::PieceColor::WHITE);
	_pieces[0][6] = new TempPawn(Piece::PieceColor::WHITE);

	_pieces[1][0] = new Pawn(Piece::PieceColor::BLACK);
	_pieces[1][1] = new Rook(Piece::PieceColor::BLACK);
	_pieces[1][2] = new Knight(Piece::PieceColor::BLACK);
	_pieces[1][3] = new Bishop(Piece::PieceColor::BLACK);
	_pieces[1][4] = new Queen(Piece::PieceColor::BLACK);
	_pieces[1][5] = new King(Piece::PieceColor::BLACK);
	_pieces[1][6] = new TempPawn(Piece::PieceColor::BLACK);
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
			_players[0]->SetColor(Piece::PieceColor::WHITE);
			_players[1] = new HumanPlayer(_view);
			_players[1]->SetColor(Piece::PieceColor::BLACK);
		}
		else if (cmd == '1') {
			_players[0] = new HumanPlayer(_view);
			_players[0]->SetColor(Piece::PieceColor::WHITE);
			_players[1] = new HumanPlayer(_view);
			_players[1]->SetColor(Piece::PieceColor::BLACK);
			//_players[1] = new AIPlayer();
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
		for (int j = 0; j < 8; j++) {
			_board[i][j] = nullptr;
		}
	}
	_board[0][0] = _board[0][7] = _pieces[1][1];
	_board[7][0] = _board[7][7] = _pieces[0][1];
	_board[0][1] = _board[0][6] = _pieces[1][2];
	_board[7][1] = _board[7][6] = _pieces[0][2];
	_board[0][2] = _board[0][5] = _pieces[1][3];
	_board[7][2] = _board[7][5] = _pieces[0][3];

	_board[0][3] = _pieces[1][4];
	_board[7][3] = _pieces[0][4];
	_board[0][4] = _pieces[1][5];
	_board[7][4] = _pieces[0][5];

	for (int i = 0; i < 8; i++) {
		_board[1][i] = _pieces[1][0];
		_board[6][i] = _pieces[0][0];
	}
	_view->ClearGizmos();
	_view->UpdateBoard();
}

void chess::GameManager::UpdateState()
{
	std::vector<std::pair<int, int>> updateLocations;
	switch (_state)
	{
	case chess::GameManager::State::START:
		_view->SetText("--PRESS ANY KEY TO START--");
		// wait for any key;
		std::cin.clear(); 
		_getch();

		SetPlayer(0);
		_view->SetText("--START-------------------");
		_state = State::PLAY;
		break;
	case chess::GameManager::State::PLAY:
		if (_playerIdx == 0) {
			_view->SetText("--WHITE's turn----------");
		}
		else {
			_view->SetText("--BLACK's turn----------");
		}

		int srcRow, srcCol, tarRow, tarCol;
		_players[_playerIdx]->OnSelect(_board, srcRow, srcCol, tarRow, tarCol);

		// if state interupt
		if (_state != chess::GameManager::State::PLAY)
			break;

		// if avaliable
		if (srcRow >= 0 && srcRow < 8 && srcCol >= 0 && srcCol < 8 && _board[srcRow][srcCol] != nullptr &&
			tarRow >= 0 && tarRow < 8 && tarCol >= 0 && tarCol < 8 && (_board[srcRow][srcCol]->GetColor() == _players[_playerIdx]->GetColor())) {
			
			updateLocations.clear();

			// move
			Piece* movePiece = _board[srcRow][srcCol];
			Piece* targetPiece = _board[tarRow][tarCol];

			// if ate a temp pawn : passant capture
			if (targetPiece != nullptr && (movePiece->GetType() == Piece::PieceType::PAWN && targetPiece->GetType() == Piece::PieceType::TMP_PAWN)) {
				if (targetPiece->GetColor() == Piece::PieceColor::WHITE) {
					_board[tarRow - 1][tarCol] = nullptr;
					updateLocations.push_back(std::make_pair(tarRow - 1, tarCol));
				}
				else {
					_board[tarRow + 1][tarCol] = nullptr;
					updateLocations.push_back(std::make_pair(tarRow + 1, tarCol));
				}
			}

			_board[srcRow][srcCol] = nullptr;
			_board[tarRow][tarCol] = movePiece;

			updateLocations.push_back(std::make_pair(srcRow, srcCol));
			updateLocations.push_back(std::make_pair(tarRow, tarCol));

			// discard temp pawn
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (_board[i][j] != nullptr && _board[i][j]->GetType() == Piece::PieceType::TMP_PAWN) {
						_board[i][j] = nullptr;
					}
				}
			}
			
			_view->UpdateBoard(updateLocations);
			updateLocations.clear();

			// if passant place one temp pawn
			if (movePiece->GetType() == Piece::PieceType::PAWN && srcCol == tarCol){
				if (movePiece->GetColor() == Piece::PieceColor::BLACK && tarRow == 3) {
					_board[2][tarCol] = _pieces[1][6];
				}
				else if(movePiece->GetColor() == Piece::PieceColor::WHITE && tarRow == 4){
					_board[5][tarCol] = _pieces[0][6];
				}
			}

			// if piece can upgrade
			if (movePiece->GetType() == Piece::PieceType::PAWN &&
				((movePiece->GetColor() == Piece::PieceColor::BLACK && tarRow == 7)
				|| (movePiece->GetColor() == Piece::PieceColor::WHITE && tarRow == 0))
				) {

				_view->DisplayUpgrades(true);

				Piece::PieceType upgradeType;
				_players[_playerIdx]->OnUpgrade(_board, tarRow, tarCol, upgradeType);

				switch (upgradeType)
				{
				case Piece::PieceType::ROOK:
					_board[tarRow][tarCol] = _pieces[_playerIdx][1];
					break;
				case Piece::PieceType::KNIGHT:
					_board[tarRow][tarCol] = _pieces[_playerIdx][2];
					break;
				case Piece::PieceType::BISHOP:
					_board[tarRow][tarCol] = _pieces[_playerIdx][3];
					break;
				case Piece::PieceType::QUEEN:
				default:
					_board[tarRow][tarCol] = _pieces[_playerIdx][4];
					break;
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(200));

				_view->DisplayUpgrades(false);

				_view->UpdateBoard(tarRow, tarCol, tarRow, tarCol);
			}

			// switch player
			_playerIdx = ((_playerIdx == 0) ? 1 : 0);
			// check checkmate
		}
		else {
			// else if not avaliable
			//    hint player to reselect avaliable move
			_view->SetText("--INVALID MOVE--", 199);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
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

