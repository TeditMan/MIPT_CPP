#pragma once

#include <array>
#include <cmath>

class Unit
{
public:
    Unit(std::size_t y_pos, std::size_t x_pos);
    Unit() = default;

    std::array<std::size_t, 2>   getPos()    const { return m_pos; }
    char                         getSymbol() const { return m_symbol; }
    int                          getHealth() const { return m_health; }
    int                          getDamage() const { return m_damage; }
    int                          getMoveCD() const { return m_moveCD; }
    int                          getAttackCD() const { return m_attackCD; }


    void  move1          (char direction);

    template <typename T>
    void operator>>(T& unit) const
    {       
        unit.receiveDamage(m_damage);   
    }
    
    template <typename T>
    int operator|(const T& unit) const
    {
        auto [y1, x1] = m_pos;
        auto [y2, x2] = unit.getPos();
        return
            static_cast<int>
            (sqrt(
                pow(static_cast<double>(y1) - static_cast<double>(y2), 2)
                + pow(static_cast<double>(x1) - static_cast<double>(x2), 2)
            ));
    }
    

protected:
    void  receiveDamage  (int damage);

    std::array<std::size_t, 2> m_pos{};
    int m_health{};
    int m_damage{};
    int m_moveCD{};
    int m_attackCD{};
    char m_symbol{};
};