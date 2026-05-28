#pragma once
#include <iostream>

class BankAccount
{
private:

	double balance; // Поле "Баланс"
	static double interestRate; // Статичне поле "Процентна ставка"

public:

	BankAccount(double bal) : balance(bal) {} // Конструктор для ініціалізації балансу

	void applyInterest() // Метод для застосування відсотків до балансу
	{
		balance += balance * interestRate;
	}

	static void setInterestRate(double newRate) // Статичний метод для встановлення процентної ставки
	{
		if (newRate < 0 || newRate > 1) // Перевірка на допустимість значення процентної ставки
		{
			std::cerr << "[ПОМИЛКА] - Неприпустиме значення процентної ставки!\n(Має бути між 0 та 1...)\n";
			return; // Вихід з методу
		}
		interestRate = newRate; // Встановлення нового значення процентної ставки
	}

	double getBalance() const // Метод для отримання значення поточного балансу
	{
		return balance;
	}
};
