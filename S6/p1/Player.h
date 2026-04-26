#pragma once
#include "Unit.h"

#include <iostream>

class Player : public Unit
{
public:
    Player(int health, int damage, std::size_t yPos, std::size_t xPos);
    Player() = default;

    void changeState();

    friend std::ostream& operator<<(std::ostream& out, const Player& player);
};