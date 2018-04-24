#ifndef CELL_H
#define CELL_H


class Cell
{
public:
Cell();
bool IsAlive();
void SetState(bool alive);
void ToggleState();

private:
bool alive;
};

#endif // CELL_H
