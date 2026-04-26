// number_check.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h> // Для відображення український символів
#include <iostream>
#include <cmath> // Для sqrt()
using namespace std;
// Функція перевіряє, чи є число простим
// Параметр: n - ціле число
// Повертає: true якщо просте, false якщо ні
bool isPrime(int n) 
{
	if (n <= 1) return false;
	if (n <= 3) return true; // 2, 3 - прості

	// Перевіряємо дільники до sqrt(n)
	for (int i = 2; i <= sqrt(n); i++) 
	{
		if (n % i == 0) return false;
	}
	return true;
}
int main() 
{
	SetConsoleOutputCP(65001); // Налаштування кодування UTF-8
	SetConsoleCP(65001); // Налаштування кодування UTF-8

	int number;
	cout << "Введіть число: ";
	cin >> number;
	if (isPrime(number))
		cout << number << " - просте число.\n";
	else
		cout << number << " - не просте число.\n";

	return 0;
}