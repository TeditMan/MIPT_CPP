#pragma once
#include <array>


class Player
{
private:
    int m_health{};
    int m_damage{};
    std::array<std::size_t, 2> m_pos{};
    char m_state{'A'};
    bool m_dead{ false };

public:
    Player() = default;
    
    Player(int health, int damage, std::size_t yPos, std::size_t xPos);

    ~Player() = default;

    Player(const Player& player) = default;

    Player& operator= (const Player& player)
    {
        if (this == &player) return *this;
        m_health = player.m_health;
        m_damage = player.m_damage;
        m_pos = player.m_pos;
        m_state = player.m_state;
        m_dead = player.m_dead;
        return *this;
    }

    Player& operator+=(int value)
    {
        m_health += value;
        return *this;
    }

    Player& operator-=(int value)
    {
        m_health -= value;
        return *this;
    }

    int getDamage() const
    {
        return m_damage;
    }

    char getChar() const
    {
        return m_state;
    }

    friend class Game;
};
