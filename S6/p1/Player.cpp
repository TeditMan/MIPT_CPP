#include "Player.h"
#include "Unit.h"

#include <iostream>

Player::Player(int health, int damage, std::size_t y_pos, std::size_t x_pos)
    : Unit(y_pos, x_pos)
{
    m_health = health;
    m_damage = damage;
    m_symbol = 'A';
}

void Player::changeState()
{
    if (m_symbol == 'A') m_symbol = 'B';
    else m_symbol = 'A';
}

std::ostream& operator<<(std::ostream& out, const Player& player)
{
    out << "You have " << player.m_health << " health left. Your damage is " << player.m_damage << ".\n";
    return out;
}