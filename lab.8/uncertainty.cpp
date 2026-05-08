// uncertainty.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для налаштування кодування

// Прототипи перевантажених функцій, що мають викликати неоднозначність
double function(double a, int b);

double function(int a, double b);

int main()
{
    SetConsoleOutputCP(65001); // Вставнолення кодування консолі UTF-8

    double result = function(5, 10); // Виклик функції з парметрами 5 та 10 (Компілятор видає помилку на цьому етапі)
    std::cout << "\nРезультат: " << result << std::endl;

    return 0; // Завершення програми з кодом 0
}

// Визначення функцій, що мають викликати неоднозначність 
double function(double a, int b)
{
    std::cout << "[УВАГА] - Працює функція function(double a, int b)!" << std::endl;
    return a + b; // Обчислює суму аргументів
}

double function(int a, double b)
{
    std::cout << "[УВАГА] - Працює функція function(int a, double b)!" << std::endl;
    return (a + b) / 2; // Обчислює середнє арифметичне значення аргументів
}

