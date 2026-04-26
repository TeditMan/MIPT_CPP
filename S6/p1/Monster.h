#pragma once
#include "Unit.h"

#include <iostream>
#include <string_view>

class Grid;
class Player;

class Monster : public Unit
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

    Monster(Type type, std::size_t yPos, std::size_t xPos);
    Monster() = default;

    std::string_view getName() const { return m_name; }

    void eliminate() { m_symbol = 'X'; }

    friend std::ostream& operator<<(std::ostream& out, const Monster& monster);

    static constexpr int s_agressiveDistance{ 6 };
    int m_moveCounter{};
    int m_attackCounter{};

private:
    Type m_type{};
    std::string_view m_name{};

};
