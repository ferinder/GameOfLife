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
    int cellNumber = newBoard.GetSizeX() * newBoard.GetSizeY();
    if(this->colorRule == Default)
    {
        for(int i = 0; i < cellNumber; i++)
        {
            if(newBoard(i).IsAlive())
                newBoard(i).SetColor(Qt::black);
            else
                newBoard(i).SetColor(Qt::white);
        }
    }
    else
    {
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
                QColor color = getMostColor(oldNeighbours, this->colorRule);
                newBoard(i).SetColor(color);
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
        this->SetColorRule(std::stoi(line));
        if(this->GetColorRule() != ColorRule::Default)
            this->SetRule("23/3");

        std::getline(file,line);
        int sizeX = std::stoi(line);

        std::getline(file, line);
        int sizeY = std::stoi(line);

        std::vector<Cell> cells;
        cells.reserve(sizeX * sizeY);

        std::getline(file, line);
        for(auto ch : line)
        {
            switch (ch) {
            case '0':
                cells.push_back(Cell(false));
                break;
            case '1': //black
                cells.push_back(Cell(true));
                break;
            case '2': //red
                cells.push_back(Cell(true, Qt::red));
                break;
            case '3': //blue
                cells.push_back(Cell(true, Qt::blue));
                break;
            case '4': //green
                cells.push_back(Cell(true, Qt::green));
                break;
            case '5': //magenta
                cells.push_back(Cell(true, Qt::magenta));
                break;
            default:
                qDebug() << "Error with getting cell state!";
                file.close();
                return false;
                break;
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
        file << this->GetColorRule() << '\n';
        file << this->GetBoardSizeX() << '\n';
        file << this->GetBoardSizeY() << '\n';

        for(int idx = 0;
            idx < this->board.GetSizeX() * this->GetBoardSizeY();
            idx++)
        {
            if(this->board(idx).IsAlive())
            {
                QColor color = this->board(idx).GetColor();
                if(color == Qt::black)
                    file.put('1');
                else if(color == Qt::red)
                    file.put('2');
                else if(color == Qt::blue)
                    file.put('3');
                else if(color == Qt::green)
                    file.put('4');
                else if(color == Qt::magenta)
                    file.put('5');
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
        mostColor = Qt::black;
        break;
    case ColorRule::Immigration:
    {
        int red = 0;
        int blue = 0;
        for(auto it : neighbours)
        {
            QColor color = it.GetColor();
            if(color == Qt::red)
                red += 1;
            else if(color == Qt::blue)
                blue += 1;
        }
        if(red > blue) mostColor = Qt::red;
        else mostColor = Qt::blue;
    }
    break;
    case ColorRule::QuadLife:
    {
        std::vector<std::pair<QColor, int> > neighboursColors;
        neighboursColors.push_back(std::make_pair(Qt::red, 0));
        neighboursColors.push_back(std::make_pair(Qt::blue, 0));
        neighboursColors.push_back(std::make_pair(Qt::green, 0));
        neighboursColors.push_back(std::make_pair(Qt::magenta, 0));

        for(auto it : neighbours)
        {
            QColor color = it.GetColor();
            if(color == Qt::red)
                neighboursColors[0].second += 1;
            else if(color == Qt::blue)
                neighboursColors[1].second += 1;
            else if(color == Qt::green)
                neighboursColors[2].second += 1;
            else if(color == Qt::magenta)
                neighboursColors[3].second += 1;
        }
        std::sort(neighboursColors.begin(),neighboursColors.end(),
                  [](std::pair<QColor, int> a, std::pair<QColor, int> b)
            {
                return a.second > b.second;
            });
        if(neighboursColors[0].second == 1)
            mostColor = neighboursColors[3].first;
        else
            mostColor = neighboursColors[0].first;
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
