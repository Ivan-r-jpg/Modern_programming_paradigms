// palindrome_check.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Для вводу/виводу
#include <Windows.h> // Для коректного відображення символів у консолі

int main() // Головна функція програми
{
    SetConsoleOutputCP(65001); // Налаштування кодування UTF-8
    SetConsoleCP(65001); // Налаштування кодування UTF-8

    int number, digit;
    int reversed = 0; // Оголошення змінних типу int

    std::cout << "Введіть число: ";

    std::cin >> number; // Введення числа з клавіатури

    int original = number; // Присвоєння змінній original значення number

    while (number != 0) // Цикл триває, поки не скінчиться число
    {
        digit = number % 10; // Береться остання цифра
        reversed = reversed * 10 + digit; // Додається в перевернуте число
        number /= 10; // З числа прибирається остання цифра
    }

    if (original == reversed) // Якщо числа співпадають
    {
        std::cout << "[УВАГА] - Число " << original << " є палiндромом!";
    }
    else
    {
        std::cout << "[УВАГА] - Число " << original << " не є палiндромом!";
    }

    return 0; // Завершення програми з кодом 0
}

