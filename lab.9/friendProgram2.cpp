// friendProgram2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для підключення кодування
#include <string> // Підключення бібліотеки для використання рядків
#include <vector> // Підключення бібліотеки для використання векторів
#include <climits> // Підключення бібліотеки для cin.ignore()
#include <random> // Підключення бібліотеки для генерування випадкових значень
#include <conio.h> // Підключення бібліотеки для _getch()
  
class Wallet // Клас, що описує гаманець
{
private:

    double balance; // Поле "баланс"
    std::string walletID; // Поле "ID гаманця"
    std::string currency; // Поле "валюта"
    std::string password; // Поле "пароль"
    double savings; // Поле "заощадження"

    friend class Bank; // Клас Bank є дружнім до класу Wallet

public:

    Wallet() {} // Створення порожнього конструктора

    // Створення конструктора з параметрами
    Wallet(double balance, std::string walletID, std::string currency, std::string password, double savings)
        : balance(balance), walletID(walletID), currency(currency), password(password), savings(savings) {}

    void viewWalletInfo() const // Метод для перегляду інформації про гаманець
    {
        std::cout << "Гаманець '" << walletID << "':\nБаланс на рахунку: " 
            << balance << "\nЗаощадження: " << savings << "\nЗберігається у валюті: "
            << currency << std::endl;
    }

    bool accessСheck(const std::string& identification) const // Метод для перевірки доступу до гаманця
    {
        if (identification == password) // Якщо введений пароль співпадає
        {
            return true; // Повернення true
        }
        return false; // Повернення false
    }

    double getBalance() // Метод для отримання значення балансу
    {
        return balance;
    }

    double getSavings() // Метод для отримання значення заощаджень
    {
        return savings;
    }
};

class Bank // Клас, що описує банк
{
private:

    std::string bankName; // Поле "назва банку"
    std::vector<double> exchangeRate; // Поле "курс валют"

public:

    Bank() {} // Створення порожнього конструктора

    // Створення конструктора з параметрами
    Bank(std::string bankName, std::vector<double> exchangeRate)
        : bankName(bankName), exchangeRate(exchangeRate) {}

    void checkExchangeRate(Wallet& wal) // Метод, що виводить на екран список курсу валют по відношенню до валюти гаманця
    {
        for (int i = 0; i < exchangeRate.size(); i++)
        {
            std::cout << "Валюта [" << i + 1 << "] = " << exchangeRate[i] << " " << wal.currency << "\n";
        }
    }

    void conversionDemonstration(Wallet& wal, int currencyIndex) // Метод, що демонструє конвертування грошей на гаманці в обрану валюту
    {
        std::cout << "Конвертація валюти у Вашому гаманці за допомогою сервісу " << bankName << ": " << std::endl;
        std::cout << "- Баланс: " << wal.balance << " " << wal.currency << 
            " -> " << wal.balance / exchangeRate[currencyIndex - 1] << " Валюта " << currencyIndex << std::endl;
        std::cout << "- Заощадження: " << wal.savings << " " << wal.currency <<  
            " -> " << wal.savings / exchangeRate[currencyIndex - 1] << " Валюта " << currencyIndex << std::endl;
    }

    void addToBalance(Wallet& wal, double money) // Метод, що додає гроші до гаманця
    {
        wal.balance += money;
    }

    void withdrawFromBalance(Wallet& wal, double money) // Метод, що знімає гроші з гаманця
    {
        wal.balance -= money;
    }

    void addToSavings(Wallet& wal, double money) // Метод, що додає гроші до заощаджень
    {
        wal.savings += money;
    }

    void withdrawFromSavings(Wallet& wal, double money) // Метод, що знімає гроші зі заощаджень
    {
        wal.savings -= money;
    }


};

int inputInt(double min, double max) // Функція для валідації вводу користувача
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

double inputDouble(double min, double max)
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

int main() // Головна функція програми
{
    SetConsoleOutputCP(65001); // Налаштування кодування консолі для коректного відображення українських символів
    SetConsoleCP(65001); // Налаштування кодування консолі для коректного вводу українських символів

    int attempts = 0; // Лічильник спроб

    std::cout << "Введіть назву банка, що надає послуги: ";
    std::string bankName;
    std::getline(std::cin, bankName);

    Wallet wal = Wallet(50000, "IP-32", "UAH", "2325GH21", 35000); // Ініціалізація об'єкта класу Wallet

    std::cout << "\n[УВАГА] - Введіть пароль, щоб отримати доступ до гаманця: ";
    std::string enteredPassword;

    std::getline(std::cin, enteredPassword);

    while (attempts < 2 && !wal.accessСheck(enteredPassword)) // Цикл повторюється поки користувач не введе правильний пароль або поки не закінчиться кількість спроб
    {
        attempts++;
        std::cout << "\n[ПОМИКА] - Введено неправильний пароль!\nСпробуйте ввести ще раз (Кількість спроб, що лишилася: " << 3 - attempts << "): ";
        std::getline(std::cin, enteredPassword);
    }
    if (attempts == 2) // Якщо використано три спроби
    {
        std::cout << "\n[УВАГА] - Ви не пройшли авторизацію!\n[Доступ заблоковано]" << std::endl;
        return 1; // Завершення програми з кодом 1
    }

    std::cout << "\n[УВАГА] - Доступ до гаманця дозволено!" << std::endl;

    int currencyIndex;
    double money;
    bool endOfProgram = false;

    // Генерування випадковостей
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> rateDist(0.1, 100.0); // Для курсу валют
    std::uniform_int_distribution<> countDist(5, 20); // Для розміру вектора курсу валют

    std::vector<double> currenciesArray; // Оголошення вектора курсу валют

    for (int i = 0; i < countDist(gen); i++) // Заповнення вектора курсу валют
    {
        currenciesArray.push_back(rateDist(gen));
    }

    Bank bk = Bank(bankName, currenciesArray); // Ініціалізація об'єкта класу Bank

    while (!endOfProgram) // Цикл триває поки користувач не захоче вийти з програми
    {
        std::cout << "\nМЕНЮ керування гаманцем:\n" <<
            "\n1 - Переглянути інформацію про гаманець;" <<
            "\n2 - Покласти гроші;" <<
            "\n3 - Зняти гроші;" <<
            "\n4 - Переглянути курс валют;" <<
            "\n5 - Показати рахунок в іншій валюті;" <<
            "\n6 - Вихід з гаманця." << std::endl;
        std::cout << "\nВведіть Ваш вибір: ";
        int userChoice = inputInt(1, 6);

        switch (userChoice) 
        {
        case 1:
            std::cout << "\n";
            wal.viewWalletInfo();
            std::cout << "\nНатисніть будь-яку клавішу для продовження..." << std::endl;
            _getch();
            break;

        case 2:
            std::cout << "\nВведіть суму, яку бажаєте покласти на рахунок: ";
            money = inputDouble(0, 100000);
            std::cout << "\nОберіть куди покласти гроші:\n\n1 - До основного балансу;\n2 - До заощаджень.\n\nВведіть Ваш вибір: ";
          
            userChoice = inputInt(1, 2);
            switch (userChoice)
            {
            case 1:
                bk.addToBalance(wal, money);
                std::cout << "\n[УВАГА] - Суму " << money << " успішно додано до Вашого балансу!" << std::endl;
                break;
            case 2:
                bk.addToSavings(wal, money);
                std::cout << "\n[УВАГА] - Суму " << money << " успішно додано до Ваших збережень!" << std::endl;
                break;
            }
            std::cout << "\nНатисніть будь-яку клавішу для продовження..." << std::endl;
            _getch();
            break;

        case 3:
            std::cout << "\nОберіть звідки зняти гроші:\n\n1 - З основного балансу;\n2 - Зі заощаджень.\n\nВведіть Ваш вибір: ";
            userChoice = inputInt(1, 2);
            switch (userChoice)
            {
            case 1:
                std::cout << "\nВведіть суму, яку бажаєте зняти з основного балансу: ";
                money = inputDouble(0, wal.getBalance());
                bk.withdrawFromBalance(wal, money);
                std::cout << "\n[УВАГА] - Суму " << money << " успішно знято з Вашого балансу!" << std::endl;
                break;
            case 2:
                std::cout << "\nВведіть суму, яку бажаєте зняти зі збережень: ";
                money = inputDouble(0, wal.getSavings());
                bk.withdrawFromSavings(wal, money);
                std::cout << "\n[УВАГА] - Суму " << money << " успішно знято з Ваших збережень!" << std::endl;
                break;     
            }
            std::cout << "\nНатисніть будь-яку клавішу для продовження..." << std::endl;
            _getch();
            break;

        case 4:
            std::cout << "\nСтан курсу валют на сьогодні:\n\n";
            bk.checkExchangeRate(wal);
            std::cout << "\nНатисніть будь-яку клавішу для продовження..." << std::endl;
            _getch();
            break;

        case 5:
            std::cout << "\nВведіть, до якого з курсу валют ви хочете конвертувати: ";
            currencyIndex = inputInt(1, currenciesArray.size());
            std::cout << "\n";
            bk.conversionDemonstration(wal, currencyIndex);
            std::cout << "\nНатисніть будь-яку клавішу для продовження..." << std::endl;
            _getch();
            break;

        case 6:
            std::cout << "\n[УВАГА] - Вихід з системи надання послуг..." << std::endl;
            endOfProgram = true;
            break;
        }
    }

    return 0; // Завершення програми з кодом 0
}


