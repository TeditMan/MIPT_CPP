#include "Unit.h"

#include <array>

Unit::Unit(std::size_t y_pos, std::size_t x_pos)
    : m_pos{ std::array<std::size_t, 2>{y_pos, x_pos} }
{ }

void Unit::move1(char direction)
{
    auto& [y, x] = m_pos;
    switch (direction)
    {
    case 'w':
        --y;
        break;
    case 'a':
        --x;
        break;
    case 's':
        ++y;
        break;
    case 'd':
        ++x;
        break;
    default:
        break;
    }
}

void Unit::receiveDamage(int damage)
{
    m_health -= damage;
}