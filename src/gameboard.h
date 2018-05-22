#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <QDebug>
#include "cell.h"
/*!
 * \brief The GameBoard class
 *
 * Class implements gameboard behavior.
 */
class GameBoard
{
public:
GameBoard() = default;
/*!
 * \brief Game board constructor iwth board size parameters.
 * \param sizeX - x size of board,
 * \param sizeY - y size of board.
 */
GameBoard(int sizeX, int sizeY);
/*!
 * \brief Game board copy constructor.
 * \param gameBoard - reference to existing game board.
 */
GameBoard(const GameBoard& gameBoard);
/*!
 * \brief Game board constructor with board size and vector of cells.
 * \param sizeX - board size x,
 * \param sizeY - board size y,
 * \param cells - vector of cells.
 */
GameBoard(int sizeX, int sizeY, std::vector<Cell> cells);
/*!
 * \brief Method for retriving game board size x.
 * \return  size x.
 */
int GetSizeX();
/*!
 * \brief Method for retriving game board size y.
 * \return size y.
 */
int GetSizeY();
/*!
 * \brief Overrided operator () for retriving game board cell with x and y coordinates.
 * \param x - x coordinate of cell on board,
 * \param y - y coordinate of cell on board.
 * \return reference to cell.
 */
Cell &operator()(int x, int y);
/*!
 * \brief  Overrided operator () for retriving cell with index in vector paraeter.
 * \param idx - index of cell in vector.
 * \return reference to cell.
 */
Cell &operator()(int idx);

private:
int sizeX;
int sizeY;
std::vector<Cell> board;
};

#endif // BOARD_H
