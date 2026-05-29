// AnimalInheritance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для роботи з консоллю 
#include <string> // Підключення бібліотеки для роботи з рядками
#include <vector> // Підключення бібліотеки дя роботи з векторами

class Animal // Базовий клас "Тварина"
{
public:

    virtual void speak() const // Віртуальний метод для відображення звуку, що видає тварина
    {
        std::cout << "Тварина видає якісь звуки..." << std::endl;
    }

    virtual ~Animal() {} // Створення віртуального деструктора
};

class Cat : public Animal // Похідний клас "Кіт"
{
public:
    
    void speak() const override // Перевизначений метод для відображення звуку, що видає кіт
    {
        std::cout << "Кіт мурчить..." << std::endl;
    }
};

class Dog : public Animal // Похідний клас "Собака"
{
public:

    void speak() const override // Перевизначений метод для відображення звуку, що видає собака
    {
        std::cout << "Собака гавкає..." << std::endl;
    }
};

class Parrot : public Animal // Похідний клас "Папуга"
{
private:

    std::string sound; // Поле "Звук"

public:
    Parrot(std::string sound) : sound(sound) {} // Створення конструктора з параметрами

    void speak() const override // Перевизначений метод для відображення звуку, що може видавати папуга
    {
        std::cout << "Папуга вимовляє {" << sound << "}" << std::endl;
    }
};

int main() // Головна функція програми
{
    SetConsoleOutputCP(65001); // Встановлення кодування для коректного відображення українських символів у консолі

    std::vector<Animal*> animals; // Оголошення вектора покажчиків

    std::cout << "=== ЗООПАРК ТВАРИН ===\n\n";
    // Створення об'єктів похідних класів і запис їх адрес у вектор покажчиків
    animals.push_back(new Cat());
    animals.push_back(new Dog());
    animals.push_back(new Parrot("Бла-бла-бла..."));

    for (int i = 0; i < 3; i++) // Демонстрація поліморфізму
    {
        animals[i]->speak();
        std::cout << "\n";
    }

    for (int i = 0; i < animals.size(); i++) // Очищення пам'яті
    {
        delete animals[i];
    }

    std::cout << "[УВАГА] - Пам'ять успішно очищено!\nЗавершення роботи програми..." << std::endl;

    return 0; // Завершення програми з кодом 0
}


