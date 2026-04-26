#include "Task_One.h"                                // підключаємо заголовний файл з оголошеннями функцій

// функція перетворення температури з градусів Цельсія у Фаренгейти
double celsiusToFahrenheit(double c)
{
	return (c * 1.8) + 32;                           // формула для переведення
}

// функція розрахунку дефіциту тиску пари (VPD)
double calculateVPD(double temp, double humidity)
{
	// повертаємо результат математичної формули розрахунку VPD
	return 0.6108 * std::exp(17.27 * temp / (temp + 237.3)) * (1.0 - humidity / 100.0);
}

// функція перевірки оптимальності температури
bool isOptimalTemperature(double temp)
{
	// повертаємо true, якщо температура в межах від 18.0 до 26.0 включно, інакше false
	return temp >= 18.0 && temp <= 26.0;
}

// функція вищого порядку для перетворення масиву за допомогою переданої функції
std::vector <double> transformReadings(const std::vector <double>& readings, const std::function<double(double)>& func)
{
	std::vector <double> result;                     // створюємо порожній вектор для збереження оброблених результатів
	result.reserve(readings.size());				 // резервуємо пам'ять

	// застосовуємо передану func до кожного елемента вектора readings та записуємо в result
	std::transform(readings.begin(), readings.end(), std::back_inserter(result), func); 

	return result;                                   // повертаємо новий вектор з перетвореними значеннями
}