#include "UserInteraction.h"

int inputInteger(const int& min, const int& max, const std::string& text) // Визначення функції для вводу цілого числа з перевіркою допустимого діапазону значень 
{
	std::string input;
	int value;
	size_t pos;

	while (true)
	{
		std::cout << text;
		std::getline(std::cin, input);
		try
		{
			value = std::stoi(input, &pos);
			if (pos < input.size())
			{
				throw std::invalid_argument("Невірний формат вводу! Введено зайві символи!");
			}
			if (value < min || value > max)
			{
				throw std::out_of_range("Значення повинно бути цілим числом між " + std::to_string(min) + " та " + std::to_string(max) + "!");
			}
			return value;
		}
		catch (const std::exception& e)
		{
			std::cerr << "\n[ПОМИЛКА ВВОДУ] - " << e.what() << "\n(Спробуйте ввести ще раз...)\n";
		}
	}
}

double inputDouble(const double& min, const double& max, const std::string& text) // Визначення функції для вводу числа з плаваючою точкою з перевіркою допустимого діапазону значень
{
	std::string input;
	double value;
	size_t pos;

	while (true)
	{
		std::cout << text;
		std::getline(std::cin, input);
		try
		{
			value = std::stod(input, &pos);
			if (pos < input.size())
			{
				throw std::invalid_argument("Невірний формат вводу! Введено зайві символи!");
			}
			if (value < min || value > max)
			{
				throw std::out_of_range("Значення повинно бути числом між " + std::to_string(min) + " та " + std::to_string(max) + "!");
			}
			return value;
		}
		catch (const std::exception& e)
		{
			std::cerr << "\n[ПОМИЛКА ВВОДУ] - " << e.what() << "\n(Спробуйте ввести ще раз...)\n";
		}
	}
}