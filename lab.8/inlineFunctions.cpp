// inlineFunctions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для налаштування кодування
#include <chrono> // Підключення бібліотеки для замірів часу
#include <vector> // Підключення бібліотеки для роботи з векторами
#include <random> // Підключення бібліотеки для використання рандомних значень

inline double sumOfSquaresInline(const std::vector<double>& arr) // Визначення inline-функції, що проводить прості математичні операції над масивом
{
    double sum = 0.0; // Оголошення суми

    for (int i = 0; i < arr.size(); i++) // Цикл, що проходиться по кожному елементу масиву
    {
        sum += arr[i] * arr[i]; // Розрахунок суми
    }

    return sum; // Повернення результату
}

__declspec(noinline) double sumOfSquares(const std::vector<double>& arr) // Визначення звичайної функції, з установленою вказівкою не робити дану функцію вбудованою 
{
    double sum = 0.0; // Оголошення суми

    for (int i = 0; i < arr.size(); i++) // Цикл, що проходиться по кожному елементу масиву
    {
        sum += arr[i] * arr[i]; // Розрахунок суми
    }

    return sum; // Повернення результату
}

int main() // Головна функція програми
{
    SetConsoleOutputCP(65001); // Встановлення кодування консолі UTF-8

    // Встановлення volatile, щоб кожен раз перезаписувати змінні dummy в циклі
    volatile double dummy1 = 0.0; 
    volatile double dummy2 = 0.0;

    int iterations = 10; // Кількість ітерацій для тесту

    // Налаштування випадкової генерації
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> elements(-1000.0, 1000.0);

    std::vector<double> arr; // Оголошення вектора
    arr.reserve(10000000); // Резервування місця

    for (int i = 0; i < 10000000; i++) // Цикл, що заповнює вектор випадковими значеннями
    {
        arr.push_back(elements(gen));
    }
    for (int i = 0; i < 10; i++) // Цикл, що проганяє функції (потрібно для чесності в тесті)
    {
        dummy1 += sumOfSquaresInline(arr);
        dummy2 += sumOfSquares(arr);
    }

    auto start1 = std::chrono::high_resolution_clock::now(); // Запуск таймера для вбудованої функції
    
    for (int i = 0; i < iterations; i++)  // Основний тестовий цикл
    {
        dummy1 += sumOfSquaresInline(arr);
    }

    auto end1 = std::chrono::high_resolution_clock::now(); // Кінець таймера для вбудованої функції
    
    std::chrono::duration<double, std::micro> timeSpent1 = end1 - start1; // Розрахунок загального часу

    auto start2 = std::chrono::high_resolution_clock::now(); // Запуск таймера для звичайної функції
    
    for (int i = 0; i < iterations; i++)
    {
        dummy2 += sumOfSquares(arr);
    }

    auto end2 = std::chrono::high_resolution_clock::now(); // Кінець таймера для звичайної функції

    std::chrono::duration<double, std::micro> timeSpent2 = end2 - start2; // Розрахунок загального часу

    // Вивід результатів на екран
    std::cout << "Час виконання inline функції:   "
        << timeSpent1.count() << " мікросекунд" << std::endl;

    std::cout << "Час виконання звичайної функції: "
        << timeSpent2.count() << " мікросекунд" << std::endl;

    return 0; // Завершення програми з кодом 0
}


