// Transport.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для налаштування кодування консолі
#include <string> // Підключення бібліотеки для роботи з рядками

class Transport // Батьківський абстрактний клас "Транспорт"
{
protected:
    
    std::string brand; // Поле "Марка"

    double profit; // Поле "Прибуток"
    double costs; // Поле "Витрати"

public:

    virtual double netProfit() = 0; // Чиста віртуальна функція для розрахунку чистого прибутку

    virtual void showInfo() // Віртуальний метод, що виводить загальну інформацію
    {
        std::cout << "Марка транспорту: " << brand << ";\n";
        std::cout << "Прибуток: " << profit << " грн;\n";
        std::cout << "Витрати: " << costs << " грн;" << std::endl;
    }

    virtual ~Transport() {}; // Оголошення віртуального деструктора
};

class PassengerCar : public Transport // Похідний клас "Пасажирський транспорт"
{
private:

    int passengerCount; // Поле "Кількість пасажирів"
    double ticketPrice; // Поле "Ціна квитка"

public:

    PassengerCar(std::string brand, double costs, int passangerCount, double ticketPrice) // Створення конструктора з параметрами
    {
        if (costs >= 0 && passangerCount >=0 && ticketPrice > 0) // Перевірка чи внесено коректні дані
        {
            this->costs = costs;
            this->passengerCount = passangerCount;
            this->ticketPrice = ticketPrice;
            this->brand = brand;
            this->costs = costs;
        }
        else // У іншому випадку генерується виняток
        {
            throw(std::logic_error(brand));
        }
    }

    double netProfit() override // Перевизначення методу для розрахунку чистого прибутку
    {
        profit = passengerCount * ticketPrice;
        return profit - costs;
    }

    void showInfo() override // Перевизначення методу, що виводить інформацію про пасажирський транспорт на екран
    {
        double profitNow = this->netProfit();
        Transport::showInfo();
        std::cout << "Кількість пасажирів: " << passengerCount << ";\n";
        std::cout << "Ціна одного місця: " << ticketPrice << " грн;\n";
        std::cout << "ЧИСТИЙ ПРИБУТОК: " << profitNow << " грн." << std::endl;
    }
};

class FreightTransport : public Transport // Похідний клас "Вантажний транспорт"
{
private:

    double productWeight; // Поле "Вага товару"
    double fuelConsumption; // Поле "Витрата пального"
    double transportationDistance; // Поле "Відстань перевезення"
    double pricePerKgKm; // Поле "Ціна за км"
    double fuelPrice; // Поле "Ціна палива"

public:

    FreightTransport(std::string brand, double productWeight, double fuelConsumption, double transportationDistance, double pricePerKgKm, double fuelPrice) // Створення конструктора з параметрами
    {
        if (productWeight >= 0 && fuelConsumption > 0 && transportationDistance > 0 && pricePerKgKm > 0 && fuelPrice > 0) // Перевірка чи внесено коректні дані
        {
            this->brand = brand;
            this->productWeight = productWeight;
            this->fuelConsumption = fuelConsumption;
            this->transportationDistance = transportationDistance;
            this->pricePerKgKm = pricePerKgKm;
            this->fuelPrice = fuelPrice;
        }
        else // У іншому випадку генерується виняток
        {  
            throw(std::logic_error(brand));
        }
    }

    double netProfit() override // Перевизначення методу для розрахунку чистого прибутку
    {
        profit = (productWeight / 1000) * transportationDistance * pricePerKgKm;
        costs = fuelConsumption * (transportationDistance / 100 * fuelPrice);
        return profit - costs;
    }

    void showInfo() override // Перевизначення методу, що виводить інформацію про вантажний транспорт на екран
    {
        double profitNow = this->netProfit();
        Transport::showInfo();
        std::cout << "Вага товару, що перевозиться: " << productWeight << " кг;\n";
        std::cout << "Кілометраж поїздки: " << transportationDistance << " км;\n";
        std::cout << "Ціна, що доплачується за 1 км поїздки: " << pricePerKgKm << " грн;\n";
        std::cout << "Ціна пального: " << fuelPrice << " грн;\n";
        std::cout << "Витрата палива на кожні 100 км: " << fuelConsumption << " л;\n";
        std::cout << "ЧИСТИЙ ПРИБУТОК: " << profitNow << " грн." << std::endl;
    }
};

int main() // Головна функція програми
{
    SetConsoleOutputCP(65001); // Налаштування кодування для коректного виводу українських символів

    Transport* trans[3] = { nullptr, nullptr, nullptr }; // Створення масиву покажчиків

    // Спроба створити різні об'єкти
    try
    {
        trans[0] = new PassengerCar("Mercedes-Benz Sprinter", 2000, 15, 2500);
        trans[1] = new FreightTransport("MAN TGX", 10200, 30, 500, 20, 90);
        trans[2] = new FreightTransport("Merc", -1200, -30, 500, 20, 90);
    }
    catch (const std::logic_error& e) // Перехоплення винятку
    {
        std::cerr << "\n[ПОМИЛКА] - Створити об'єкт '" << e.what() << "' з переданими параметрами неможливо!\n\n";
        std::cerr << "------------------------\n\n";
    }

    for (int i = 0; i < 3; i++) // Демонстрація поліморфізму
    {
        if (trans[i] != nullptr) // Якщо об'єкт створено
        {
            trans[i]->showInfo();
            std::cout << "\n------------------------\n\n";
        }
    }

    for (int i = 0; i < 3; i++) // Очищення пам'яті
    {
        delete trans[i];
    }

    return 0; // Завершення програми з кодом 0
}