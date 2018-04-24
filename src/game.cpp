#include "game.h"

Game::Game()
{
    simulation = false;
}

void Game::RunSimulation(int steps)
{

}

void Game::NewBoard(int sizeX, int sizeY)
{
    board = GameBoard(sizeX,sizeY);
}

void Game::ToggleSimulation()
{
    if(simulation) simulation = false;
    else simulation = true;
}

bool Game::IsContinouse()
{
    return simulation;
}
