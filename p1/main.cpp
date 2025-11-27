#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>


void addStringToString(std::string& base, const std::string& num)
{
	std::string result;
	std::size_t i{ base.size() };
	std::size_t j{ num.size() };
	int carry{};

	while (i > 0 || j > 0 || carry > 0)
	{
		int digit1{ (i > 0) ? static_cast<int>(base[--i] - '0') : 0 };
		int digit2{ (j > 0) ? static_cast<int>(num[--j] - '0') : 0 };
		int sum{ digit1 + digit2 + carry };
		carry = sum / 10;
		result.push_back(static_cast<char>(sum % 10 + '0'));
	}

	std::reverse(result.begin(), result.end());
	base = result;
}

void multiplyString(std::string& base, int number)
{
	std::string result{};
	while (number-- > 0)
	{
		addStringToString(result, base);
	}
	base = result;
}

std::string calculateFactorial(int number)
{
	std::string result{ "1" };

	while (number > 0)
	{
		multiplyString(result, number--);
	}

	return result;
}

void factorialFunction()
{
	while (true)
	{
		int number{};

		while (true)
		{
			std::cout << "Enter a non-negative integer: ";
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

			if (number < 0)
			{
				std::cout << "Invalid input. Try again.\n";
				continue;
			}

			break;
		}

		std::cout << "The factorial of this number is: " << calculateFactorial(number) << '\n';

		char check{};
		bool condition{true};
		while (condition)
		{
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
				condition = false;
				break;
			case 'n':
				std::exit(0);
			default:
				std::cout << "Invalid input. Try again.\n";
			}
		}
	}
}

int main()
{
	factorialFunction();

    return 0;
}





