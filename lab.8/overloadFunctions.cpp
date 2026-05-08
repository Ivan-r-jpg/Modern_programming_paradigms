// overloadFunctions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для налаштування кодування консолі
#include <cmath> // Підключення бібілотеки для використання математичних функцій

// Прототипи перевантажених функцій
int func(int a, float b);

int func(float a);

int func(double x, double y, double z);

int func(float a, int b);

int main()
{

    SetConsoleOutputCP(65001); // Встановлення кодування UTF-8

    int result; // Змінна, що зберігає результат функції

    result = func(5, 7);
    std::cout << "\nРезультат: " << result << std::endl;
    result = func(2, 1);
    std::cout << "\nРезультат: " << result << std::endl;
    result = func(7.85);
    std::cout << "\nРезультат: " << result << std::endl;
    result = func(2.12, 7.135, -9.3);
    std::cout << "\nРезультат: " << result << std::endl;

    return 0; // Завершення програми з кодом 0
}

// Визначення перевантажених функцій
int func(int a, float b)
{
    std::cout << "\n[УВАГА] - Викликається функція int func(int a, float b)" << std::endl;
    return a + b;
}

int func(float a)
{
    std::cout << "\n[УВАГА] - Викликається функція int func(float a)" << std::endl;
    a = static_cast<int>(round(a));
    return pow(a, 3);
}

int func(double x, double y, double z)
{
    std::cout << "\n[УВАГА] - Викликається функція int func(double x, double y, double z)" << std::endl;
    return static_cast<int>(round(sqrt((x * x) + (y * y) + (z * z))));
}

int func(float a, int b)
{
    std::cout << "\n[УВАГА] - Викликається функція int funс(float a, int b)" << std::endl;
    return static_cast<int>(round(a * b));
}

