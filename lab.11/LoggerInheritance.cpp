// LoggerInheritance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <Windows.h> // Підключення бібліотеки для роботи з консоллю 
#include <fstream> // Підключення бібліотеки для роботи з файлами
#include <vector> // Підключення бібліотеки для роботи з векторами
#include <string> // Підключення бібліотеки для роботи з рядками

class Logger // Базовий клас "Logger"
{
public:

	virtual void log(const std::string& message) = 0; // Чистий віртуальний метод для логування повідомлення

	virtual std::string getType() const // Віртуальний метод для отримання типу логера
	{
		return "Базовий Logger";
	}

	virtual ~Logger() // Віртуальний деструктор для коректного видалення об'єктів через покажчик на базовий клас
	{
		std::cout << "[Logger] - Деструктор викликано!\n";
	}
};

class ConsoleLogger : public Logger // Похідний клас "Консольний Logger"
{
public:

	void log(const std::string& message) override // Перевизначення методу для виводу повідомлення у консоль
	{
		std::cout << "[Console] " << message << std::endl;
	}

	std::string getType() const override // Перевизначення методу для отримання типу логера
	{
		return "Консольний Logger";
	}

	~ConsoleLogger() // Деструктор класу ConsoleLogger
	{
		std::cout << "[ConsoleLogger] - Деструктор викликано!\n";
	}
};

class FileLogger : public Logger // Похідний клас "Файловий Logger"
{
private:

	std::ofstream file; // Потік для запису повідомлень у файл

public:

	FileLogger() // Конструктор класу FileLogger
	{
		file.open("log.txt", std::ios::app); // Відкриття файлу для дозапису повідомлень
	}

	void log(const std::string& message) override // Перевизначення методу для запису повідомлення у файл
	{
		if (file.is_open()) // Перевірка, чи файл успішно відкритий
			file << "[File] " << message << std::endl;
	}

	std::string getType() const override // Перевизначення методу для отримання типу логера
	{
		return "Файловий Logger";
	}

	~FileLogger() // Деструктор класу FileLogger
	{
		std::cout << "[FileLogger] - Деструктор викликано!\n";
		file.close(); // Закриття файлу
	}
};

class MemoryLogger : public Logger // Похідний клас "Memory Logger"
{
private:

	std::vector<std::string> messages; // Вектор для зберігання повідомлень у пам'яті

public:

	void log(const std::string& message) override // Перевизначення методу для збереження повідомлення у пам'яті
	{
		messages.push_back(message); // Додавання повідомлення у вектор
	}

	std::string getType() const override // Перевизначення методу для отримання типу логера
	{
		return "Memory Logger";
	}

	const std::vector<std::string>& getMessages() const // Метод для отримання всіх збережених повідомлень
	{
		return messages;
	}

	~MemoryLogger() // Деструктор класу MemoryLogger
	{
		std::cout << "[MemoryLogger] - Деструктор викликано!\n";
	}
};

int main() // Головна функція програми
{
	SetConsoleOutputCP(65001); // Встановлення кодування для коректного відображення українських символів у консолі

	std::vector<Logger*> loggers; // Створення вектора покажчиків на базовий клас Logger

	// Додавання об'єктів похідних класів у вектор
	loggers.push_back(new ConsoleLogger());
	loggers.push_back(new FileLogger());
	loggers.push_back(new MemoryLogger());

	for (Logger* logger : loggers) // Демонстрація поліморфізму
	{
		std::cout << "Logger тип: " << logger->getType() << std::endl; 
		logger->log("Якесь повідомлення"); 
	}

	for (Logger* logger : loggers) // Очищення пам'яті
	{
		delete logger; 
	}

	return 0; // Завершення програми з кодом 0
}