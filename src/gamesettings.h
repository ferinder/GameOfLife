#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

/*!
 * \brief The GameSettings class
 * Game setting class which implements singleton design pattern.
 */
class GameSettings
{
public:
/*!
 * \brief Get instance of settings singleton.
 * \return
 */
static GameSettings *GetInstance();
/*!
 * \brief Get current simulation interval setting.
 * \return time interval in ms.
 */
int GetSimulationInterval();
/*!
 * \brief Sets simulation interval setting.
 * \param interval - time interval between calculating new board in ms.
 */
void SetSimulationInterval(int interval);
/*!
 * \brief Get game board wrapping setting.
 * \return true if board is wraping, false if not.
 */
bool GetBoardWraping();

/*!
 * \brief Ses game board wrapping setting.
 * \param wraping - new setting.
 */
void SetBoardWraping(bool wraping);

private:
static GameSettings *instance;
GameSettings();

bool boardWraping;
int simulationInterval;
};

#endif // GAMESETTINGS_H
