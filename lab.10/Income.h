#pragma once
#include <iostream>

class Income
{
private:

	double revenue; // Поле "Дохід"
	double expense; // Поле "Витрати"

public:

	Income() : revenue(0), expense(0) {} // Конструктор за замовчуванням

	Income(double rev, double exp) : revenue(rev), expense(exp) {} // Конструктор з параметрами

	Income operator + (const Income& other) const // Перевантаження оператора додавання
	{
		return Income(revenue + other.revenue, expense + other.expense);
	}

	Income operator - (const Income& other) const // Перевантаження оператора віднімання
	{
		return Income(revenue - other.revenue, expense - other.expense);
	}

	friend std::ostream& operator << (std::ostream& out, const Income& object) // Перевантаження оператора виводу
	{
		out << "Дохід: " << object.revenue << std::endl;
		out << "Витрати: " << object.expense << std::endl;
		return out;
	}

	Income& operator += (const Income& other) // Перевантаження оператора додавання з присвоєнням
	{
		revenue += other.revenue;
		expense += other.expense;
		return *this;
	}

	Income& operator -= (const Income& other) // Перевантаження оператора віднімання з присвоєнням
	{
		revenue -= other.revenue;
		expense -= other.expense;
		return *this;
	}

};