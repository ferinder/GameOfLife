#include "cell.h"

Cell::Cell()
{
    this->alive = false;
    this->color = Qt::white;
}

Cell::Cell(bool alive)
{
    this->alive = alive;
    if(alive)
        this->color = Qt::black;
    else
        this->color = Qt::white;
}

Cell::Cell(bool alive, QColor color)
{
    this->alive = alive;
    if(alive)
        this->color = color;
    else
        this->color = Qt::white;
}

bool Cell::IsAlive() const
{
    return alive;
}

void Cell::SetState(bool state)
{
    this->alive = state;
}

void Cell::ToggleState()
{
    if(alive) alive = false;
    else alive = true;
}

void Cell::SetColor(QColor color)
{
    this->color = color;
}

QColor Cell::GetColor() const
{
    return this->color;
}
