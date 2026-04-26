// menu_of_prorgam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для роботи з консоллю
using namespace std; // Використання простору імен std

void printMenu() // Визначення функції для виведення меню
{
	cout << "\n==== МЕНЮ ====\n";
	cout << "1. Додати два числа\n";
	cout << "2. Відняти два числа\n";
	cout << "3. Вихід\n";
	cout << "Оберіть пункт: ";
}

int main() // Головна функція програми
{
	SetConsoleOutputCP(65001); // Кодування UTF-8
	SetConsoleCP(65001); // Кодування UTF-8
	bool running = true; // Змінна для контролю циклу
	while (running) // Основний цикл програми
	{
		printMenu(); // Виклик функції для виведення меню
		int choice;
		cin >> choice; // Зчитування вибору користувача
		switch (choice)  
		{
		case 1: 
		{
			int a, b;
			cout << "Введіть a і b: ";
			cin >> a >> b;
			cout << "Результат додавання: " << (a + b) << endl;
			break; // Вихід з цього випадку
		}
		case 2: 
		{
			int a, b;
			cout << "Введіть a і b: ";
			cin >> a >> b;
			cout << "Результат віднімання: " << (a - b) << endl;
			break; // Вихід з цього випадку
		}
		case 3:
			cout << "Завершення програми.\n";
			running = false; // Єдиний «вихід» із циклу
			break;
		default:
			cout << "Невірний вибір! Спробуйте ще раз." << endl;
		}
	}
	return 0; // Завершення програми з кодом успіху
}