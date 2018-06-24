#include "gamesettings.h"

GameSettings *GameSettings::GetInstance()
{
    return (instance ? instance :
            instance = new GameSettings());
}

int GameSettings::GetSimulationInterval()
{
    return simulationInterval;
}

void GameSettings::SetSimulationInterval(int interval)
{
    simulationInterval = interval;
}

bool GameSettings::GetBoardWraping()
{
    return boardWraping;
}

void GameSettings::SetBoardWraping(bool wraping)
{
    boardWraping = wraping;
}

GameSettings* GameSettings::instance = nullptr;

GameSettings::GameSettings()
{
    boardWraping = false;
    simulationInterval = 500;
}
