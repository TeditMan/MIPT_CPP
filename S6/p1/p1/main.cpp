#include <iostream>
#include "Monster.h"
#include <array>

int main()
{
	Game game{1};
	std::array<double, 3> mPos{ 10, 10, 10 };
	Monster enemy1{ Monster::barghest, mPos };

	std::cout << enemy1;
	game.printPlayer();
	enemy1.attack(game);
	game.printPlayer();

	return 0;
}
