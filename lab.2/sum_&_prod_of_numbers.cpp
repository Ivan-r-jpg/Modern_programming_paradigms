// sum_&_prod_of_numbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Для вводу/виводу
#include <Windows.h> // Для правильного відображення символів кирилиці
using namespace std; // Використання простору імен std

int sumOfNumbers(int N); // Прототип функції, що рахує суму з N чисел

int main() 
{
	SetConsoleOutputCP(65001); // Налаштування кодування UTF-8
	SetConsoleCP(65001); // Налаштування кодування UTF-8
	// Оголошення та ініціалізація змінних
	int N; 
	int sum = 0;
	int prod = 1;
	cout << "Введіть число N: ";
	cin >> N; // Введення числа з клавіатури
	while (N <= 0) // Нескінченний цикл вводу правильного значення
	{
		cout << "[ПОМИЛКА] - Введіть невід'ємне число: ";
		cin >> N; // Введення числа з клавіатури
	}
	for (int i = 1; i <= N; i++) // Цикл по кожному числу від 1 до N
	{
		prod *= i; // Множення чисел
	}
	sum = sumOfNumbers(N); // Виклик функції
	// Виведення результатів
	cout << "Сума чисел від 1 до " << N << " дорівнює " << sum <<
		endl;
	cout << "Добуток чисел від 1 до " << N << " дорівнює " << prod <<
		endl;
	
	return 0; // Завершення програми з кодом 0
}

int sumOfNumbers(int N) // Визначення функції, що рахує суму з N чисел
{
	int sum = 0; // Ініціалізація змінної sum
	for (int i = 1; i <= N; i++) // Цикл по кожному числу від 1 до N
	{
		sum += i; // Додавання числа до загальної суми
	}
	return sum; // Повернення результату
}