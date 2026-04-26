// oop_book-reader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Для вводу/виводу
#include <string> // Для роботи з рядками
#include <Windows.h> // Для встановлення кодування консолі
#include <vector> // Для використання вектора
#include <cstdlib> // Для використання exit()

int input(int min, int max) // Функція для валідації вводу користувача
{
	if (min > max)
	{
		std::cerr << "\n[СИСТЕМНА ПОМИЛКА] - Аргументи діапазону задані неправильно!\n";
		exit(1);
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
				return number; // Повернення числа
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

void displayMenu() // Функція для відображення меню користувача
{
	std::cout << "[МЕНЮ]:\n\n";
	std::cout << "1. Додати книги до бібліотеки;\n";
	std::cout << "2. Вивести інформацію про книги;\n";
	std::cout << "3. Змінити рік видання книги;\n";
	std::cout << "4. Видалити книгу з бібліотеки;\n";
	std::cout << "5. Вихід.\n\n";
}

class Book // Клас для представлення книги
{
	// Приватні поля класу для зберігання інформації про книгу
private: 

	std::string title; 
	std::string author;
	int publicationYear;

	// Публічні методи класу для взаємодії з полями
public:

	Book(std::string tit, std::string aut, int yr) 
		: title(tit), author(aut), publicationYear(yr) {} // Конструктор класу з параметрами
	void printInfo() const // Метод класу, що дозволяє переглянути інформацію про книгу
	{
		std::cout << "Назва: " << title << "\n";
		std::cout << "Автор: " << author << "\n";
		std::cout << "Рік видання: " << publicationYear;
	}
	void setYear(int year) // Метод класу, що дозволяє змінити рік видання
	{
		publicationYear = year;
	}
};

class Library // Клас для представлення бібліотеки
{
	// Приватні поля класу для зберігання інформації про книги
private: 

	std::vector<Book> books;

	// Публічні методи класу для взаємодії з книгами
public:

	Library() {}; // Створення порожнього конструктора
	void addBook(const Book& newBook) // Метод класу, що використовується для додавання нової книги
	{
		books.push_back(newBook);
	}

	bool outputTheInformation() const // Метод класу, що дозволяє вивести інформацію про книги
	{
		if (books.empty())
		{
			return false;
		}
		for (int i = 0; i < books.size(); i++)
		{	
			std::cout << "\nКнига " << i + 1 << ":\n\n";
			books[i].printInfo();
			std::cout << std::endl;
		}
		return true;
	}

	bool changeYear(int bookIndex, int newYear) // Метод класу, що дозволяє змінити рік видання книги за її індексом
	{
		if (books.empty() || bookIndex < 1 || bookIndex > books.size())
		{
			return false;
		}
		books[bookIndex - 1].setYear(newYear);
		return true;
	}

	bool clearBook(int index) // Метод класу, що дозволяє видалити книгу з бібліотеки за її індексом
	{
		if (books.empty() || index < 1 || index > books.size())
		{
			return false;
		}
		books.erase(books.begin() + index - 1);
		return true;
	}

	int countOfBooks() const // Метод класу, що дозволяє отримати кількість книг у бібліотеці
	{
		return books.size();
	}
};

bool checkEmptyStatus(const Library& lib)
{
	if (lib.countOfBooks() == 0)
	{
		std::cout << "\n[ПОМИЛКА] - Бібліотека порожня!\n(Спочатку додайте книги до бібліотеки!)\n" << std::endl;
		return true;
	}
	return false;
}

int main()
{
	SetConsoleOutputCP(65001); // Встановлення кодування консолі на UTF-8
	SetConsoleCP(65001); // Встановлення кодування консолі на UTF-8

	bool endOfProgram = false;
	int bookIndex;
	Library books = Library(); // Створення об'єкта класу Library для зберігання книг

	while (!endOfProgram) // Головний цикл програми, який продовжується, поки користувач не вибере вихід
	{
		displayMenu();
		std::cout << "[УВАГА] - Оберіть дію (1-5): ";
		int choice = input(1, 5); 

		switch (choice) // Використання конструкції switch для обробки вибору користувача
		{
		case 1:
			std::cout << "\nВведіть кількість книг, що плануєте додати до бібліотеки: ";
			int numBooks;
			numBooks = input(1, 100); 
			for (int i = 0; i < numBooks; i++) // Цикл для додавання вказаної кількості книг до бібліотеки
			{
				std::cout << "\nКнига " << books.countOfBooks() + 1 << ":\n\n";
				std::cout << "Введіть назву книги: ";
				std::string title;
				std::getline(std::cin, title);
				std::cout << "Введіть автора книги: ";
				std::string author;
				std::getline(std::cin, author);
				std::cout << "Введіть рік видання книги: ";
				int year = input(0, 2026);
				books.addBook(Book(title, author, year)); // Додавання нової книги до бібліотеки за допомогою методу addBook
			}
			std::cout << "\n[УВАГА] - Всі книги (" << numBooks << " шт.) є успішно доданими!\n" << std::endl;
			break;
		case 2:
			if (!books.outputTheInformation()) 
			{
				std::cout << "\n[ПОМИЛКА] - Бібліотека порожня!\n(Спочатку додайте книги до бібліотеки!)" << std::endl;
			}
			std::cout << std::endl;
			break;
		case 3:
			if (checkEmptyStatus(books)) // Якщо бібліотека порожня, вивести повідомлення про помилку
			{
				break;
			}
			std::cout << "\nВведіть номер книги, рік видання якої хочете змінити: ";
			bookIndex = input(1, books.countOfBooks());
			std::cout << "\nВведіть новий рік видання: ";
			int newYear;
			newYear = input(0, 2026);
			books.changeYear(bookIndex, newYear);
			std::cout << "\n[УВАГА] - Книзі під номером " << bookIndex << " успішно замінено рік видання!\n" << std::endl;
			break;
		case 4:
			if (checkEmptyStatus(books)) // Якщо бібліотека порожня, вивести повідомлення про помилку
			{
				break;
			}
			std::cout << "\nВведіть номер книги, яку хочете видалити з бібліотеки: ";
			bookIndex = input(1, books.countOfBooks());
			books.clearBook(bookIndex);
			std::cout << "\n[УВАГА] - Книгу під номером " << bookIndex << " успішно видалено!\n" << std::endl;
			break;

		case 5:
			endOfProgram = true; // Встановлення прапорця для завершення програми
			std::cout << "\n[УВАГА] - Завершення програми..." << std::endl;
			break;
		}
	}

	return 0; // Завершення програми з кодом 0, що означає успішне виконання 
}

 