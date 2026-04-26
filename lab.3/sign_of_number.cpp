// sign_of_number.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для роботи з консоллю
#include <string> // Підключення бібліотеки для роботи з рядками

int signOfNumber(int x) // Визначення функції, яка аналізує знак числа
{
    int result;

	if (x > 0) // Якщо число більше нуля, результат буде 1
    {
        result = 1;
    }
	else if (x < 0) // Якщо число менше нуля, результат буде -1
    {
        result = -1;
    }
	else // Якщо число дорівнює нулю, результат буде 0
    {
        result = 0;
	}
	return result; // Повернення результату функції
}

int main() // Головна функція програми
{
	SetConsoleOutputCP(65001); // Встановлення кодування UTF-8
	SetConsoleCP(65001); // Встановлення кодування UTF-8

	int number, result_func;
	bool error = false;
    std::string input;

    std::cout << "Введіть число: ";
	std::getline(std::cin, input);
    // Обробка вводу користувача
    try
    {
        size_t pos;
        try
        {
            number = stoi(input, &pos);
        }
        catch (const std::exception& e)
        {
            throw std::invalid_argument("Некоректний ввід!");
		}
		if (pos < input.length())
        {
            throw std::invalid_argument("Некоректний ввід!");
        }
    }
	catch (const std::invalid_argument& e) // Перехоплення виключення
    {
        std::cout << "\n[ПОМИЛКА] - " << e.what() << std::endl;
		error = true; // Встановлення прапорця помилки
    }
    
	if (!error) // Якщо помилки під час виконання не виникло
    {
        result_func = signOfNumber(number); // Виклик функції signOfNumber

		// Виведення результату на екран залежно від значення result_func
        if (result_func == 1)
        {
            std::cout << "\n[УВАГА] - Введено додатне число";
        }
        else if (result_func == -1)
        {
            std::cout << "\n[УВАГА] - Введено від'ємне число";
        }
        else
        {
            std::cout << "\n[УВАГА] - Введено нуль";
        }
    }

	return 0; // Завершення програми з кодом успіху
}
