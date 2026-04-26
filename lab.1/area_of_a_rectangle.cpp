// area_of_a_rectangle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу

int main() // Головна функція програми
{
	// Оголошення змінних для зберігання значення ширини та довжини прямокутника
	double width = 0.0; 
	double height = 0.0;
	std::cout << "Enter the width of the rectangle: ";
	std::cin >> width; // Введення значення ширини з клавіатури

	std::cout << "Enter the height of the rectangle: ";
	std::cin >> height; // Введення значення довжини з клавіатури

	const double area = width * height; // Обчислення площі
	std::cout << "The area of the rectangle is: " << area << '\n';

	return 0; // Завершення програми з кодом 0
}
