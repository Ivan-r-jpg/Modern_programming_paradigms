// mini_calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення стандартної бібліотеки для вводу-виводу
#include <Windows.h> // Підключення бібліотеки для роботи з консоллю Windows
#include <limits> // Підключення бібліотеки для роботи для очищення потока вводу
#include <string> // Підключення бібліотеки для обробки вводу операції

int main() // Головна функція програми
{
	// Налаштування кодування консолі на Windows для відображення українських символів
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	// Оголошення змінних для зберігання результатів обчислень та введених чисел
	float sum = 0.0f;
	float prod = 1.0f;
	float diff = 0.0f;
	float part = 0.0f;
	float number1, number2;
	int choice;
	std::string operation;

	std::cout << "Введіть два дійсних числа:" << std::endl;
	while (true) // Цикл для введення першого числа з обробкою помилок
	{
		std::cout << "Число №1: ";
		std::cin >> number1;
		if (std::cin.fail()) // Якщо при введенні виникла помилка
		{
			std::cerr << "< Помилка при введені! >\n(Спробуйте ще раз...)\n";
			std::cin.clear(); // Очищення стану потока вводу
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), 
				'\n'); // Очищення потока вводу від залишкових символів
		}
		else
		{
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), 
				'\n'); // Очищення потока вводу від залишкових символів
			break;
		}
	}
	while (true) // Цикл для введення другого числа з обробкою помилок
	{
		std::cout << "Число №2: ";
		std::cin >> number2;
		if (std::cin.fail()) // Якщо при введенні виникла помилка
		{
			std::cerr << "< Помилка при введені! >\n(Спробуйте ще раз...)\n";
			std::cin.clear(); // Очищення стану потока вводу
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), 
				'\n'); // Очищення потока вводу від залишкових символів
		}
		else
		{
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), 
				'\n'); // Очищення потока вводу від залишкових символів
			break; // Вихід з циклу
		}
	}
	sum = number1 + number2; // Обчислення суми двох чисел
	prod = number1 * number2; // Обчислення добутку двох чисел
	std::cout << "Оберіть як саме будуть виконуватися дії "
		"віднімання та ділення (оберіть 1 або 2):" << std::endl;
	std::cout << "> 1 - Віднімання та ділення першого числа на друге" << std::endl;
	std::cout << "> 2 - Віднімання та ділення другого числа на перше" << std::endl;
	while (true) // Цикл для введення вибору операції з обробкою помилок
	{
		std::cout << "Ваш вибір: ";

		std::getline(std::cin, operation);
		// Спроба конвертувати введений рядок в ціле число 
		try
		{
			size_t pos;
			choice = stoi(operation, &pos);

			if (pos < operation.length()) // Якщо після конвертації залишилися інші символи
			{
				throw std::invalid_argument("< У записі числа наявні зайві символи! >");
			}

			if (choice != 1 && choice != 2) // Якщо введено інше число, то вибір некоректний
			{
				std::cerr << "< Введено неправильний вибір! >\n";
				continue; 
			}
			break; // Вихід з циклу
		}
		catch (const std::invalid_argument& e) // Обробка помилки
		{
			std::cerr << e.what() << "\n< Введіть ще раз коректне ціле число! >\n";
		}
	}
	std::cout << std::fixed;
	std::cout << std::endl << "\t\tРЕЗУЛЬТАТИ" << std::endl;

	std::cout << "Сума: " << sum << std::endl;
	std::cout << "Добуток: " << std::right << prod << std::endl;
	if (choice == 1) // Якщо вибір користувача - 1
	{
		diff = number1 - number2;

		std::cout << "Різниця: " << diff << std::endl;

		if (number2 != 0) // Перевірка на ділення на нуль 
		{
			part = number1 / number2; // Обчислення частки першого числа на друге

			std::cout << "Частка: " << part << std::endl;
		}
		else // Якщо друге число дорівнює нулю
		{
			std::cout << "Частка: Помилка (Ділення на нуль)" << std::endl;
		}
	}
	else if (choice == 2) // Якщо вибір користувача - 2
	{
		diff = number2 - number1; // Обчислення різниці другого числа на перше

		std::cout << "Різниця: " << diff << std::endl;
		if (number1 != 0) // Перевірка на ділення на нуль 
		{
			part = number2 / number1;

			std::cout << "Частка: " << part << std::endl;
		}
		else // Якщо перше число дорівнює нулю
		{
			std::cout << "Частка: Помилка (Ділення на нуль)" << std::endl;
		}
	}

	return 0; // Завершення програми з кодом 0
}
