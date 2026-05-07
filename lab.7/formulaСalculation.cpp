// formulaСalculation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "inputCheck.h" // Підключення заголовочного файлу, що потрібен для використання функцій валідації вводу
#include "calculationArguments.h" // Підключення заголовочного файлу, що потрібен для використання функцій, що приймають участь в обчисленні формули
#include <Windows.h> // Підключення бібліотеки для налаштування кодування
#include <iomanip> // Підключення бібліотеки для форматованого виведення

class Vector // Клас, що описує вектор значень
{
private:

    std::string arrName; // Поле "ім'я масиву"
    int arrSize; // Поле "розмір масиву"
    std::vector<double> arr; // Поле "масив"

public:

    Vector(std::string arrName, int arrSize) // Створення конструктора з параметрами
    {
        this->arrName = arrName;
        this->arrSize = arrSize;
    }

    const std::vector<double>& getArr() const // Метод, що дозволяє передати адресу вектора
    { 
        return arr; 
    }

    void initialization() // Метод, необхідний для ініціалізації масиву (вектора)
    {
        arr.reserve(arrSize); // Резерування пам'яті перед заповненням
        std::cout << "\n[УВАГА] - Введіть значення елементів масиву " << arrName << ":\n" << std::endl;
        for (int i = 0; i < arrSize; i++) // Цикл, що проходить по всім елементам вектора
        {
            std::cout << arrName << "[" << i << "]: ";
            arr.push_back(inputDouble(-1000000.0, 1000000.0)); // Додавання нового елемента в кінець вектора
        }
        std::cout << "\n[УВАГА] - Всі елементи масиву успішно введено!" << std::endl;
    }

    void output() // Метод, що виводить значення елементів масиву (вектора) на екран
    {
        std::cout << "\nМасив чисел " << arrName << ": [ ";
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
};

void finalCalculation(const std::vector<double>& arrZ, const std::vector<double>& arrB, double& result); // Прототип функції, що виконує розрахунки за формулою

int main() // Головна функція програми
{
    SetConsoleOutputCP(65001); // Налаштування кодування консолі UTF-8

    std::cout << "Введіть розмір масиву z: ";
    int n = inputInt(1, 100); // Введення кількості елементів масиву z
    Vector vecZ = Vector("z", n); // Ініціалізація об'єкта класу Vector
    vecZ.initialization(); // Заповнення вектора
    vecZ.output(); // Вивід вектора на екран

    std::cout << "\n\nВведіть розмір масиву beta: ";
    int m = inputInt(1, 100); // Введення кількості елементів масиву beta
    Vector vecB = Vector("beta", m); // Ініціалізація об'єкта класу Vector
    vecB.initialization(); // Заповнення вектора
    vecB.output(); // Вивід вектора на екран

    double result = 0;
    finalCalculation(vecZ.getArr(), vecB.getArr(), result); // Виклик функції, що обчислює значення за формулою

    std::cout << std::fixed << std::setprecision(3) << "\n\n[РЕЗУЛЬТАТ] - phi (округлено до 3-х знаків після коми) = " << result << std::endl;
    
    return 0; // Завершення програми з кодом 0
}

void finalCalculation(const std::vector<double>& arrZ, const std::vector<double>& arrB, double& result) // Визначення функції, що виконує розрахунки за формулою
{
    double numerator = calculationAD(arrZ, [](double x) {return std::exp(x); }) + calculationBE(arrZ, [](double x) {return std::cos(x); }) *
        std::cos(calculationAD(arrB, [](double x) {return std::sin(x); })) + sin(calculationC(arrZ)); // Обчислення чисельника
    double denominator = calculationAD(arrB, [](double x) {return std::sin(x); }) + calculationBE(arrB, [](double x) {return std::tan(x); }) +
        std::cos(calculationF(arrB)); // Обчислення знаменника
    if (denominator == 0.0) // Перевірка чи знаменник дорівнює 0
    {
        std::cerr << "\n[ПОМИЛКА] - Вираз у знаменнику дорівнює 0!\n";
        exit(1); // Вихід з програми
    }
    result = numerator / denominator; // Привласнення результату змінній result
}