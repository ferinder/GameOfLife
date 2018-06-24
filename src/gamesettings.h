#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H


class GameSettings
{
public:
static GameSettings *GetInstance();

int GetSimulationInterval();
void SetSimulationInterval(int interval);

bool GetBoardWraping();
void SetBoardWraping(bool wraping);

private:
static GameSettings *instance;
GameSettings();

bool boardWraping;
int simulationInterval;
};

#endif // GAMESETTINGS_H
