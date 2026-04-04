#include "Game.h"
#include "Player.h"
#include "Monster.h"
#include "Random.h"

#include <iostream>
#include <cstdlib>
#include <limits>
#include <array>
#include <cmath>

Game::Game()
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

	int health{};
	int damage{};
	int numberOfMonsters{};

	switch (number)
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

	m_player = Player(health, damage, m_sizeY / 2, m_sizeX / 2);

	for (std::size_t i{}; i < numberOfMonsters; ++i)
	{
		Monster newMonster{};
		bool keep{ true };

		while (keep)
		{
			keep = false;
			newMonster = Monster(static_cast<Monster::Type>(Random::get(0, 7)),
				Random::get<std::size_t>(0, m_sizeY - 1), Random::get<std::size_t>(0, m_sizeX - 1));

			for (const Monster& monster : m_monstersVector)
			{
				if (monster.m_pos == newMonster.m_pos)
				{
					keep = true;
				}
			}

			if (newMonster.m_pos == m_player.m_pos) keep = true;
		}

		m_monstersVector.push_back(newMonster);
	}

	updateBoard();
}

void Game::updateBoard()
{
	for (std::size_t i{}; i < m_sizeY; ++i)
	{
		for (std::size_t j{}; j < m_sizeX; ++j)
		{
			m_board[i][j] = '-';
		}
	}

	m_board[m_player.m_pos[0]][m_player.m_pos[1]] = m_player.getChar();

	for (const Monster& monster : m_monstersVector)
	{
		m_board[monster.m_pos[0]][monster.m_pos[1]] = monster.m_char;
	}
}

template <typename T>
bool Game::move(T& obj, char c)
{
	switch (c)
	{
	case 'w':
		if (obj.m_pos[0] != 0)
		{
			if (m_board[obj.m_pos[0] - 1][obj.m_pos[1]] == '-')
			{
				m_board[obj.m_pos[0] - 1][obj.m_pos[1]] = obj.getChar();
				m_board[obj.m_pos[0]][obj.m_pos[1]] = '-';
				obj.m_pos[0] -= 1;
				return true;
			}
		}
		break;
	case 'a':
		if (obj.m_pos[1] != 0)
		{
			if (m_board[obj.m_pos[0]][obj.m_pos[1] - 1] == '-')
			{
				m_board[obj.m_pos[0]][obj.m_pos[1] - 1] = obj.getChar();
				m_board[obj.m_pos[0]][obj.m_pos[1]] = '-';
				obj.m_pos[1] -= 1;
				return true;
			}
		}
		break;
	case 's':
		if (obj.m_pos[0] != m_sizeY - 1)
		{
			if (m_board[obj.m_pos[0] + 1][obj.m_pos[1]] == '-')
			{
				m_board[obj.m_pos[0] + 1][obj.m_pos[1]] = obj.getChar();
				m_board[obj.m_pos[0]][obj.m_pos[1]] = '-';
				obj.m_pos[0] += 1;
				return true;
			}
		}
		break;
	case 'd':
		if (obj.m_pos[1] != m_sizeX - 1)
		{
			if (m_board[obj.m_pos[0]][obj.m_pos[1] + 1] == '-')
			{
				m_board[obj.m_pos[0]][obj.m_pos[1] + 1] = obj.getChar();
				m_board[obj.m_pos[0]][obj.m_pos[1]] = '-';
				obj.m_pos[1] += 1;
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}

template <typename T, typename V>
int Game::distance(T& left, V& right)
{	
	return static_cast<int>(sqrt(
		pow(static_cast<double>(left.m_pos[0]) - static_cast<double>(right.m_pos[0]), 2)
	  + pow(static_cast<double>(left.m_pos[1]) - static_cast<double>(right.m_pos[1]), 2)
	));
}

void Game::render()
{
	for (std::size_t i{}; i < m_sizeY; ++i)
	{
		for (std::size_t j{}; j < m_sizeX; ++j)
		{
			std::cout << m_board[i][j];
		}
		std::cout << '\n';
	}
}

void Game::writeReport()
{
	std::cout << "You have " << m_player.m_health << " health left, and your damage is " << m_player.m_damage << ".\n";

	int counter{};
	std::cout << "Monsters in radius:\n";

	for (const Monster& monster : m_monstersVector)
	{
		if (distance(m_player, monster) < monster.m_agressiveDistance && !monster.m_dead) 
		{
			++counter;
			std::cout << monster;
		}
	}
	if (!counter) std::cout << "None.\n";
}

void Game::run()
{

	bool done{};

	while (!done)
	{
		render();
		writeReport();

		char input{};

		while (true)
		{
			std::cout << "\nMake move (wasd) || Attack (x) || Change state (z) || Skip move (c) || Exit game (e) || Reference (q)\n";
			std::cin >> input;

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

			switch (input)
			{
			case 'w':
			case 'a':
			case 's':
			case 'd':
				if (!move(m_player, input))
				{
					std::cout << "Can't move there. Try again.\n";
					continue;
				}
				
				break;
			case 'x':
				if (m_player.m_state == 'A')
				{
					for (Monster& monster : m_monstersVector)
					{
						if (!monster.m_dead && distance(monster, m_player) == 1)
						{
							m_player >> monster;
							std::cout << monster.getName() << " receives " << m_player.m_damage << " damage.\n";
							if (monster.m_health < 0)
							{
								std::cout << monster.getName() << " is eliminated.\n";
								monster.m_char = 'X';
								monster.m_dead = true;
								updateBoard();
							}
						}
					}
				}
				else
				{
					std::cout << "You can't attack while in block state.\n";
					continue;
				}
				break;
			case 'z':
				if (m_player.m_state == 'A')
					m_player.m_state = 'B';
				else if (m_player.m_state == 'B')
					m_player.m_state = 'A';
				updateBoard();
				break;
			case 'c':
				std::cout << "Move skipped.\n";
				break;
			case 'e':
				done = true;
				break;
			case 'q':
				std::cout << "Player can be in either in A(attack) or in B(block) state. In A you can attack, but can't be damaged, in B vice versa.\n"
					<< "Each monster has unique base stats, and can move once in two turns and attack once in three.\n"
					<< "Once you are in their radius of aggression (6), they are going to try to approach and attack you.\n"
					<< "Radius of attack for everyone in 1";
				continue;
			default:
				std::cout << "Invalid input. Try again.\n";
				continue;
			}

			break;
		}


		bool allDead{ true };

		for (Monster& monster : m_monstersVector)
		{
			if (monster.m_dead == false)
			{
				allDead = false;

				int dist{ distance(monster, m_player) };

				if (dist == 1)
				{
					if (!(monster.m_attackCounter++ % monster.m_attackCD))
					{
						if (m_player.m_state == 'A')
						{
							monster >> m_player;
							std::cout << monster.getName() << " deals " << monster.m_damage << " damage." << '\n';
						}
						else { std::cout << monster.m_damage << " damage blocked.\n"; }
					}
				}
				else if (dist < monster.m_agressiveDistance && !(monster.m_moveCounter++ % monster.m_moveCD))
				{
					int yDiff{ static_cast<int>(m_player.m_pos[0]) - static_cast<int>(monster.m_pos[0]) };
					int xDiff{ static_cast<int>(m_player.m_pos[1]) - static_cast<int>(monster.m_pos[1]) };

					char yDir{};
					char xDir{};

					if (yDiff > 0) yDir = 's';
					else if (yDiff < 0) yDir = 'w';
					else yDir = '-';

					if (xDiff > 0) xDir = 'd';
					else if (xDiff < 0) xDir = 'a';
					else xDir = '-';

					std::array<char, 2> appVect{ yDir, xDir };

					if (xDir == '-')
					{
						if (!move(monster, yDir))
						{
							if (!move(monster, 'd'))
							{
								move(monster, 'a');
							}
						}
					}
					else if (yDir == '-')
					{
						if (!move(monster, xDir))
						{
							if (!move(monster, 's'))
							{
								move(monster, 'w');
							}
						}
					}
					else
					{
						char rolled{ appVect[Random::get<std::size_t>(0, 1)] };
						if (!move(monster, rolled))
						{
							if (rolled == 'w') rolled = 's';
							if (rolled == 's') rolled = 'w';
							if (rolled == 'a') rolled = 'd';
							if (rolled == 'd') rolled = 'a';
						}
					}
				}
			}
		}

		if (allDead)
		{
			render();
			std::cout << "\n\nAll enemies are dead.\n";
			done = true;
		}
		if (m_player.m_health < 0)
		{
			render();
			std::cout << "\n\nYou are dead.\n";
			done = true;
		}

	}
	std::cout << "Game over.\n";
}
