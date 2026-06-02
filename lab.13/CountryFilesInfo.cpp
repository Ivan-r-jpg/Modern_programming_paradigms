// CountryFilesInfo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу 
#include <Windows.h> // Підключення бібліотеки для роботи з консоллю Windows
#include <fstream> // Підключення бібліотеки для роботи з файлами
#include <vector> // Підключення бібліотеки для використання контейнера vector
#include <string> // Підключення бібліотеки для роботи з рядками
#include <sstream> // Підключення бібліотеки для роботи з потоками рядків
#include <algorithm> // Підключення бібліотеки для використання алгоритму сортування
#include <iomanip> // Підключення бібліотеки для форматування виводу

struct CountryInfo // Визначення структури для зберігання інформації про країну
{
	std::string name; // Поле для зберігання назви країни
	std::string capital; // Поле для зберігання назви столиці країни
};

void printTable(const std::vector<CountryInfo>& countries, std::ostream& out) // Визначення функції для виводу інформації про країни у вигляді таблиці
{
	out << std::left;

	out << " " << std::setfill('-') << std::setw(48) << "-" << std::endl;

	out << std::setfill(' ')
		<< "| " << std::setw(25) << "Назва країни"
		<< "| " << std::setw(20) << "Столиця" << "|" << std::endl;

	out << " " << std::setfill('-') << std::setw(48) << "-" << std::endl;

	out << std::setfill(' ');

	for (const CountryInfo& country : countries) // Вивід інформації про кожну країну у вигляді рядка таблиці
	{
		out << "| " << std::setw(25) << country.name
			<< "| " << std::setw(20) << country.capital << "|" << std::endl;
	}

	out << " " << std::setfill('-') << std::setw(48) << "-" << std::endl;
}

void writeToFile(const std::vector<CountryInfo>& countries, const std::string& filename) // Визначення функції для запису інформації про країну у файл
{
	std::ofstream fout(filename); // Відкриття файлу для додавання інформації

	if (!fout) // Перевірка на успішне відкриття файлу
	{
		throw std::runtime_error("Не вдалося відкрити файл countriesInfo.txt для запису!"); // Викидання виключення у випадку помилки при відкритті файлу
	}

	fout << std::setfill('=') << std::setw(17) << "=" << " Довідник країн " << std::setw(17) << "=" << "\n" << std::endl;

	printTable(countries, fout);

	fout << std::setfill('=') << std::setw(50) << "=" << "\n" << std::endl;

	fout.close(); // Закриття файлу після запису
}

void readFromFile(std::vector<CountryInfo>& countries, const std::string& filename) // Визначення функції для зчитування інформації про країни з файлу
{
	countries.clear(); // Очищення вектора країн перед зчитуванням нових даних

	std::ifstream fin(filename); // Відкриття файлу для зчитування

	if (!fin) // Перевірка на успішне відкриття файлу
	{
		throw std::runtime_error("Не вдалося відкрити файл countriesInfo.txt!"); // Викидання виключення у випадку помилки при відкритті файлу
	}

	std::string line;

	while (std::getline(fin, line)) // Зчитування файлу рядок за рядком
	{
		CountryInfo country;

		std::stringstream ss(line); // Створення об'єкта потоку для передачі одного рядка з файлу

		// Змінні для зберігання окремих полів інформації про країну, які будуть зчитані з рядка
		std::string nameStr;
		std::string capitalStr;

		// Зчитування окремих полів інформації про країну з рядка, розділеного символом ';'
		getline(ss, nameStr, ';');
		getline(ss, capitalStr, ';');

		// Присвоєння зчитаних значень полям структури CountryInfo та додавання її до вектора країн
		country.name = nameStr;
		country.capital = capitalStr;
		countries.push_back(country);	
	}

	fin.close(); // Закриття файлу після зчитування
}

void sortCountries(std::vector<CountryInfo>& countries) // Визначення функції для сортування інформації про країни за назвою
{
	std::sort(countries.begin(), countries.end(), 
		[](const CountryInfo& a, const CountryInfo& b) {
		return a.name < b.name; 
		}); // Використання алгоритму std::sort з лямбда-функцією для порівняння назв країн та сортування їх у алфавітному порядку
}

int main() // Головна функція програми
{
	SetConsoleOutputCP(1251); // Встановлення кодування для виводу в консоль

	std::vector <CountryInfo> countries; // Створення вектора для зберігання інформації про країни

	// Спроба зчитування з файлу, вивід інформації у вигляді таблиці, сортування та запис у новий файл
	try
	{
		readFromFile(countries, "countriesInfo.txt"); 
		std::cout << "\n[ІНФОРМАЦІЯ] - Інформація про країни успішно зчитана з файлу countriesInfo.txt!\n" << std::endl; 
		printTable(countries, std::cout); 

		sortCountries(countries); 
		std::cout << "\n[ІНФОРМАЦІЯ] - Інформація про країни успішно відсортована за назвою!\n" << std::endl; 
		printTable(countries, std::cout); 

		writeToFile(countries, "countriesDirectory.txt"); 
		std::cout << "\n[ІНФОРМАЦІЯ] - Каталог країн успішно створено у файлі countriesDirectory.txt!\n" << std::endl;
	}
	catch (const std::runtime_error& e) // Перехоплення виключення у випадку помилки при роботі з файлами
	{
		std::cerr << "\n[ПОМИЛКА] - " << e.what() << "\n" << std::endl; 
	}
	
	std::cout << "[УВАГА] - Завершення роботи програми!" << std::endl;

    return 0; // Завершення роботи програми з кодом 0
}



