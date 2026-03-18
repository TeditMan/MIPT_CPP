#include <iostream>
#include "Monster.h"
#include <array>

int main()
{
	Player player1{};
	Game game{player1, 1};
	std::array<double, 3> mPos{ 10, 10, 10 };
	Monster enemy1{ Monster::barghest, mPos };

	std::cout << enemy1.getHealth() << '\n' << enemy1.getDamage() << '\n';
	std::cout << game.getPlayer().getHealth() << '\n';
	enemy1.attack(game);
	std::cout << game.getPlayer().getHealth();

	return 0;
}
