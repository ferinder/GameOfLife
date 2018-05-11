#include "game.h"

Game::Game()
{
    isSet = false;
}

void Game::RunSimulation(int steps)
{
    for(int s = 0; s < steps; s++)
    {
        GameBoard newBoard(this->board);
        int boardSizeX = this->board.GetSizeX();
        int boardSizeY = this->board.GetSizeY();
        for (int x = 0; x < boardSizeX; x++)
        {
            for(int y = 0; y < boardSizeY; y++)
            {
                int AliveNeighbours = calculateNeighbours(x,y);
                if(this->board(x,y).IsAlive())
                {
                    if(AliveNeighbours == 2 || AliveNeighbours == 3)
                    { }
                    else
                    {
                        newBoard(x,y).ToggleState();
                    }
                }
                else
                {
                    if(AliveNeighbours == 3)
                    {
                        newBoard(x,y).ToggleState();
                    }
                }
            }
        }
        this->board = newBoard;
    }
}

int Game::calculateNeighbours(int x, int y)
{
    int aliveNeighbours = 0;
    for(int i = -1; i < 2; i++)
    {
        if((x+i) < 0 || (x+i) >= this->board.GetSizeX()) continue;
        for (int j = -1; j < 2; j++)
        {
            if((y+j) < 0 || (y+j) >= this->board.GetSizeY() || (i == 0 && j == 0)) continue;
            if(this->board(x+i, y+j).IsAlive()) aliveNeighbours += 1;
        }
    }
    return aliveNeighbours;
}

void Game::NewBoard(int sizeX, int sizeY)
{
    board = GameBoard(sizeX, sizeY);
    isSet = true;
}

bool Game::IsSet()
{
    return isSet;
}

int Game::GetBoardSizeX()
{
    return board.GetSizeX();
}

int Game::GetBoardSizeY()
{
    return board.GetSizeY();
}

void Game::ToggleCellState(int x, int y)
{
    this->board(x,y).ToggleState();
}

void Game::ToggleContinouse()
{
    if (isContinouse == false) isContinouse = true;
    else isContinouse = false;
}

bool Game::IsContinouse()
{
    return isContinouse;
}

bool Game::IsCellAlive(int x, int y)
{
    return board(x,y).IsAlive();
}
