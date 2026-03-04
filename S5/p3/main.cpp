#include <iostream>
#include <cassert>
#include <string_view>

uint64_t calculatePower(int base, int power)
{
	assert(base >= 0 && power >= 0);
	if (power == 0) { return 1; }
	else { return base * calculatePower(base, power - 1); }
}

void handleInput(int& input, std::string_view name)
{
	while (true)
	{
		std::cout << "Enter " << name << ": ";
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

		if (input < 0)
		{
			std::cout << "Invalid input. Try again.\n";
			continue;
		}

		break;
	}
}

void powerFunction()
{
	while (true)
	{
		int base{};
		int power{};

		handleInput(base, "base");
		handleInput(power, "power");

		std::cout << base << " to the power of " << power << " is " << calculatePower(base, power) << '\n'
			      << "(if the value is too large it is going to be set to 0)\n";

		
		while (true)
		{
			char check{};
			std::cout << "Do you want to continue? (y/n): ";
			std::cin >> check;

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

			switch (check)
			{
			case 'y':
				break;
			case 'n':
				return;
			default:
				std::cout << "Invalid input. Try again.\n";
				continue;
			}

			break;
		}
	}
}

int main()
{
	powerFunction();

	return 0;
}
