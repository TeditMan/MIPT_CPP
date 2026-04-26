#include "Grid.h"
#include "Monster.h"
#include "Player.h"
#include "Random.h"

#include <vector>
#include <iostream>
#include <cstdlib>

Grid::Grid(Player& player, std::vector<Monster>& monsters)
{
    for (auto& row : m_grid)
    {
        for (auto& element : row)
        {
            element = '-';
        }
    }

    p_player = &player;
    
    for (Monster& monster : monsters)
    {
        vp_monsters.push_back(&monster);
    }
}

void Grid::update()
{
	auto [yP, xP] = p_player->getPos();
	m_grid[yP][xP] = p_player->getSymbol();

	for (const Monster* monster : vp_monsters)
	{
		auto [yM, xM] = monster->getPos();
		m_grid[yM][xM] = monster->getSymbol();
	}
}

bool Grid::enemyMove()
{
    bool allDead{ true };

    for (Monster* p_monster : vp_monsters)
    {
        if (p_monster->getSymbol() != 'X')
        {
            allDead = false;

            if (((*p_monster) | (*p_player)) == 1)
            {
                if (!(p_monster->m_attackCounter++ % p_monster->getAttackCD()))
                {
                    if (p_player->getSymbol() == 'A')
                    {
                        *p_monster >> *p_player;
                        std::cout << p_monster->getName() << " deals " << p_monster->getDamage() << " damage." << '\n';
                    }
                    else { std::cout << p_monster->getDamage() << " damage blocked.\n"; }
                }
            }
            else if ((*p_monster | *p_player) < p_monster->s_agressiveDistance && !(p_monster->m_moveCounter++ % p_monster->getMoveCD()))
            {
                int yDiff{ static_cast<int>(p_player->getPos()[0]) - static_cast<int>(p_monster->getPos()[0]) };
                int xDiff{ static_cast<int>(p_player->getPos()[1]) - static_cast<int>(p_monster->getPos()[1]) };

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
                    if (!move(*p_monster, yDir))
                    {
                        if (!move(*p_monster, 'd'))
                        {
                            move(*p_monster, 'a');
                        }
                    }
                }
                else if (yDir == '-')
                {
                    if (!move(*p_monster, xDir))
                    {
                        if (!move(*p_monster, 's'))
                        {
                            move(*p_monster, 'w');
                        }
                    }
                }
                else
                {
                    char rolled{ appVect[Random::get<std::size_t>(0, 1)] };
                    if (!move(*p_monster, rolled))
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

    return allDead;
}

bool Grid::playerMove()
{
	bool over{ false };

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
			if (!move(*p_player, input))
			{
				std::cout << "Can't move there. Try again.\n";
				continue;
			}

			break;
		case 'x':
			if (p_player->getSymbol() == 'A')
			{
				for (Monster* p_monster : vp_monsters)
				{
					if (p_monster->getSymbol() != 'X' && (*p_monster | *p_player) == 1)
					{
						*p_player >> *p_monster;
						std::cout << p_monster->getName() << " receives " << p_player->getDamage() << " damage.\n";
						if (p_monster->getHealth() <= 0)
						{
							std::cout << p_monster->getName() << " is eliminated.\n";
							p_monster->eliminate();
							update();
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
			p_player->changeState();
			update();
			break;
		case 'c':
			std::cout << "Move skipped.\n";
			break;
		case 'e':
			over = true;
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
	return over;
}


template <typename T>
bool Grid::move(T& unit, char direction)
{
	auto [y, x] = unit.getPos();

	switch (direction)
	{
	case 'w':
		if (y != 0)
		{
			if (m_grid[y - 1][x] == '-')
			{
				m_grid[y - 1][x] = unit.getSymbol();
				m_grid[y][x] = '-';
				unit.move1(direction);
				return true;
			}
		}
		break;
	case 'a':
		if (x != 0)
		{
			if (m_grid[y][x - 1] == '-')
			{
				m_grid[y][x - 1] = unit.getSymbol();
				m_grid[y][x] = '-';
				unit.move1(direction);
				return true;
			}
		}
		break;
	case 's':
		if (y != s_ySize - 1)
		{
			if (m_grid[y + 1][x] == '-')
			{
				m_grid[y + 1][x] = unit.getSymbol();
				m_grid[y][x] = '-';
				unit.move1(direction);
				return true;
			}
		}
		break;
	case 'd':
		if (x != s_xSize - 1)
		{
			if (m_grid[y][x + 1] == '-')
			{
				m_grid[y][x + 1] = unit.getSymbol();
				m_grid[y][x] = '-';
				unit.move1(direction);
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}

std::ostream& operator<<(std::ostream& out, const Grid& grid)
{
    for (auto& row : grid.m_grid)
    {
        for (auto& element : row)
        {
            out << element;
        }
        out << '\n';
    }
    return out;
}