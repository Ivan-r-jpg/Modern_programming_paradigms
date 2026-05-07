// calculatingArrayStatistics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для налаштування кодування консолі
#include <vector> // Підключення бібліотеки для використання векторів
#include <string> // Підключення бібліотеки для використання рядків
#include <cstdlib> // Використання бібліотеки для використання exit()

int inputInt(double min, double max); // Прототип функції для валідації користувацького вводу цілих чисел

double inputDouble(double min, double max); // Прототип функції для валідації користувацького вводу чисел з плавуючою крапкою

void initialization(std::vector<double>& arr, int arrSize); // Прототип функції, необхідної для ініціалізації масиву (вектора)

void output(const std::vector<double>& arr); // Прототип функції, що виводить значення елементів масиву (вектора) на екран

void calculateStatistics(const std::vector<double>& arr, int arraySize, double& sumNegative, double& sumPositive, int& zeroCount); // Прототип функції для обчислення статистики

void printResults(const double& sumNegative, const double& sumPositive, const int& zeroCount); // Прототип функції, необхідної для друкування результатів на екран

int main() // Головна функція програми
{
    
    SetConsoleOutputCP(65001); // Налаштування кодування консолі

    // Оголошення та ініціалізація змінних для збереження сум та кількості елементів
    double sumNeg = 0.0, sumPos = 0.0;
    int zeroCount = 0;

    std::cout << "Введіть кількість елементів масиву: ";
    int size = inputInt(1, 100);
    
    std::vector<double> array; // Оголошення вектора значень

    initialization(array, size); // Виклик функції ініціалізації вектора
    output(array); // Виклик функції для виводу значень вектора на екран
    calculateStatistics(array, size, sumNeg, sumPos, zeroCount); // Виклик функції, що рахує статистику
    std::cout << "\n";
    printResults(sumNeg, sumPos, zeroCount); // Виклик функції, що друкує результати на екран
    std::cout << "\n\n[УВАГА] - Завершення роботи програми..." << std::endl;

    return 0; // Завершення програми з кодом 0
}

void calculateStatistics(const std::vector<double>& arr, int arraySize, double& sumNegative, double& sumPositive, int& zeroCount) // Визначення функції, що необхідна для обчислення статистики
{
    for (int i = 0; i < arraySize; i++) // Цикл, що проходить по всім елементам вектора
    {
        if (arr[i] > 0) // Якщо елемент більше 0, то рахується сума додатніх значень
        {
            sumPositive += arr[i];
        }
        else if (arr[i] == 0) // Якщо елемент дорівнює 0, то рахується кілкьість нульових елементів
        {
            zeroCount++;
        }
        else // Інакше рахується кількість від'ємних елементів
        {
            sumNegative += arr[i];
        }
    }
}

void initialization(std::vector<double>& arr, int arrSize) // Визначення функції, необхідної для ініціалізації масиву (вектора)
{
    std::cout << "\nВведіть значення елементів масиву:\n" << std::endl;
    for (int i = 0; i < arrSize; i++) // Цикл, що проходить по всім елементам вектора
    {
        std::cout << "arr[" << i << "]: ";
        arr.push_back(inputDouble(-1000000.0, 1000000.0)); // Додавання нового елемента в кінець вектора
    }
    std::cout << "\n[УВАГА] - Всі елементи масиву успішно введено!" << std::endl;
}

void output(const std::vector<double>& arr) // Визначення функції, що виводить значення елементів масиву (вектора) на екран
{
    std::cout << "\nМасив чисел: [ ";
    for (int i = 0; i < arr.size(); i++) // Цикл, що проходить по всім елементам вектора
    {
        // Для гарного виводу елементів вектора
        if (i != arr.size() - 1)
        {
            std::cout << arr[i] << "; ";
        }
        else
        {
            std::cout << arr[i] << " ]";
        }
    }
}

void printResults(const double& sumNegative, const double& sumPositive, const int& zeroCount) // Визначення функції, необхідної для друкування результатів на екран
{
    std::cout << "\nРЕЗУЛЬТАТИ:\n\nСума додатніх елементів в масиві: " << sumPositive <<
        "\nСума від'ємних елементів в масиві: " << sumNegative <<
        "\nКількість нульових елементів: " << zeroCount;
}

int inputInt(double min, double max) // Визначення функції для валідації користувацького вводу цілих чисел
{
    if (min > max) // Логічна помилка, якщо мінімальне значення більше за максимальне
    {
        std::cerr << "\n[СИСТЕМНА ПОМИЛКА] - Аргументи діапазону задані неправильно!\n";
        exit(1); // Вихід з програми
    }
    std::string input;
    size_t pos;
    int number;
    while (true) // Цикл для повторного запиту вводу, поки користувач не введе коректне значення
    {
        std::getline(std::cin, input);
        try
        {
            try
            {
                number = std::stoi(input, &pos); // Спроба конвертувати рядок у ціле число
            }
            // Обробка можливих помилок конвертації
            catch (const std::invalid_argument& e)
            {
                throw std::invalid_argument("\n[ПОМИЛКА] - Введено некоректний запис!\nСпробуйте ввести ще раз: ");
            }
            catch (const std::out_of_range& e)
            {
                throw std::out_of_range("\n[ПОМИЛКА] - Введений числовий запис виходить за межі допустимого!\nСпробуйте ввести ще раз: ");
            }
            if (pos < input.length()) // Перевірка на наявність зайвих символів після числа
            {
                throw std::invalid_argument("\n[ПОМИЛКА] - У записі наявні зайві символи!\nСпробуйте ввести ще раз: ");
            }
            if (number <= max && number >= min) // Перевірка, чи знаходиться число в межах допустимого діапазону
            {
                return number; // Повернення int значення
            }
            else
            {
                std::cout << "\n[ПОМИЛКА] - Введений числовий запис виходить за межі допустимого!\nСпробуйте ввести ще раз: ";
                continue; // Якщо число не в межах, повторити запит вводу
            }
        }
        catch (const std::invalid_argument& e) // Перехоплення помилки некоректного запису
        {
            std::cerr << e.what();
            continue;
        }
        catch (const std::out_of_range& e) // Перехоплення помилки виходу за межі допустимого діапазону
        {
            std::cerr << e.what();
            continue;
        }
    }
}

double inputDouble(double min, double max) // Визначення функції для валідації користувацького вводу чисел з плавуючою крапкою
{
    if (min > max) // Логічна помилка, якщо мінімальне значення більше за максимальне
    {
        std::cerr << "\n[СИСТЕМНА ПОМИЛКА] - Аргументи діапазону задані неправильно!\n";
        exit(1); // Вихід з програми
    }
    std::string input;
    size_t pos;
    double number;

    while (true)
    {
        std::getline(std::cin, input);
        try
        {
            number = std::stod(input, &pos); // Спроба конвертувати рядок у double

            if (pos < input.length()) // Перевірка на наявність зайвих символів після числа
            {
                throw std::invalid_argument("\n[ПОМИЛКА] - У записі наявні зайві символи!\nСпробуйте ввести ще раз: ");
            }
            if (number < min || number > max) // Перевірка, чи знаходиться число в межах допустимого діапазону
            {
                std::cerr << "\n[ПОМИЛКА] - Введений числовий запис виходить за межі допустимого!\nСпробуйте ввести ще раз: ";
                continue;
            }

            return number; // Повернення double значення
        }
        catch (const std::invalid_argument& e) // Перехоплення помилки некоректного запису
        {
            std::cerr << e.what();
            continue;
        }
        catch (const std::out_of_range& e) // Перехоплення помилки виходу за межі діапазону
        {
            std::cerr << "\n[ПОМИЛКА] - Число занадто велике для обробки!\nСпробуйте ввести ще раз: ";
            continue;
        }
    }
}