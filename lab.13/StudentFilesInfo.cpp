// StudentFilesInfo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підлкючення бібліотеки для вводу/виводу
#include <sstream> // Підключення бібліотеки для зчитування рядків з потоку
#include <string> // Підключення бібліотеки для роботи з рядками
#include <Windows.h> // Підключення бібліотеки для роботи з консоллю
#include <limits> // Підключення бібліотеки для роботи з обмеженнями типів даних
#include <algorithm> // Підключення бібліотеки для алгоритмов, таких як std::max_element та std::remove_if
#include <vector> // Підключення бібліотеки для роботи з векторами
#include <iomanip> // Підключення бібліотеки для форматування виводу
#include <fstream> // Підключення бібліотеки для роботи з файлами
#include <conio.h> // Підключення бібліотеки для функції _getch()

struct Student // Структура для зберігання інформації про студента
{
	int ID;
	std::string fullName;
	std::string group;
	double averageGrade;
};

void printMenu() // Визначення функції для виводу меню програми
{
	std::cout << "МЕНЮ ПРОГРАМИ:\n\n";
	std::cout << "1. Додати нових студентів у файл;\n";
	std::cout << "2. Зчитати дані про студентів з файлу та вивести їх на екран;\n";
	std::cout << "3. Пошук студентів за групою;\n";
	std::cout << "4. Видалити студента з файлу;\n";
	std::cout << "5. Вихід." << std::endl;
}

int inputInt(int min, int max, const std::string& prompt) // Визначення функції для вводу цілого числа з валідацією та обробкою помилок
{
	int value;
	size_t pos;

	while (true)
	{
		std::cout << prompt;
		std::string input;
		std::getline(std::cin, input);
		try
		{
			try
			{
				value = stoi(input, &pos);
			}
			catch (const std::invalid_argument&)
			{
				throw std::invalid_argument("");
			}
			if (pos < input.length())
			{
				throw(std::invalid_argument(""));
			}
			if (value < min || value > max)
			{
				throw(std::out_of_range("Значення має бути в диапазоні від " + std::to_string(min) + " до " + std::to_string(max) + "!"));
			}
			return value;
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << "\n[ПОМИЛКА] - Знайдено зайві символи у записі! Введіть ціле число ще раз!" << std::endl;
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "\n[ПОМИЛКА] - " << e.what() << std::endl;
		}
	}
}

double inputDouble(double min, double max, const std::string& prompt) // Визначення функції для вводу дійсного числа з валідацією та обробкою помилок
{
	double value;
	size_t pos;

	while (true)
	{
		std::cout << prompt;
		std::string input;
		std::getline(std::cin, input);
		try
		{
			try
			{
				value = stod(input, &pos);
			}
			catch (const std::invalid_argument&)
			{
				throw std::invalid_argument("");
			}
			if (pos < input.length())
			{
				throw(std::invalid_argument(""));
			}
			if (value < min || value > max)
			{
				throw(std::out_of_range("Значення має бути в диапазоні від " + std::to_string(min) + " до " + std::to_string(max) + "!"));
			}
			return value;
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << "\n[ПОМИЛКА] - Знайдено зайві символи у записі! Введіть дійсне число ще раз!" << std::endl;
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "\n[ПОМИЛКА] - " << e.what() << std::endl;
		}
	}
}

void rewriteFile(const std::vector<Student>& students, const std::string& filename) // Визначення функції для перезапису файлу з оновленим списком студентів
{
	std::ofstream fout(filename); // Відкриття файлу для перезапису 

	if (!fout) // Перевірка на успішне відкриття файлу
	{
		throw std::runtime_error("Не вдалося відкрити файл для перезапису!"); // Викидання виключення у випадку помилки при відкритті файлу
	}

	for (const Student& student : students) // Запис інформації про кожного студента у файл
	{
		fout << student.ID << ";"
			<< student.fullName << ";"
			<< student.group << ";"
			<< student.averageGrade << std::endl;
	}

	fout.close(); // Закриття файлу після запису
}

void writeToFile(const Student& student, const std::string& filename) // Визначення функції для запису інформації про студента у файл
{
	std::ofstream fout(filename, std::ios::app); // Відкриття файлу для додавання інформації у режимі дозапису

	if (!fout) // Перевірка на успішне відкриття файлу
	{
		throw std::runtime_error("Не вдалося відкрити файл studentsInfo.txt для запису!"); // Викидання виключення у випадку помилки при відкритті файлу
	}
	
	fout << student.ID << ";" << student.fullName << ";" 
		<< student.group << ";" << student.averageGrade << std::endl;

	fout.close(); // Закриття файлу після запису
}

void readFromFile(std::vector<Student>& students, const std::string& filename) // Визначення функції для зчитування інформації про студентів з файлу
{
	students.clear(); // Очищення вектора студентів перед зчитуванням нових даних

	std::ifstream fin(filename); // Відкриття файлу для зчитування

	if (!fin) // Перевірка на успішне відкриття файлу
	{
		throw std::runtime_error("Не вдалося відкрити файл studentsInfo.txt!"); // Викидання виключення у випадку помилки при відкритті файлу
	}

	int lineNumber = 0; // Змінна для відстеження номера рядка при зчитуванні файлу
	std::string line; 

	while (std::getline(fin, line)) // Зчитування файлу рядок за рядком
	{
		Student student;

		std::stringstream ss(line); // Створення об'єкта потоку для передачі одного рядка з файлу

		// Змінні для зберігання окремих полів інформації про студента, які будуть зчитані з рядка
		std::string idStr;
		std::string fullName;
		std::string group;
		std::string averageStr;

		// Зчитування окремих полів інформації про студента з рядка, розділеного символом ';'
		getline(ss, idStr, ';');
		getline(ss, fullName, ';');
		getline(ss, group, ';');
		getline(ss, averageStr);
		
		// Спроба конвертації зчитаних рядків у відповідні типи даних та додавання інформації про студента у вектор
		try
		{
			student.ID = std::stoi(idStr);
			student.fullName = fullName;
			student.group = group;
			student.averageGrade = std::stod(averageStr);
			students.push_back(student);
			lineNumber++;
		}
		catch (const std::invalid_argument& e) // Перехоплення виключення у випадку помилки конвертації рядка у число
		{
			if (line != "") // Перевірка, чи рядок не є порожнім, щоб уникнути помилки при зчитуванні пустих рядків
			{
				std::cerr << "[ПОМИЛКА] - Невірний формат даних у рядку " << lineNumber + 1 << "!" << std::endl;
			}
		}
	}

	fin.close(); // Закриття файлу після зчитування
}

void printTable(const std::vector<Student>& students) // Визначення функції для виводу інформації про студентів у вигляді таблиці
{
	std::cout << std::left;

	std::cout << " " << std::setfill('-') << std::setw(87) << "-" << std::endl;

	std::cout << std::setfill(' ')
		<< "| " << std::setw(5) << "ID"
		<< "| " << std::setw(50) << "Прізвище Ім'я"
		<< "| " << std::setw(10) << "Група"
		<< "| " << std::setw(15) << "Середній бал" << "|" << std::endl;

	std::cout << " " << std::setfill('-') << std::setw(87) << "-" << std::endl;

	std::cout << std::setfill(' ');

	for (const Student& student : students) // Вивід інформації про кожного студента у вигляді рядка таблиці
	{
		std::cout << "| " << std::setw(5) << student.ID
			<< "| " << std::setw(50) << student.fullName
			<< "| " << std::setw(10) << student.group
			<< "| " << std::setw(15) << student.averageGrade << "|" << std::endl;
	}

	std::cout << " " << std::setfill('-') << std::setw(87) << "-" << std::endl;
}

int main() // Головна функція програми
{
	SetConsoleOutputCP(1251); // Встановлення кодування ANSI для виводу символів на консоль
	SetConsoleCP(1251); // Встановлення кодування ANSI для вводу символів в консоль
	
	std::vector<Student> students; // Створення вектора для зберігання інформації про студентів

	while (true) // Основний цикл програми для відображення меню та обробки вибору користувача
	{ 
		system("cls");
		printMenu();

		int choice = inputInt(1, 5, "\n[УВАГА] - Введіть номер пункту меню: "); 

		switch (choice) // Обробка вибору користувача за допомогою оператора switch
		{
		case 1:
		{
			system("cls");
			// Спроба зчитування існуючих даних про студентів з файлу для визначення наступного ID, який буде присвоєно новому студенту
			try
			{
				readFromFile(students, "studentsInfo.txt");
			}
			catch (const std::runtime_error&)
			{
				students.clear();
			}

			auto maxStudent = std::max_element(students.begin(), students.end(),
				[](const Student& a, const Student& b)
				{
					return a.ID < b.ID;
				}); // Знаходження студента з максимальним ID для визначення наступного ID

			int nextID;

			if (maxStudent != students.end()) // Якщо вектор студентів не порожній
			{
				nextID = maxStudent->ID + 1; // Встановлюється nextID на значення + 1 більше від максимального
			}
			else // Якщо вектор студентів порожній, то nextID встановлюється як 1
			{
				nextID = 1;
			}

			int numberOfRecords = inputInt(1, (std::numeric_limits<int>::max)(),
				"\nВведіть кількість записів, що потрібно створити: ");

			for (int i = 0; i < numberOfRecords; i++) // Цикл для вводу інформації про кожного нового студента
			{
				Student student;

				std::cout << "\nЗапис " << i + 1 << ":\n";

				student.ID = nextID++;

				std::cout << "Введіть повне ім'я студента: ";
				std::getline(std::cin, student.fullName);

				std::cout << "Введіть групу студента: ";
				std::getline(std::cin, student.group);

				student.averageGrade = inputDouble(0.0, 5.0,
					"Введіть середній бал студента: ");

				// Спроба запису інформації про студента у файл
				try
				{
					writeToFile(student, "studentsInfo.txt");
					
				}
				catch (const std::runtime_error& e) // Перехоплення виключення у випадку помилки при записі у файл
				{
					std::cerr << "\n[ПОМИЛКА] - " << e.what() << std::endl;
					break;
				}
			}

			students.clear(); // Очищення вектора студентів після запису нових даних у файл

			std::cout << "\n[УСПІХ] - Дані успішно записані у файл!\n" << std::endl;
			std::cout << "Натисніть будь-яку клавішу для повернення до меню..." << std::endl;

			_getch();
			break;
		}
		case 2:
		{
			system("cls");

			// Спроба зчитування даних про студентів з файлу та виводу їх на екран у вигляді таблиці
			try
			{
				readFromFile(students, "studentsInfo.txt");
				printTable(students);
				students.clear();
				std::cout << "\n[УСПІХ] - Дані успішно зчитано з файлу!\n" << std::endl;
			}
			catch (const std::runtime_error& e) // Перехоплення виключення у випадку помилки при зчитуванні з файлу
			{
				std::cerr << "\n[ПОМИЛКА] - " << e.what() << "\n" << std::endl;
			}
			std::cout << "Натисніть будь-яку клавішу для повернення до меню..." << std::endl;

			_getch();
			break;
		}
		case 3:
		{
			bool studentNotFound = false;

			system("cls");

			// Спроба зчитування даних про студентів з файлу для виконання пошуку за групою та виводу результатів на екран
			try
			{
				readFromFile(students, "studentsInfo.txt");
				printTable(students);
			}
			catch (const std::runtime_error& e) // Перехоплення виключення у випадку помилки при зчитуванні з файлу
			{
				std::cerr << "[ПОМИЛКА] - " << e.what() << std::endl;
			}

			std::string groupToSearch;

			std::cout << "Введіть назву групи для пошуку: ";
			std::getline(std::cin, groupToSearch);
			std::vector<Student> filteredStudents;

			for (const Student& student : students) // Цикл для фільтрації студентів за вказаною групою
			{
				if (student.group == groupToSearch) // Якщо група студента відповідає введеній групі для пошуку
				{
					filteredStudents.push_back(student); // Додавання студента до вектора відфільтрованих студентів
					studentNotFound = true; // Встановлення прапорця, що студент з вказаною групою знайдений
				}
			}
			if (!studentNotFound) // Якщо студент з вказаною групою не знайдений, виводиться відповідне повідомлення
			{
				std::cout << "\n[УВАГА] - Студентів з такою групою не знайдено!\n";
				std::cout << "\n[ХАЛЕПА] - Пошук завершено!\n" << std::endl;

				std::cout << "Натисніть будь-яку клавішу для повернення до меню..." << std::endl;

				_getch();
				break;
			}

			std::cout << "\n";
			printTable(filteredStudents);
			filteredStudents.clear(); // Очищення вектора відфільтрованих студентів після виводу результатів на екран

			std::cout << "\n[УВАГА] - Пошук завершено!\n" << std::endl;
			std::cout << "Натисніть будь-яку клавішу для повернення до меню..." << std::endl;

			_getch();
			break;
		}
		case 4:
		{
			system("cls");

			// Спроба зчитування даних про студентів з файлу
			try
			{
				readFromFile(students, "studentsInfo.txt");
				printTable(students);
			}
			catch (const std::runtime_error& e) // Перехоплення виключення у випадку помилки при зчитуванні з файлу
			{
				std::cerr << "\n[ПОМИЛКА] - " << e.what() << "\n" << std::endl;
				break;
			}

			int idToDelete = inputInt(1, (std::numeric_limits<int>::max)(), "Введіть ID студента для видалення: ");

			auto newEnd = std::remove_if(students.begin(), students.end(),
				[idToDelete](const Student& student)
				{
					return student.ID == idToDelete;
				}); // Використання алгоритму std::remove_if для переміщення студентів з вказаним ID в кінець вектора та отримання ітератора на нову "кінцеву" позицію

			if (newEnd != students.end()) // Якщо знайдено студента з вказаним ID для видалення
			{
				students.erase(newEnd, students.end()); // Видалення студентів з вказаним ID з вектора, використовуючи отриманий ітератор 

				// Спроба перезапису файлу з оновленим списком студентів після видалення
				try
				{
					rewriteFile(students, "studentsInfo.txt");
					std::cout << "\n[УСПІХ] - Студент з ID " << idToDelete << " успішно видалений!\n" << std::endl;
				}
				catch (const std::runtime_error& e) // Перехоплення виключення у випадку помилки при перезапису файлу
				{
					std::cerr << "\n[ПОМИЛКА] - " << e.what() << "\n" << std::endl;
				}
			}
			else // Якщо студент з вказаним ID не знайдено для видалення
			{
				std::cout << "\n[УВАГА] - Студента з таким ID не знайдено!\n" << std::endl;;
			}

			students.clear(); // Очищення вектора студентів після виконання операції видалення та перезапису файлу

			std::cout << "Натисніть будь-яку клавішу для повернення до меню..." << std::endl;

			_getch();
			break;
		}

		case 5:
		{
			std::cout << "\n[УВАГА] - Завершення роботи програми..." << std::endl;
			return 0; // Вихід з програми
		}
		}
	}
}


