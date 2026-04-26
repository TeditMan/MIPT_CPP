#include "Game.h"
#include "Grid.h"
#include "Player.h"
#include "Monster.h"
#include "Random.h"

#include <iostream>
#include <cstdlib>
#include <limits>
#include <array>


int Game::getDifficulty()
{
	int number{};

	while (true)
	{
		std::cout << "Choose a difficulty level from 1 to 3: ";
		std::cin >> number;

		if (!std::cin)
		{
			if (std::cin.eof())
			{
				std::exit(0);
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Try again.\n";
			continue;
		}

		if (!std::cin.eof() && std::cin.peek() != '\n')
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Try again.\n";
			continue;
		}

		if (number < 1 || number > 3)
		{
			std::cout << "Invalid input. Try again.\n";
			continue;
		}

		break;
	}

	return number;
}

Game::Game()
{
	int dLevel{ getDifficulty() };
	std::size_t ySize = m_grid.s_ySize;
	std::size_t xSize = m_grid.s_xSize;

	int health{};
	int damage{};
	int numberOfMonsters{};

	switch (dLevel)
	{
	case 1:
		health = 120;
		damage = 12;
		numberOfMonsters = 6;
		break;
	case 2: 
		health = 100;
		damage = 10;
		numberOfMonsters = 8;
		break;
	case 3:
		health = 80;
		damage = 8;
		numberOfMonsters = 10;
		break;
	}

	m_player = Player(health, damage, ySize / 2, xSize / 2);

	for (std::size_t i{}; i < numberOfMonsters; ++i)
	{
		bool keep{ true };
		Monster newMonster{};

		while (keep)
		{
			keep = false;
			newMonster = Monster
			(
				static_cast<Monster::Type>(Random::get(0, 7)),
				Random::get<std::size_t>(0, ySize - 1),
				Random::get<std::size_t>(0, xSize - 1)
			);

			for (const Monster& monster : m_monsters)
			{
				if (monster.getPos() == newMonster.getPos())
				{
					keep = true;
				}
			}

			if (newMonster.getPos() == m_player.getPos()) keep = true;
		}

		m_monsters.push_back(newMonster);
	}

    m_grid = Grid(m_player, m_monsters);
	m_grid.update();
}

void Game::writeReport()
{
	std::cout << m_player;

	int counter{};
	std::cout << "Monsters in radius:\n";

	for (const Monster& monster : m_monsters)
	{
		if ((m_player | monster) < monster.s_agressiveDistance && monster.getSymbol() != 'X')
		{
			++counter;
			std::cout << monster;
		}
	}
	if (!counter) std::cout << "None.\n";
}

void Game::run()
{
	bool over{};
	bool allDead{};

	while (!over)
	{
		std::cout << m_grid;
		writeReport();

		over = m_grid.playerMove();
		allDead = m_grid.enemyMove();
	
		if (allDead)
		{
            std::cout << m_grid;
			std::cout << "\n\nAll enemies are dead.\n";
			over = true;
		}
		if (m_player.getHealth() <= 0)
		{
			std::cout << m_grid;
			std::cout << "\n\nYou are dead.\n";
			over = true;
		}

	}
	std::cout << "Game over.\n";
}