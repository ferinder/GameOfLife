#include "game.h"

#include <QIODevice>
#include <QTime>

Game::Game()
{
    isSet = false;
    rule = "12345/3";
}

void Game::RunSimulation(int steps)
{
    QTime timer;
    timer.start();
    int splitIndex = this->rule.find('/');
    std::string live = this->rule.substr(0,splitIndex);
    std::string die = this->rule.substr(splitIndex+1);
    for(int s = 0; s < steps; s++)
    {
        GameBoard newBoard(this->board);
        int boardSizeX = this->board.GetSizeX();
        int boardSizeY = this->board.GetSizeY();
//        qDebug() << "Rule: " << rule.c_str() << "live: " << live.c_str() << "Die: " << die.c_str();
        for (int x = 0; x < boardSizeX; x++)
        {
            for(int y = 0; y < boardSizeY; y++)
            {
                int AliveNeighbours = calculateNeighbours(x,y);
                bool stateNeedsChange = false;
                if(this->board(x,y).IsAlive())
                {
                    for(auto ch : live)
                    {
                        if(AliveNeighbours != (int(ch) - 48))
                        {
                            stateNeedsChange = true;
                        }
                        else
                        {
                            stateNeedsChange = false;
                            break;
                        }
                    }
                }
                else
                {
                    for(auto ch : die)
                    {
                        if(AliveNeighbours != (int(ch) - 48))
                        {
                            stateNeedsChange = false;
                        }
                        else
                        {
                            stateNeedsChange = true;
                            break;
                        }
                    }
                }
//                qDebug() << "Cell:" << x << y << AliveNeighbours << board(x,y).IsAlive() << stateNeedsChange;
                if(stateNeedsChange) newBoard(x,y).ToggleState();
                stateNeedsChange = false;
            }
        }
        this->board = newBoard;
    }
    qDebug() << "Time: " << timer.elapsed();
}

bool Game::LoadBoard(std::string filePath)
{
    std::ifstream file(filePath);
    if(file.is_open())
    {
        std::string line;
        std::getline(file, line);
        int sizeX = std::stoi(line);

        std::getline(file, line);
        int sizeY = std::stoi(line);

        std::vector<Cell> cells;
        cells.reserve(sizeX * sizeY);

        std::getline(file, line);
        for(auto ch : line)
        {
            if(ch == '0')
            {
                cells.push_back(Cell(false));
            }
            else if(ch == '1')
            {
                cells.push_back(Cell(true));
            }
            else
            {
                qDebug() << "Error with getting cell state!";
            }
        }
        file.close();
        this->board = GameBoard(sizeX, sizeY, cells);
        isSet = true;
        return true;
    }
    else
    {
        qDebug() << "Error with reading file!";
        return false;
    }

}

void Game::SaveBoard(std::string filepath)
{
    std::ofstream file;
    file.open(filepath);
    if(file.is_open())
    {
        file << this->GetBoardSizeX() << '\n';
        file << this->GetBoardSizeY() << '\n';

        for(int idx = 0;
            idx < this->board.GetSizeX() * this->GetBoardSizeY();
            idx++)
        {
            if(this->board(idx).IsAlive())
            {
                file.put('1');
            }
            else
            {
                file.put('0');
            }
        }
        file.close();
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
