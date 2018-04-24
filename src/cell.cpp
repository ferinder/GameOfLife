#include "cell.h"

Cell::Cell()
{
    state = false;
}

bool Cell::GetState()
{
    return state;
}

void Cell::SetState(bool state)
{
    this->state = state;
}

void Cell::ToggleState()
{
    if(state) state = false;
    else state = true;
}
