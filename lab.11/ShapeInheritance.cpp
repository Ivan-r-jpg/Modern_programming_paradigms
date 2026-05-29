// ShapeInheritance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для роботи з консоллю 
#include <string> // Підключення бібліотеки для роботи з рядками
#include <numbers> // Підключення бібліотеки для використання точного числового значення числа пі

class Shape // Базовий клас "Фігура"
{
protected:

    std::string name; // Поле "Назва"

public:

    Shape(std::string name) : name(name) {} // Створення конструктора з параметрами

    virtual double getArea() const = 0; // Віртуальний метод для знаходження площі фігури

    virtual void printInfo() const // Віртуальний метод для виведення інформації про фігуру
    {
        std::cout << "Фігура: " << name << std::endl;
    }

    virtual ~Shape() {}; // Створення віртуального деструктора
};

class RectangleShape : public Shape // Похідний клас "Прямокутник"
{
private:

    double width; // Поле "Довжина"
    double height; // Поле "Висота"

public:

    RectangleShape(std::string name, double width, double height) : Shape(name), width(width), height(height) {} // Створення конструктора з параметрами

    double getArea() const override // Перевизначений метод для знаходження площі прямокутника
    {
        return width * height;
    }

    void printInfo() const override // Перевизначений метод для виведення інформації про прямокутник
    {
        Shape::printInfo(); // Виклик методу з базового класу
        std::cout << "Довжина: " << width << " од.;\n";
        std::cout << "Висота: " << height << " од.;\n";
        std::cout << "Площа фігури: " << this->getArea() << " од^2." << std::endl;
    }
};

class Circle : public Shape // Похідний клас "Круг"
{
private:

    double radius; // Поле "Радіус"

public:

    Circle(std::string name, double radius) : Shape(name), radius(radius) {} // Створення конструктора з параметрами

    double getArea() const override // Перевизначений метод для знаходження площі круга
    {
        return std::numbers::pi * radius * radius;
    }

    void printInfo() const override // Перевизначений метод для виведення інформації про круг
    {
        Shape::printInfo(); // Виклик методу з базового класу
        std::cout << "Радіус: " << radius << " од.;\n";
        std::cout << "Площа фігури: " << this->getArea() << " од^2." << std::endl;
    }
};

class Triangle : public Shape // Похідний клас "Трикутник"
{
private:

    double base; // Поле "Основа"
    double height; // Поле "Висота"

public:

    Triangle(std::string name, double base, double height) : Shape(name), base(base), height(height) {} // Створення конструктора з параметрами

    double getArea() const override // Перевизначений метод для знаходження площі трикутника
    {
        return 0.5 * base * height;
    }

    void printInfo() const override // Перевизначений метод для виведення інформації про трикутник
    {
        Shape::printInfo(); // Виклик методу з базового класу
        std::cout << "Довжина основи: " << base << " од.;\n";
        std::cout << "Висота: " << height << " од.;\n";
        std::cout << "Площа фігури: " << this->getArea() << " од^2." << std::endl;
    }
};

int main() // Головна функція програми
{
    SetConsoleOutputCP(65001); // Встановлення кодування для коректного відображення українських символів у консолі

    Shape* shape[3]; // Оголошення масиву покажчиків

    std::cout << "=== ФІГУРИ ===\n\n";
    // Створення об'єктів похідних класів і запис їх адрес у масив покажчиків
    shape[0] = new RectangleShape("Прямокутник", 20, 40);
    shape[1] = new Circle("Круг", 10);
    shape[2] = new Triangle("Трикутник", 20, 150);

    for (int i = 0; i < 3; i++) // Демонстрація поліморфізму
    {
        shape[i]->printInfo();
        std::cout << "\n";
    }

    for (int i = 0; i < 3; i++) // Очищення пам'яті 
    {
        delete shape[i];
    }

    std::cout << "[УВАГА] - Пам'ять успішно очищено!\nЗавершення роботи програми..." << std::endl;

    return 0; // Завершення програми з кодом 0
}

