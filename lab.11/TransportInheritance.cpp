// TransportInheritance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для роботи з консоллю 

class Transport // Базовий клас "Транспорт"
{
protected:

    double speed; // Поле "Швидкість"
    double weight; // Поле "Вага"

public:

    Transport(double speed, double weight) : speed(speed), weight(weight) {} // Створення конструктора з параметрами

    virtual void printInfo() const // Віртуальний метод для виводу інформації про транспорт на екран
    { 
        std::cout << "Швидкість транспорту: " << speed << " км/год;\n";
        std::cout << "Вага транспорту: " << weight << " кг;" << std::endl;
    }

    virtual ~Transport() {} // Створення віртуального деструктора
};

class Car : public Transport // Похідний клас "Автомобіль"
{
private:

    int passengerCount; // Поле "Кількість пасажирів"

public:

    Car(double speed, double weight, int passengerCount) : Transport(speed, weight), passengerCount(passengerCount) {} // Створення конструктора з параметрами

    void printInfo() const override // Перевизначений метод для виводу інформації про автомобіль на екран
    {
        Transport::printInfo(); // Виклик методу з базового класу
        std::cout << "Кількість пасажирів: " << passengerCount << ";" << std::endl;
    }
};

class Truck : public Transport // Похідний клас "Вантажівка"
{
private:

    double loadCapacity; // Поле "Вантажопідйомність"

public:

    Truck(double speed, double weight, double loadCapacity) : Transport(speed, weight), loadCapacity(loadCapacity) {} // Створення конструктора з параметрами

    void printInfo() const override // Перевизначений метод для виводу інформації про вантажівку на екран
    {
        Transport::printInfo(); // Виклик методу з базового класу
        std::cout << "Вантажопідйомність: " << loadCapacity << " кг." << std::endl;
    }
};

int main() // Головна функція програми
{
    SetConsoleOutputCP(65001); // Встановлення кодування для коректного відображення українських символів у консолі

    Transport* trans[2]; // Оголошення масиву покажчиків

    std::cout << "=== ТРАНСПОРТ ===\n\n";
    // Створення об'єктів похідних класів і запис їх адрес у масив покажчиків
    trans[0] = new Car(150, 1800, 5);
    trans[1] = new Truck(130, 4500, 10000);

    for (int i = 0; i < 2; i++) // Демонстрація поліморфізму
    {
        trans[i]->printInfo();
        std::cout << "\n";
    }

    for (int i = 0; i < 2; i++) // Очищення пам'яті 
    {
        delete trans[i];
    }

    std::cout << "[УВАГА] - Пам'ять успішно очищено!\nЗавершення роботи програми..." << std::endl;

    return 0; // Завершення програми з кодом 0
}


