#ifndef GAME_H
#define GAME_H
#include "gameboard.h"
#include "cell.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <QDebug>
#include "colorruleenum.h"
/*!
 * \brief The Game class
 *
 * Class represents game and implements its behavior.
 */
class Game
{
public:
/*!
 * \brief Game default constructor.
 *
 * Constructs game ands sets default game rule to ''23/3'' which is basic Conway's game of life rule.
 */
Game();
/*!
 * \brief Method perform single simulation step.
 */
void RunSimulation();
/*!
 * \brief Load board from file.
 * \param filePath - path to file with saved board.
 * \return true if file was successfully loaded, false if there was an error with file loading.
 */
bool LoadBoard(std::string filePath);
/*!
 * \brief Save board to file.
 * \param filepath - path to file where board will be saved.
 */
void SaveBoard(std::string filepath);
/*!
 * \brief Creating new board.
 * \param sizeX - board size x,
 * \param sizeY - board size y.
 */
void NewBoard(int sizeX, int sizeY);
/*!
 * \brief Method for checking if game is properly set.
 * \return true if game is set, else returns false.
 */
bool IsSet();
/*!
 * \brief Method for getting board size x.
 * \return size x of board.
 */
int GetBoardSizeX();
/*!
 * \brief Method for getting board size y.
 * \return size y of board.
 */
int GetBoardSizeY();
/*!
 * \brief Method toggles cell state in given coordinates.
 * \param x - cell x coordinate on board,
 * \param y - cell y coordinate on board.
 */
void ToggleCellState(int x, int y);
/*!
 * \brief Method checks cell state in given coordinates.
 * \param x - cell x coordinate on board,
 * \param y - cell y coordinate on board.
 * \return true if cell is alive and false if cell is not alive.
 */
bool IsCellAlive(int x, int y);
/*!
 * \brief Method sets game rule.
 * \param rule - game rule string representation.
 *
 * Rule must be given in format "L/D",
 * where L - number of alive cell neighbours, for which cell dies,
 * D - number of alive cell neighbours for which dead cell comes alive.
 * Eg: "23/3".
 */
void SetRule(std::string rule);

void SetCellColor(int x, int y, QColor color);

QColor GetCellColor(int x, int y);

void SetColorRule(int colorRule);

int GetColorRule();

private:
GameBoard board;
bool isSet;
std::string rule;
int colorRule;

int calculateNeighbours(int x, int y);
std::vector<Cell> getNeighbours(GameBoard &board, int x, int y);
void calculateNewBoard(GameBoard& newBoard);
void colorNewBoard(GameBoard& newBoard);
int calculateNeighbours(std::vector<Cell> &neighbours);
QColor getMostColor(std::vector<Cell> &neighbours, int colorRule);
};

#endif // GAME_H
