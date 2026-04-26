#include <iostream>
#include <algorithm>

#include "UserInteraction.h"

#define MIN_SIZE 1 // Визначення мінімальної кількості теплиць
#define MAX_SIZE 50 // Визначення максимальної кількості теплиць

int main() // Головна функція програми
{
	int numberGreenhouses = inputProcessing(MIN_SIZE, MAX_SIZE,
		"Enter the number of greenhouses: "); // Використання функції inputProcessing для отримання кількості теплиць від користувача 

	std::vector<SensorReading> readings;
	readings.reserve(numberGreenhouses);

	bool endOfProgram = true;

	readings = generateRandomReadings(numberGreenhouses); /* Використання функції generateRandomReadings для генерації вектора зчитувань
	з кількістю елементів, що відповідає кількості теплиць */

	while (endOfProgram) // Основний цикл програми, який продовжується, поки користувач не вибере опцію виходу
	{
		printInsructions(); // Використання функції printInsructions для виведення інструкцій користувачу

		int userChoice = inputProcessing(0, 7, "Enter your choice: "); // Використання функції inputProcessing для отримання вибору користувача

		switch (userChoice) // Використання оператора switch для обробки вибору користувача
		{
		case 1:
			chooseOne(readings);
			break;
		case 2:
			chooseTwo(readings);
			break;
		case 3:
			chooseThree(readings);
			break;
		case 4:
			chooseFour(readings);
			break;
		case 5:
			chooseFive(readings);
			break;
		case 6:
			chooseSix(readings);
			break;
		case 7:
			readings = chooseSeven(readings);
			break;
		case 0:
			std::cout << "\nExiting the program...\n";
			endOfProgram = false; // Встановлення прапорця для виходу з основного циклу
			break; // Вихід з програми
		}
	}
	return 0; // Завершення пррограми з кодом успіху
}
