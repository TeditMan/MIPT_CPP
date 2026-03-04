#include "Monster.h"
#include <cmath>

bool distanceLessThan(std::array<double, 3> a, std::array<double, 3> b, double condition)
{
    double distance{ std::pow(std::pow(a[0] - b[0], 2) + std::pow(a[1] - b[1], 2) + std::pow(a[2] - b[2], 2), 2) };
    if (distance < condition)
    {
        return true;
    }
    return false;
}

Monster::Monster(Monster::Type type, std::array<double, 3>) :
    m_type{ type }
{
    switch (m_type)
    {
    case Monster::barghest:
        m_health = 8;
        m_damage = 6;
        m_movementSpeed = 25;
        m_model = Globals::mDirectory.models[0];
        break;
    case Monster::drowner:
        m_health = 5;
        m_damage = 5;
        m_movementSpeed = 15;
        m_model = Globals::mDirectory.models[1];
        break;
    case Monster::ghoul:
        m_health = 15;
        m_damage = 12;
        m_movementSpeed = 12;
        m_model = Globals::mDirectory.models[2];
        break;
    case Monster::golem:
        m_health = 30;
        m_damage = 30;
        m_movementSpeed = 2;
        m_model = Globals::mDirectory.models[3];
        break;
    case Monster::troll:
        m_health = 20;
        m_damage = 15;
        m_movementSpeed = 6;
        m_model = Globals::mDirectory.models[4];
        break;
    case Monster::werewolf:
        m_health = 17;
        m_damage = 20;
        m_movementSpeed = 20;
        m_model = Globals::mDirectory.models[5];
        break;
    case Monster::wraith:
        m_health = 14;
        m_damage = 7;
        m_movementSpeed = 16;
        m_model = Globals::mDirectory.models[6];
        break;
    case Monster::wyvern:
        m_health = 25;
        m_damage = 25;
        m_movementSpeed = 25;
        m_model = Globals::mDirectory.models[7];
        break;
    }
}

Monster::Monster(const Monster& other)
{
    m_health = other.getHealth();
    m_damage = other.getDamage();
    m_pos = other.getPos();
    m_movementSpeed = other.getMS();
    m_model = other.getModel();
    m_type = other.getType();
    m_state = other.getState();
}

Monster& Monster::operator=(const Monster& other)
{
    m_health = other.getHealth();
    m_damage = other.getDamage();
    m_pos = other.getPos();
    m_movementSpeed = other.getMS();
    m_model = other.getModel();
    m_type = other.getType();
    m_state = other.getState();
}

void Monster::changeState(Game& game)
{
    if (distanceLessThan(m_pos, game.getPlayer().getPos(), m_alarmDistance))
    {
        m_state = alerted;
    }

    else if (distanceLessThan(m_pos, game.getPlayer().getPos(), m_agressiveDistance))
    {
        m_state = agressive;
    }

    else
    {
        m_state = idle;
    }
}

void Monster::attack(Game& game) const
{
    game.getPlayer().changeHealth(m_damage, 0);
}

void Monster::move(Game& game, std::array<double, 3> direction)
{
    m_pos[0] += m_movementSpeed * direction[0];
    m_pos[1] += m_movementSpeed * direction[1];
    m_pos[2] += m_movementSpeed * direction[2];
}

void Monster::render(Game& game) const
{
    if (distanceLessThan(game.getPlayer().getPos(), m_pos, m_renderDistance))
    {
        game.render(m_model);
    }
}
