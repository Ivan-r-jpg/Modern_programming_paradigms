// Merchandise.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для налаштування кодування консолі
#include <string> // Підключення бібліотеки для роботи з рядками

class Merchandise // Батьківський абстрактний клас "Товар"
{
protected:

    double price; // Поле "Ціна"
    std::string condition; // Поле "Стан товару"

public:

    virtual void showInfo() const = 0; // Чиста віртуальна функція для виведення інформації на екран

    virtual ~Merchandise() {} // Оголошення віртуального деструктора
};

class Toy : public Merchandise // Похідний клас "Іграшка"
{
private:

    int releaseYear; // Поле "Рік випуску"
    std::string toyType; // Поле "Тип іграшки"

public:

    Toy(double price, std::string condition, int releaseYear, std::string toyType) // Створення конструктора з параметрами
    {
        if (price > 0 && releaseYear > 0) // Перевірка чи внесено коректні дані
        {
            this->price = price;
            this->condition = condition;
            this->releaseYear = releaseYear;
            this->toyType = toyType;
        }
        else // У іншому випадку генерується виняток
        {
            throw std::logic_error("Не вдалося створити об'єкт типу 'Іграшка'!");
        }
    }

    void showInfo() const override // Перевизначення методу, що виводить інформацію про іграшку на екран
    {
        std::cout << "Товар 'Іграшка':\n\n";
        std::cout << "    Тип іграшки: " << toyType << ";\n";
        std::cout << "    Ціна іграшки: " << price << " грн;\n";
        std::cout << "    Рік випуску: " << releaseYear << " рік;\n";
        std::cout << "    Стан іграшки: " << condition << "." << std::endl;
    }
};

class Product : public Merchandise // Похідний клас "Продукт"
{
protected:

    std::string productName; // Поле "Назва продукту"

public:

    Product(double price, std::string condition, std::string productName) // Створення конструктора з параметрами
    {
        if (price > 0) // Перевірка чи внесено коректні дані
        {
            this->price = price;
            this->condition = condition;
            this->productName = productName;
        } 
        else // У іншому випадку генерується виняток
        {
            throw std::logic_error("Не вдалося створити об'єкт типу 'Продукт'!");
        }
    }

    void showInfo() const override // Перевизначення методу, що виводить інформацію про продукт на екран
    {
        std::cout << "Товар 'Продукт':\n\n";
        std::cout << "    Назва продукту: " << productName << ";\n";
        std::cout << "    Ціна продукту: " << price << " грн;\n";
        std::cout << "    Стан продукту: " << condition << "." << std::endl;
    }
};

class DairyProduct : public Product // Вкладений похідний клас "Молочний продукт"
{
private:

    double cost; // Поле "Собівартість"
    double fatContent; // Поле "Відсоток жирності"

public:

    DairyProduct(double price, std::string condition, std::string productName, double cost, double fatContent) // Створення конструктора з параметрами 
        : Product(price, condition, productName) // та списком ініціалізації
    {
        if (cost > 0 && cost <= price && fatContent > 0 && fatContent <= 100) // Перевірка чи внесено коректні дані
        {
            this->cost = cost;
            this->fatContent = fatContent;
        }
        else // У іншому випадку генерується виняток
        {
            throw std::logic_error("Не вдалося створити об'єкт типу 'Молочний продукт'!");
        }
    }

    void showInfo() const override // Перевизначення методу, що виводить інформацію про молочний продукт на екран
    {
        std::cout << "Товар 'Молочний продукт':\n\n";
        std::cout << "    Назва продукту: " << productName << ";\n";
        std::cout << "    Ціна продукту: " << price << " грн;\n";
        std::cout << "    Собівартість: " << cost << " грн;\n";
        std::cout << "    Відсоток жирності: " << fatContent << "%;\n";
        std::cout << "    Стан продукту: " << condition << "." << std::endl;
    }
};

int main() // Головна функція програми
{
    SetConsoleOutputCP(65001); // Налаштування кодування для коректного виводу українських символів

    Merchandise* merchandise[4] = { nullptr, nullptr, nullptr, nullptr }; // Створення масиву покажчиків

    // Спроба створити різні об'єкти
    try
    {
        merchandise[0] = new Toy(850, "Новий", 2024, "Конструктор");
        merchandise[1] = new Product(45, "Свіжий", "Хліб");
        merchandise[2] = new DairyProduct(62, "Свіжий", "Молоко", 40, 2.5);
        merchandise[3] = new DairyProduct(95, "Свіжий", "Сметана", 70, -15);
    }
    catch (const std::logic_error& e) // Перехоплення винятку
    {
        std::cerr << "\n[ПОМИЛКА] - " << e.what() << "\n\n";
        std::cout << "------------------------\n\n";
    }

    for (int i = 0; i < 4; i++) // Демонстрація поліморфізму
    { 
        if (merchandise[i] != nullptr) // Якщо об'єкт створено
        {
            merchandise[i]->showInfo();
            std::cout << "\n------------------------\n\n";
        }
    }

    for (int i = 0; i < 4; i++) // Очищення пам'яті
    {
        delete merchandise[i];
    }

    return 0; // Завершення програми з кодом 0
}