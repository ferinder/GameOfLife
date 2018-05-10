#ifndef GAME_H
#define GAME_H
#include <memory>
#include "gameboard.h"
#include <string>
#include <iostream>

class Game
{
public:
Game();
void RunSimulation(int steps = 0);
void LoadBoard(std::string filePath);
void SaveBoard(std::string filepath);
void NewBoard(int sizeX, int sizeY);
void ToggleContinouse();
bool IsContinouse();
int GetBoardSizeX();
int GetBoardSizeY();
bool IsCellAlive(int x, int y);
void ToggleCellState(int x, int y);
bool IsSet();

private:
GameBoard board;
bool gameIsSet;
bool continouse;
};

#endif // GAME_H