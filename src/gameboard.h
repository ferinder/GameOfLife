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
int GetSizeX();
int GetSizeY();
bool GetCellState(int x, int y);

private:

int sizeX;
int sizeY;
std::vector<std::vector<Cell> > board;
};

#endif // BOARD_H
