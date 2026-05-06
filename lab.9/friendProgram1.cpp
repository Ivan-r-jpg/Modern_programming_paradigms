// friendProgram1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключенння бібліотеки для налаштування консолі
#include <string> // Підключення бібліотеки для використання рядків

class User; // Передчасне оголошення класу User, вказівка компілятору, що далі цей клас буде визначено

class Library // Клас Library, що описує бібліотеку
{
    // Приватні поля доступу
private: 
    std::string locationAddress; // Поле "адреса знаходження"
    unsigned int libraryNumber; // Поле "номер бібліотеки"
    unsigned int booksCount; // Поле "кількість книг"

    // Публічні поля доступу
public:
    Library(std::string locationAddress, unsigned int libraryNumber, unsigned int booksCount) // Створення конструктора з параметрами
    {
        this->locationAddress = locationAddress;
        this->libraryNumber = libraryNumber;
        this->booksCount = booksCount;
    }

    friend bool checkAvailability(const Library& lib, User& usr); // Оголошення дружньої функції до класу Library
};

class User // Клас User, що описує користувача бібліотеки
{
    // Приватні поля доступу
private: 
    std::string userName; // Поле "ім'я користувача"
    std::string userID; // Поле "порядковий номер користувача, за яким він числиться"
    unsigned int requestedBooks; // Поле "кількість зарезервованих книг"

    // Публічні поля доступу
public:
    User(std::string userName, std::string userID, unsigned int requestedBooks) // Створення конструктора з параметрами
    {
        this->userName = userName;
        this->userID = userID;
        this->requestedBooks = requestedBooks;
    }

    friend bool checkAvailability(const Library& lib, User& usr); // Оголошення дружньої функції до класу User
};

bool checkAvailability(const Library& lib, User& usr); // Прототип дружньої функції для класів Library та User, що перевіряє кількість доступних книг

int main() // Головна функція програми
{
    SetConsoleOutputCP(65001); // Налаштування кодування консолі для коректного виведення українських символів на екран

    Library lib = Library("вул. Охтирська 7", 2, 11); // Створення та ініціалізація об'єкту класу Library
    User usr = User("Орехов Іван Васильович", "IП-21", 15); // Створення та ініціалізація об'єкту класу User
   
    if (checkAvailability(lib, usr)) // Якщо функція повертає true
    {
        std::cout << "\n[УВАГА] - Статус: Дозволено!\n[Деталі: Книг достатньо!]" << std::endl;
    }
    else // Інакше
    {
        std::cout << "\n[УВАГА] - Статус: Відмовлено!\n[Деталі: Недостатньо книг у бібліотеці!]" << std::endl;
    }

    std::cout << "\n[УВАГА] - Завершення програми..." << std::endl;

    return 0; // Повернення нуль як результату правильного відпрацювання програми
}

bool checkAvailability(const Library& lib, User& usr) // Визначення дружньої функції для класів Library та User, що перевіряє кількість доступних книг
{
    std::cout << "\t\t\t\t\t--- Перевірка доступу ---" << std::endl;
    std::cout << "\n\t-> Бібліотека: " << lib.libraryNumber << ", що знаходиться за адресою: "<< lib.locationAddress << " - має в наявності " << lib.booksCount << " книг!" << std::endl;
    std::cout << "\t<- Користувач " << usr.userName << " (ID: " << usr.userID << ") хоче взяти " << usr.requestedBooks << " книг!" << std::endl;
    
    if (lib.booksCount < usr.requestedBooks) // Якщо кількість книг в бібліотеці менша за ті книги, що хоче взяти користувач
    {
        return false; // Повернення ознаки відмови
    }
    return true; // У інакшому випадку буде повернено true
}
