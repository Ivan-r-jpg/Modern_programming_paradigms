#pragma once

#include <vector> // Підлкючення бібліотеки для роботи з векторами
#include <algorithm> // Підключення бібліотеки для використання алгоритмів
#include <iterator> // Підключення бібліотеки для використання ітераторів

struct SensorReading // Структура для зберігання даних з сенсорів
{
	int zoneId; // Ідентифікатор зони
	int hour; // Час зчитування даних
	double temperature; // Температура в градусах Цельсія
	double humidity; // Вологість у відсотках
};

std::vector<SensorReading> filter(const std::vector<SensorReading>&
	readings); // Прототип функції для фільтрації даних з сенсорів
