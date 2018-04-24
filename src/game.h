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
void ToggleSimulation();
bool IsContinouse();


private:
GameBoard board;
bool simulation;
};

#endif // GAME_H
