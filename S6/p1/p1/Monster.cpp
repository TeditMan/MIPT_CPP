#include "Monster.h"
#include <cmath>
#include <iostream>

// техническая функция
bool distanceLessThan(std::array<double, 3> a, std::array<double, 3> b, double condition)
{
    double distance{ std::pow(std::pow(a[0] - b[0], 2) + std::pow(a[1] - b[1], 2) + std::pow(a[2] - b[2], 2), 2) };
    if (distance < condition)
    {
        return true;
    }
    return false;
}


// конструктор
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

// конструктор копирования
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

// конструктор оператора копирования
Monster& Monster::operator=(const Monster& other)
{
    if (this != &other)
    {
        m_health = other.getHealth();
        m_damage = other.getDamage();
        m_pos = other.getPos();
        m_movementSpeed = other.getMS();
        m_model = other.getModel();
        m_type = other.getType();
        m_state = other.getState();
    }
    return *this;
}

// изменение состояния 
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

// атака(нанесение урона игроку)
void Monster::attack(Game& game) const
{
    std::cout << "Monster deals " << m_damage << " to the player \n\n";
    game.getPlayer() -= m_damage;
}

// смена позиции
void Monster::move(std::array<double, 3> direction)
{
    m_pos[0] += m_movementSpeed * direction[0];
    m_pos[1] += m_movementSpeed * direction[1];
    m_pos[2] += m_movementSpeed * direction[2];
}

// отрендерить
void Monster::render(Game& game) const
{
    if (distanceLessThan(game.getPlayer().getPos(), m_pos, m_renderDistance))
    {
        game.render(m_model);
    }
}

// перегрузка операторов

Monster& Monster::operator+=(int value)
{
    m_health += value;
    return *this;
}

Monster& Monster::operator-=(int value)
{
    m_health -= value;
    return *this;
}

Monster& Monster::operator*=(int value)
{
    m_health *= value;
    return *this;
}

Monster& Monster::operator/=(int value)
{
    m_health /= value;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Monster& monster)
{
    out << "Monster type: ";

    switch (monster.m_type)
    {
    case Monster::drowner:
        out << "drowner";
        break;
    case Monster::ghoul:
        out << "ghoul";
        break;
    case Monster::troll:
        out << "troll";
        break;
    case Monster::wraith:
        out << "wraith";
        break;
    case Monster::golem:
        out << "golem";
        break;
    case Monster::wyvern:
        out << "wyvern";
        break;
    case Monster::barghest:
        out << "barghest";
        break;
    case Monster::werewolf:
        out << "werewolf";
        break;
    }
    
    out << "\n" << "Current health: " << monster.m_health << '\n'
        << "Damage amount: " << monster.m_damage << '\n'
        << "Movement speed: " << monster.m_movementSpeed << '\n'
        << "State: " << monster.m_state << "\n\n";

    return out;
}