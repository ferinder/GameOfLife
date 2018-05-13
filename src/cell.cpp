#include "cell.h"

Cell::Cell()
{
    this->alive = false;
}

Cell::Cell(bool alive)
{
    this->alive = alive;
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
