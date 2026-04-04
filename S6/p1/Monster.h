#pragma once
#include <array>
#include <iostream>
#include <string_view>

class Monster
{
public:
    enum Type
    {
        drowner,
        ghoul,
        troll,
        wraith,
        golem,
        wyvern,
        barghest,
        werewolf
    };

private:
    const int m_agressiveDistance{ 6 };
    const int m_attackCD{ 3 };
    const int m_moveCD{ 2 };

    Type m_type{};
    std::array<std::size_t, 2> m_pos{};
    int m_health{};
    int m_damage{};
    bool m_dead{ false };
    char m_char{'X'};
    std::string_view m_name{};

    int m_moveCounter{};
    int m_attackCounter{};

public:
    Monster() = default;

    Monster(Type type, std::size_t yPos, std::size_t xPos);

    ~Monster() = default;

    Monster(const Monster& monster)
    {
        m_type = monster.m_type;
        m_pos = monster.m_pos;
        m_health = monster.m_health;
        m_damage = monster.m_damage;
        m_dead = monster.m_dead;
        m_char = monster.m_char;
        m_name = monster.m_name;
    }

    Monster& operator= (const Monster& monster)
    {
        if (this == &monster) return *this;
        m_type = monster.m_type;
        m_pos = monster.m_pos;
        m_health = monster.m_health;
        m_damage = monster.m_damage;
        m_dead = monster.m_dead;
        m_char = monster.m_char;
        m_name = monster.m_name;
        return *this;
    }

    char getChar() const
    {
        std::cout << m_char << '\n';
        return m_char;
    }

    std::string_view getName() const
    {
        return m_name;
    }
    
    friend std::ostream& operator<<(std::ostream& out, const Monster& monster);

    Monster& operator+=(int value)
    {
        m_health += value;
        return *this;
    }

    Monster& operator-=(int value)
    {
        m_health -= value;
        return *this;
    }

    int getDamage() const
    {
        return m_damage;
    }


    friend class Game;

};
