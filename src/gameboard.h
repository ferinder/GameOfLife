#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "cell.h"

class GameBoard
{
public:
GameBoard() = default;
GameBoard(int sizeX, int sizeY);
GameBoard(const GameBoard& gameBoard);
int GetSizeX();
int GetSizeY();
Cell &operator()(int x, int y);

private:
int sizeX;
int sizeY;
std::vector<Cell> board;
};

#endif // BOARD_H
