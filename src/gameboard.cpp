#include "gameboard.h"


GameBoard::GameBoard(int sizeX, int sizeY)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    board = std::vector<Cell>((sizeX * sizeY), Cell());
//    qDebug() << "Board constructor: " << this->sizeX << 'x' << this->sizeY;//<< std::endl;
}

GameBoard::GameBoard(const GameBoard &gameBoard)
{
    this->sizeX = gameBoard.sizeX;
    this->sizeY = gameBoard.sizeY;
    this->board = gameBoard.board;
//    qDebug() << "copy const" << this->sizeX << 'x' << this->sizeY;//<< std::endl;
}

GameBoard::GameBoard(int sizeX, int sizeY, std::vector<Cell> cells)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->board = cells;
}

int GameBoard::GetSizeX()
{
    return this->sizeX;
}

int GameBoard::GetSizeY()
{
    return this->sizeY;
}

Cell &GameBoard::operator()(int x, int y)
{
    return board[(y * this->sizeX) + x];
}

Cell &GameBoard::operator()(int idx)
{
    return board[idx];
}
