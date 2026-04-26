#pragma once

#include "Monster.h"
#include "Player.h"


#include <array>
#include <vector>
#include <iostream>


class Grid
{
public:
    Grid(Player& player, std::vector<Monster>& monsters);
    Grid() = default;

    template <typename T>
    bool move(T& unit, char direction);

    void update();

    bool enemyMove();

    bool playerMove();

    friend std::ostream& operator<<(std::ostream& out, const Grid& grid);

    static constexpr std::size_t s_ySize{ 30 };
    static constexpr std::size_t s_xSize{ 30 };

private:
    Player* p_player{};
    std::vector<Monster*> vp_monsters{};

    std::array<std::array<char, s_xSize>, s_ySize> m_grid{};
};