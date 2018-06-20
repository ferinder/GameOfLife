#include "cell.h"

Cell::Cell()
{
    this->alive = false;
    this->color = Qt::black;
}

Cell::Cell(bool alive)
{
    this->alive = alive;
    this->color = Qt::black;
}

bool Cell::IsAlive()
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

QColor Cell::GetColor()
{
    return this->color;
}
