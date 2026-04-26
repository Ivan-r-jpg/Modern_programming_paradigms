// input_number.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
using namespace std;
int main() 
{
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	int number;
	cout << "Введіть число [1..100]: ";
	cin >> number;
	// Цикл продовжується, поки умова НЕ виконується
	while (number < 1 || number > 100) 
	{
		cout << "Помилка! Число повинно бути від 1 до 100.\n";
		cout << "Спробуйте ще раз: ";
		cin >> number;
	}
	cout << "Дякуємо! Ви ввели коректне число: " << number << endl;
	return 0;
}

