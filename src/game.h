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
bool IsSet();
int GetBoardSizeX();
int GetBoardSizeY();
void ToggleCellState(int x, int y);
void ToggleContinouse();
bool IsContinouse();
bool IsCellAlive(int x, int y);

private:
GameBoard board;
bool isSet;
bool isContinouse;
int calculateNeighbours(int x, int y);
};

#endif // GAME_H
