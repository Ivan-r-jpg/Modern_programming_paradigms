#include "Task_Four.h" // Підключення заголовочного файлу

double calculateAVGTemp(const std::vector<SensorReading>& reading) // Визначення функції для обчислення середнього значення температури
{
	std::vector<SensorReading> stressZones;

	std::copy_if(reading.begin(), reading.end(),
		std::back_inserter(stressZones), [](const SensorReading& r)
		{
			return r.temperature > 28.0 || r.temperature < 16.0;
		}); // Використання алгоритму copy_if для копіювання лише тих зчитувань, які відповідають умовам

	if (stressZones.empty()) // Перевірка на випадок, якщо немає зчитувань, що відповідають умовам
	{
		return 0.0;
	}

	double sum = std::accumulate(stressZones.begin(), stressZones.end(), 0.0,
		[](double sum, const SensorReading& r)
		{
			return sum + r.temperature;
		}); // Використання алгоритму accumulate для обчислення суми температур зчитувань, що відповідають умовам

	return sum / stressZones.size(); // Повернення середнього значення температури, що відповідає умовам
}

int countOfHourStress(const std::vector<SensorReading>& reading) /* Прототип функції для підрахунку кількості годин,
коли рослини знаходяться в стресі */
{
	std::vector<SensorReading> criticalReadings;

	criticalReadings = filter(reading); // Використання функції filter для отримання зчитувань, що відповідають умовам стресу

	std::vector<int> stressHours;

	std::transform(criticalReadings.begin(), criticalReadings.end(),
		std::back_inserter(stressHours), [](const SensorReading& r)
		{
			return r.hour;
		}); // Використання алгоритму transform для отримання вектора годин, коли рослини знаходяться в стресі

	if (stressHours.empty()) // Перевірка на випадок, якщо немає зчитувань, що відповідають умовам стресу
	{
		return 0;
	}

	std::sort(stressHours.begin(), stressHours.end()); // Сортування вектора для подальшого видалення дублікатів 

	auto last = std::unique(stressHours.begin(), stressHours.end()); // Використання алгоритму unique для виизначення дублікатів вектора 

	stressHours.erase(last, stressHours.end()); // Видалення зайвих елементів з вектора 

	return stressHours.size(); /* Повернення кількості годин, коли рослини знаходяться в стресі,
	що відповідає кількості унікальних годин у векторі stressHours */
}

double calculateAVG_VPD(const std::vector<SensorReading>& reading) // Визначення функції для обчислення середнього значення VPD
{
	if (reading.empty()) // Перевірка на випадок, якщо вектор зчитувань порожній
	{
		return 0.0;
	}

	double sum = std::accumulate(reading.begin(), reading.end(), 0.0,
		[](double sum, const SensorReading& r)
		{
			return sum + calculateVPD(r.temperature, r.humidity);
		}); /* Використання алгоритму accumulate для обчислення суми VPD для всіх зчитувань,
	використовуючи функцію calculateVPD для обчислення VPD для кожного зчитування */

	return sum / reading.size(); // Повернення середнього значення VPD
}
