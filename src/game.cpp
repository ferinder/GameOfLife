#include "game.h"

#include <QIODevice>
#include <QTime>

Game::Game()
{
    isSet = false;
    rule = "23/3";
    colorRule = ColorRule::Default;
}

void Game::calculateNewBoard(GameBoard &newBoard)
{
    int boardSizeX = newBoard.GetSizeX();
    int boardSizeY = newBoard.GetSizeY();
    int splitIndex = this->rule.find('/');
    std::string live = this->rule.substr(0,splitIndex);
    std::string die = this->rule.substr(splitIndex+1);
    for (int x = 0; x < boardSizeX; x++)
    {
        for(int y = 0; y < boardSizeY; y++)
        {
            std::vector<Cell> neighbours = getNeighbours(this->board, x, y);
            int AliveNeighbours = calculateNeighbours(neighbours);
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
            if(stateNeedsChange) newBoard(x,y).ToggleState();
            stateNeedsChange = false;
        }
    }
}

void Game::colorNewBoard(GameBoard &newBoard)
{
    switch (this->colorRule) {
    case ColorRule::Default:
    {
        int cellNumber = newBoard.GetSizeX() * newBoard.GetSizeY();
        for(int i = 0; i < cellNumber; i++)
        {
            if(newBoard(i).IsAlive())
                newBoard(i).SetColor(Qt::black);
            else
                newBoard(i).SetColor(Qt::white);
        }
    }
    break;
    case ColorRule::Immigration:
    {
        int cellNumber = newBoard.GetSizeX() * newBoard.GetSizeY();
        bool cellCameAlive = false;
        for(int i = 0; i < cellNumber; i++)
        {
            if((!this->board(i).IsAlive() && newBoard(i).IsAlive()))
                cellCameAlive = true;
            else
                cellCameAlive = false;

            if(cellCameAlive)
            {
                int idxX = i % this->GetBoardSizeX();
                int idxY = i / this->GetBoardSizeX();
                std::vector<Cell> oldNeighbours = getNeighbours(this->board, idxX, idxY);
                int aliveOldNeighbours = calculateNeighbours(oldNeighbours);

                if(aliveOldNeighbours == 3)
                {
                    QColor color = getMostColor(oldNeighbours, ColorRule::Immigration);
                    newBoard(i).SetColor(color);
                }
            }
            else
            {
                if(newBoard(i).IsAlive())
                    newBoard(i).SetColor(this->board(i).GetColor());
                else
                    newBoard(i).SetColor(Qt::white);
            }
        }

    }
    break;
    case ColorRule::QuadLife:
    {

    }
    break;
    default:
        break;
    }
}

void Game::RunSimulation()
{
    QTime timer;
    timer.start();
    GameBoard newBoard(this->board);
//    qDebug() << "Rule: " << rule.c_str() << "live: " << live.c_str() << "Die: " << die.c_str();
    calculateNewBoard(newBoard);
    colorNewBoard(newBoard);
    this->board = newBoard;
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

int Game::calculateNeighbours(std::vector<Cell> & neighbours)
{
    int aliveNeighbours = 0;
    for(auto it = neighbours.cbegin(); it != neighbours.cend(); it++)
    {
        if( (*it).IsAlive()) aliveNeighbours += 1;
    }
    return aliveNeighbours;
}

QColor Game::getMostColor(std::vector<Cell> &neighbours, int colorRule)
{
    QColor mostColor;
    switch (colorRule) {
    case ColorRule::Default:
        break;
    case ColorRule::Immigration:
    {
        int red = 0;
        int yellow = 0;
        for(auto it : neighbours)
        {
            if(it.GetColor() == Qt::red) red += 1;
            else yellow += 0;
        }
        if(red > yellow) mostColor = Qt::red;
        else mostColor = Qt::blue;
    }
    break;
    case ColorRule::QuadLife:
    {

    }
    break;
    default:
        break;
    }
    return mostColor;
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

std::vector<Cell> Game::getNeighbours(GameBoard& board, int x, int y)
{
    std::vector<Cell> neighbours;
    neighbours.reserve(8);
    int boardSizeX = board.GetSizeX();
    int boardSizeY = board.GetSizeY();
    int idxX, idxY;
    for(int i = -1; i < 2; i++)
    {
        if( (x + i) < 0) idxX = boardSizeX - 1;
        else if( (x + i) >= boardSizeX) idxX = 0;
        else idxX = x + i;
        for (int j = -1; j < 2; j++)
        {
            if( i == 0 && j == 0) continue;
            if( (y + j) < 0) idxY = boardSizeY - 1;
            else if( (y + j) >= boardSizeY) idxY = 0;
            else idxY = y + j;
            neighbours.push_back(board(idxX, idxY));
        }
    }
    return neighbours;
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

bool Game::IsCellAlive(int x, int y)
{
    return board(x,y).IsAlive();
}

void Game::SetRule(std::string rule)
{
    this->rule = rule;
}

void Game::SetCellColor(int x, int y, QColor color)
{
    this->board(x,y).SetColor(color);
}

QColor Game::GetCellColor(int x, int y)
{
    return this->board(x,y).GetColor();
}

void Game::SetColorRule(int colorRule)
{
    this->colorRule = colorRule;
}

int Game::GetColorRule()
{
    return this->colorRule;
}
