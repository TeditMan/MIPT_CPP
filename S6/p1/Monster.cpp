#include "Monster.h"

#include <iostream>
#include <array>
#include <string_view>

Monster::Monster(Monster::Type type, std::size_t yPos, std::size_t xPos)
    : m_type{ type }
    , m_pos{ std::array<std::size_t, 2>{yPos, xPos} }
{
    switch (m_type)
    {
    case Monster::barghest:
        m_health = 8;
        m_damage = 6;
        m_char = 'b';
        m_name = "Barghest";
        break;
    case Monster::drowner:
        m_health = 5;
        m_damage = 5;
        m_char = 'd';
        m_name = "Drowner";
        break;
    case Monster::ghoul:
        m_health = 15;
        m_damage = 12;
        m_char = 'g';
        m_name = "Ghoul";
        break;
    case Monster::golem:
        m_health = 30;
        m_damage = 30;
        m_char = 'm';
        m_name = "Golem";
        break;
    case Monster::troll:
        m_health = 20;
        m_damage = 15;
        m_char = 't';
        m_name = "Troll";
        break;
    case Monster::werewolf:
        m_health = 17;
        m_damage = 20;
        m_char = 'f';
        m_name = "Werewolf";
        break;
    case Monster::wraith:
        m_health = 14;
        m_damage = 7;
        m_char = 'w';
        m_name = "Wraith";
        break;
    case Monster::wyvern:
        m_health = 25;
        m_damage = 25;
        m_char = 'y';
        m_name = "Wyvern";
        break;
    default:
        std::cout << "None";
    }
}

std::ostream& operator<<(std::ostream& out, const Monster& monster)
{
    out << monster.m_name << ": " << "health: " << monster.m_health << " || "
        << "damage: " << monster.m_damage << " || "
        << "move CD: " << (1000 - monster.m_moveCounter) % monster.m_moveCD << " || "
        << "attack CD: " << (1002 - monster.m_attackCounter) % monster.m_attackCD << '\n';

    return out;
}
