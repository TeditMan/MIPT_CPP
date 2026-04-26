#pragma once

#include "Player.h"
#include "Monster.h"
#include "Grid.h"

#include <vector>

class Game
{
private:
    Player m_player{};
    std::vector<Monster> m_monsters{};
    Grid m_grid{};

public:
    Game();

    int getDifficulty();

    void writeReport();

    void run();
};