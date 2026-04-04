#pragma once

#include "Player.h"
#include "Monster.h"

#include <vector>
#include <array>

class Game
{
private:
    static const std::size_t m_sizeX{ 30 };
    static const std::size_t m_sizeY{ 30 };

    std::array<std::array<char, m_sizeX>, m_sizeY> m_board{ {} };

    Player m_player{};

    std::vector<Monster> m_monstersVector{};

public:
    Game();

    void run();

    void render();
    
    template <typename T>
    bool move(T&, char);

    template <typename T, typename V>
    int distance(T&, V&);

    void writeReport();

    void updateBoard();
};

template <typename T, typename V>
void operator>> (T& left, V& right)
{
    right -= left.getDamage();
}
