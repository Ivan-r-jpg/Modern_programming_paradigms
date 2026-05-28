// Program.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "User.h"
#include "Matrix.h"
#include "Income.h"
#include "BankAccount.h"
#include <Windows.h>

int main()
{
    SetConsoleOutputCP(65001);
	while (true)
	{
		std::cout << "\n=== ГОЛОВНЕ МЕНЮ ВИКОНАННЯ ЛАБОРАТОРНОЇ РОБОТИ ===\n\n"
			<< "1. Демонстрація класу User (Завдання 1);\n"
			<< "2. Демонстрація класу Matrix (Завдання 2);\n"
			<< "3. Демонстрація класу Income (Завдання 3);\n"
			<< "4. Демонстрація класу BankAccount (Завдання 4);\n"
			<< "5. Вихід.\n";

		int choice;
		choice = inputInteger(1, 5, "\nЗробіть Ваш вибір: ");

		system("cls");

		switch (choice)
		{
		case 1:
		{
			std::cout << "=== ДЕМОНСТРАЦІЯ РОБОТИ КЛАСУ USER ===\n\n";
			std::cout << "Кількість користувачів: " << User::getTotalUsers() << std::endl;
			User user1("Олександр", 0);
			std::cout << user1.getUserInfo() << "\n" << std::endl;
			// Створення блоку для демонстрації роботи конструктора та деструктора
			{
				std::cout << "Кількість користувачів: " << User::getTotalUsers() << std::endl;
				User user2("Марія", 1);
				std::cout << user2.getUserInfo() << "\n" << std::endl;
				// Створення вкладеного блоку для демонстрації роботи конструктора та деструктора
				{
					std::cout << "Кількість користувачів: " << User::getTotalUsers() << std::endl;
					User user3("Андрій", 0);
					std::cout << user3.getUserInfo() << "\n" << std::endl;
				}
			}
			// Після виходу з блоків, кількість користувачів повинна зменшитися, оскільки об'єкти user2 та user3 будуть знищені
			{
				std::cout << "Кількість користувачів: " << User::getTotalUsers() << std::endl;
				User user4("Іван", 2);
				std::cout << user4.getUserInfo() << "\n" << std::endl;
			}
			if (user1.changeAccessLevel(2)) // Спроба змінити рівень доступу користувача user1
			{
				std::cout << "[ОНОВЛЕННЯ] - Рівень доступу користувача успішно змінено!" << std::endl;
				std::cout << "Нові дані користувача: " << "\n" << user1.getUserInfo() << "\n" << std::endl;
			}
			else
			{
				std::cout << "\n[ПОМИЛКА] - Невірний рівень доступу для користувача!\n" << user1.getUserInfo() << "." << std::endl;
			}
			std::cout << "Кількість користувачів: " << User::getTotalUsers() << std::endl;
			User user5("Роман", 2);
			std::cout << user5.getUserInfo() << std::endl;
			std::cout << "\n[УВАГА] - Завершення демонстрації роботи класу User..." << std::endl;
			break;
		}
		case 2:
		{
			int rows1, cols1, rows2, cols2;
			std::cout << "=== МНОЖЕННЯ МАТРИЦЬ ===\n\n";
			std::cout << "[УВАГА] - Ініціалізація матриць:\n";
			rows1 = inputInteger(1, (std::numeric_limits<int>::max)(), "\n    Введіть кількість рядків для першої матриці: ");
			cols1 = inputInteger(1, (std::numeric_limits<int>::max)(), "    Введіть кількість стовпців для першої матриці: ");
			Matrix matrix1(rows1, cols1);

			rows2 = inputInteger(1, (std::numeric_limits<int>::max)(), "\n    Введіть кількість рядків для другої матриці: ");
			cols2 = inputInteger(1, (std::numeric_limits<int>::max)(), "    Введіть кількість стовпців для другої матриці: ");
			Matrix matrix2(rows2, cols2);
			try
			{
				if (cols1 != rows2)
				{
					throw std::invalid_argument("Матриці не можна перемножити!\n(Кількість стовпців першої матриці не дорівнює кількості рядків другої)");
				}
				matrix1.input();
				std::cout << matrix1;
				matrix2.input();
				matrix2.print();
				Matrix result = matrix1 * matrix2;
				std::cout << "\n[РЕЗУЛЬТАТ] - Результат множення матриць:\n";
				std::cout << result;
			}
			catch (const std::invalid_argument& e)
			{
				std::cerr << "\n[ПОМИЛКА] - " << e.what() << "\n";
				break;
			}
			std::cout << "\n[УВАГА] - Завершення демонстрації роботи класу Matrix..." << std::endl;
			break;
		}
		case 3:
		{
			// Створення об'єктів класу Income для відображення даних по двом місяцям
			Income month1(1000, 500);
			Income month2(1500, 700);
			std::cout << "=== ДОХОДИ ТА ВИТРАТИ ЗА ДВА МІСЯЦІ ===\n\n";
			std::cout << "Дані за місяць 1:\n" << month1;
			std::cout << "\nДані за місяць 2:\n" << month2;
			Income total = month1 + month2;
			std::cout << "\nСумарні доходи та витрати місяців 1 та 2:\n" << total;
			Income difference = month2 - month1;
			std::cout << "\nРізниця між місяцем 2 та місяцем 1:\n" << difference;

			month1 += month2;
			std::cout << "\nДоходи та витрати першого місяця після додавання до нього статистики за другий місяць:\n" << month1;
			month2 -= Income(500, 200);
			std::cout << "\nДоходи та витрати другого місяця після віднімання від нього статистики (500 доходу та 200 витрат):\n" << month2;

			std::cout << "\n[УВАГА] - Завершення демонстрації роботи класу Income..." << std::endl;
			break;
		}
		case 4:
		{
			// Створення трьох об'єктів класу BankAccount з різними початковими балансами
			BankAccount acc1(1000);
			BankAccount acc2(2000);
			BankAccount acc3(500);

			bool bankMenuRunning = true;

			while (bankMenuRunning)
			{
				std::cout << "=== МЕНЮ ===\n\n"
					<< "1. Встановити ставку;\n"
					<< "2. Застосувати відсотки до рахунку (За замовчуванням - 0.05);\n"
					<< "3. Переглянути баланси всіх рахунків;\n"
					<< "4. Вихід.\n";

				int choice = inputInteger(1, 4, "\nОберіть дію (1-4): ");

				switch (choice)
				{

				case 1: // Встановлення нової процентної ставки
				{
					double newRate = inputDouble(0, 1, "\nВведіть ставку (0-1): ");
					BankAccount::setInterestRate(newRate);
					std::cout << "\n[УВАГА] - Ставку оновлено!\n\n";
					break;
				}

				case 2: // Застосування відсотків до вибраного рахунку
				{
					int accNum = inputInteger(1, 3, "\nОберіть рахунок (1-3): ");

					if (accNum == 1)
					{
						acc1.applyInterest();
					}
					else if (accNum == 2)
					{
						acc2.applyInterest();
					}
					else
					{
						acc3.applyInterest();
					}

					std::cout << "\n[УВАГА] - Відсотки застосовано!\n\n";
					break;
				}

				case 3: // Виведення поточних балансів усіх рахунків
				{
					std::cout << "\nБаланс 1: " << acc1.getBalance() << " грн\n";
					std::cout << "Баланс 2: " << acc2.getBalance() << " грн\n";
					std::cout << "Баланс 3: " << acc3.getBalance() << " грн\n\n";
					break;
				}

				case 4: // Вихід з циклу
				{
					std::cout << "\n[УВАГА] - Завершення демонстрації роботи класу BankAccount...\n";
					bankMenuRunning = false;
					break;
				}
				}
			}
			break;
		}
		case 5:
		{
			std::cout << "\n[УВАГА] - Завершення роботи програми...\n";
			return 0; // Завершення роботи програми з кодом 0
		}
		}
	}
}


