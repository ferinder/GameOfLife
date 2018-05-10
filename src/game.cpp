#include "game.h"

Game::Game()
{
    continouse = false;
    gameIsSet = false;
}

void Game::RunSimulation(int steps)
{

}

void Game::NewBoard(int sizeX, int sizeY)
{
    board = GameBoard(sizeX, sizeY);
    gameIsSet = true;
}

void Game::ToggleContinouse()
{
    if(continouse) continouse = false;
    else continouse = true;
}

bool Game::IsContinouse()
{
    return continouse;
}

int Game::GetBoardSizeX()
{
    return board.GetSizeX();
}

int Game::GetBoardSizeY()
{
    return board.GetSizeY();
}

bool Game::IsCellAlive(int x, int y)
{
    return board.GetCellState(x, y);
}

void Game::ToggleCellState(int x, int y)
{
    this->board.ToggleCellState(x, y);
}

bool Game::IsSet()
{
    return gameIsSet;
}
