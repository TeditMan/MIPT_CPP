#include <iostream>
#include "Random.h"
#include <limits>
#include <cassert>

int calculateSum(int* array, std::size_t size)
{
	assert(size > 0 && "function does not support arrays of size 0");
	if (size == 1) { return *array; }
	else { return calculateSum(array, size - 1) + array[size - 1]; }
}

void arraySumFunction()
{
	while (true)
	{
		int input{};

		while (true)
		{
			std::cout << "Enter a size of an array, elements of which will then be randomly generated: ";
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

			if (input <= 0)
			{
				std::cout << "Invalid input. Try again.\n";
				continue;
			}

			break;
		}

		std::size_t size{ static_cast<std::size_t>(input) };

		int* array{ new int[size] {} };
		for (std::size_t i{}; i < size; ++i)
		{
			array[i] = Random::get(0, 1000);
		}

		std::cout << "Array: [";
		for (std::size_t i{}; i < size; ++i)
		{
			std::cout << array[i] << (i == size - 1 ? "]\n" : ", ");
		}

		std::cout << "The sum of all elements is: " << calculateSum(array, size) << '\n';

		delete[] array;
		array = nullptr;

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
	arraySumFunction();

	return 0;
}
