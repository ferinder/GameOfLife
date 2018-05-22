#ifndef CELL_H
#define CELL_H

/*!
 * \brief The Cell class
 *
 * Class represents single cell.
 */
class Cell
{
public:
/*!
 * \brief Cell default constructor.
 *
 * Constructs Cell and initialize its state with false, what means, cell is not alive.
 */
Cell();
/*!
 * \brief Cell constructor with custom state initialization.
 * \param alive - cell state for initialization.
 *
 * Constructs Cell an initialize its state with parameter alive.
 */
Cell(bool alive);
/*!
 * \brief Method returns cell state.
 * \return cell state.
 *
 * If cell is alive, method return true, otherwise returns false.
 */
bool IsAlive();
/*!
 * \brief Method sets cell state acording to parameter.
 * \param alive - new cell state.
 */
void SetState(bool alive);
/*!
 * \brief Toggles cell state from true to false and otherwise.
 */
void ToggleState();

private:
bool alive; ///< Propertie holds cell state.
};

#endif // CELL_H
