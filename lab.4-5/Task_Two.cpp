#include "Task_Two.h" // Підключення заголовочного файлу

std::vector<SensorReading> filter(const std::vector<SensorReading>&
	readings) // Визначення функції для фільтрації даних з сенсорів
{
	std::vector<SensorReading> filteredReadings;

	std::copy_if(readings.begin(), readings.end(),
		std::back_inserter(filteredReadings), [](const SensorReading& r)
		{
			return r.temperature > 35.0 || r.humidity < 40.0;
		}); // Використання алгоритму copy_if для копіювання лише тих зчитувань, які відповідають умовам

	return filteredReadings; // Повернення відфільтрованого вектора зчитувань
}