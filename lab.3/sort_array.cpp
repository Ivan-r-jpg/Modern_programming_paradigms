// sort_array.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для роботи з консоллю
#include <cstdlib> // Підключення бібліотеки для генерації випадковостей
#include <ctime> // Підключення бібліотеки для роботи з часом
#include <string> // Підключення бібліотеки для роботи з рядками

int checkInput(const std::string& input) /* Функція для 
перевірки коректності введення розміру масиву 
*/
{
	size_t pos;
	int size = 0; // Ініціалізація змінної для збереження розміру масиву
	try
	{
		// Спроба конвертації рядка в ціле число
		try
		{
			size = std::stoi(input, &pos);
		}
		catch (const std::exception&) 
		{
			throw std::invalid_argument("Некоректний ввід!");
		}
		catch (const std::out_of_range&)
		{
			throw std::invalid_argument("Некоректний ввід!");
		}
		if (pos < input.length()) /* Перевірка на наявність зайвих 
			символів
			*/
		{
			throw std::invalid_argument("Некоректний ввід!");
		}
	}
	catch (const std::invalid_argument& e) // Перехоплення виключення
	{
		std::cout << "\n[ПОМИЛКА] - " << e.what() << std::endl;
		size = -1; // Повернення -1 для позначення некоректного вводу
	}
	
	return size; // Повернення розміру масиву або -1 у випадку помилки
}

void initArray(int* arr, int size) /* Функція для ініціалізації 
масиву випадковими числами
*/
{
	srand(static_cast<unsigned int>(time(0))); /* Ініціалізація генератора 
	випадкових чисел
	*/
	// Заповнення масиву випадковими числами від 1 до 100
	for (int i = 0; i < size; ++i) 
	{
		arr[i] = rand() % 100 + 1;
	}
}

void printArray(int* arr, int size) // Функція для виведення масиву 
{
	std::cout << "[ ";
	for (int i = 0; i < size; ++i)
	{
		if (i == size - 1)
		{
			std::cout << arr[i] << " ]";	
		}
		else
		{
			std::cout << arr[i] << "; ";
		}
	}
	std::cout << std::endl;
}

void sortArray(int* arr, int size) /* Функція для сортування масиву 
за допомогою алгоритму бульбашки
*/
{
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
}

int main() // Головна функція програми
{
	SetConsoleOutputCP(65001); // Встановлення кодування UTF-8 
	SetConsoleCP(65001); // Встановлення кодування UTF-8 

	int size;
	std::string input;

	std::cout << "Введіть розмір масиву: ";
	std::getline(std::cin, input);
	size = checkInput(input); // Перевірка введення розміру масиву
	// Цикл для повторного вводу розміру масиву, якщо введення некоректне
	while (size <= 0 || size > 100) 
	{
		std::cout << "\n[УВАГА] - Розмір масиву повинен в межах від 1 до 100!"
			"\n\nСпробуйте ще раз: ";
		std::getline(std::cin, input);
		size = checkInput(input);
	}
	int* arr = new int[size]; // Динамічне виділення пам'яті під масив

	initArray(arr, size);
	std::cout << "\n[УВАГА] - Невідсортований масив:\n" << std::endl;
	printArray(arr, size);

	sortArray(arr, size);
	std::cout << "\n[УВАГА] - Відсортований масив:\n" << std::endl;
	printArray(arr, size);

	// Звільнення виділеної пам'яті під масив
	delete[] arr;
	arr = nullptr;

	return 0; // Успішне завершення програми з кодом 0
}
