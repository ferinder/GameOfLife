#include "gameboard.h"


GameBoard::GameBoard(int sizeX, int sizeY)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    board = std::vector<std::vector<Cell> >(sizeX,std::vector<Cell>(sizeY,Cell()));
    std::cout << this->sizeX << ' ' << this->sizeY;
}

GameBoard::GameBoard(const GameBoard &gameBoard)
{
    this->sizeX = gameBoard.sizeX;
    this->sizeY = gameBoard.sizeY;
    this->board = gameBoard.board;
    std::cout << "copy const" << this->sizeX << ' ' << this->sizeY;
}

void GameBoard::ToggleCellState(int x, int y)
{
    board[x][y].ToggleState();
}

int GameBoard::GetSizeX()
{
    return sizeX;
}

int GameBoard::GetSizeY()
{
    return sizeY;
}

bool GameBoard::GetCellState(int x, int y)
{
    return board[x][y].IsAlive();
}

GameBoard::GameBoard()
{

}
