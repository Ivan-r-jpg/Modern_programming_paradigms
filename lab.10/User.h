#pragma once
#include <string>
#include <vector>

class User
{
private:

	std::string name;
	const int userID; // Унікальний ідентифікатор користувача, який не змінюється після створення
	int accessLevelIndex;
	static int totalUsers; // Статична змінна для відстеження загальної кількості користувачів
	static int nextID; // Статична змінна для генерації унікальних ідентифікаторів користувачів
	static std::vector<std::string> accessLevels;

public:

	User(const std::string& name, int accessLevelIndex) : name(name), userID(nextID++) // Конструктор зі списком ініціалізації
	{
		if (accessLevelIndex >= 0 && accessLevelIndex < static_cast<int>(accessLevels.size())) // Перевірка правильності індексу рівня доступу
		{
			this->accessLevelIndex = accessLevelIndex; // Встановлення рівня доступу даному об'єкту
		}
		else // Якщо індекс неправильний, то встановлюється рівень доступу за замовчуванням (0 - User)
		{
			this->accessLevelIndex = 0;
		}
		totalUsers++; // Збільшення загальної кількості користувачів при створенні нового об'єкта
	}

	~User() // Деструктор, який зменшує загальну кількість користувачів при знищенні об'єкта
	{
		totalUsers--;
	}

	std::string getUserInfo() const // Метод для отримання інформації про користувача у вигляді рядка
	{
		return "UserID: " + std::to_string(userID) + ", Ім'я: " + name + ", Рівень доступу: " + accessLevels[accessLevelIndex];
	}

	static int getTotalUsers() // Метод для отримання загальної кількості користувачів
	{
		return totalUsers;
	}

	bool changeAccessLevel(int newLevel) // Метод для зміни рівня доступу користувача
	{
		if (newLevel >= 0 && newLevel < static_cast<int>(accessLevels.size()))
		{
			accessLevelIndex = newLevel;
			return true;
		}
		else
		{
			return false;
		}
	}

};
