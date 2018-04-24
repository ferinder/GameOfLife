#ifndef CELL_H
#define CELL_H


class Cell
{
public:
    Cell();
    bool GetState();
    void SetState(bool state);
    void ToggleState();

private:
    bool state;
};

#endif // CELL_H
