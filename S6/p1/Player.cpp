#include "Player.h"
#include <array>

Player::Player(int health, int damage, std::size_t yPos, std::size_t xPos)
    : m_health{health}
    , m_damage{damage}
    , m_pos{ std::array<std::size_t, 2>{yPos, xPos} }
{ }
