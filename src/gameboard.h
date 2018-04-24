#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "cell.h"

class GameBoard
{
public:
GameBoard();
GameBoard(int sizeX, int sizeY);
GameBoard(const GameBoard& gameBoard);
void ToggleCellState(int x, int y);

private:
Cell &GetCell(int x, int y);

int sizeX;
int sizeY;
std::vector<std::vector<Cell> > board;
};

#endif // BOARD_H
