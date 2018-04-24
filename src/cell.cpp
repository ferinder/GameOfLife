#include "cell.h"

Cell::Cell()
{
    alive = false;
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
