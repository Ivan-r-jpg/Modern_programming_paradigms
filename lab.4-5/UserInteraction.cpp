#include "UserInteraction.h"

// функція для безпечного введення цілих чисел з перевіркою на допустимий діапазон від minVal до maxVal
int inputProcessing(int minVal, int maxVal, std::string text)
{
	std::string inputStr;                         // змінна для зчитування сирого тексту з консолі
	int val;                                      // змінна для збереження конвертованого цілого числа

	std::cout << text;                            // виводимо запрошення на введення

	while (true)                                  // нескінченний цикл, що триває доки не буде введено коректне значення
	{
		std::getline(std::cin, inputStr);         // зчитуємо весь введений рядок

		try                                       // блок обробки виняткових ситуацій
		{
			size_t pos;                           // змінна для збереження індексу символу, на якому зупинилась конвертація

			val = std::stoi(inputStr, &pos);      // намагаємось перетворити рядок у число

			if (pos < inputStr.length())          // якщо після числа в рядку є ще якісь символи
			{
				throw std::invalid_argument("");  // генеруємо помилку некоректного аргументу
			}
			if (val < minVal)                     // якщо введене число менше за дозволений мінімум
			{
				throw std::logic_error("\nError! Minimum allowed value: " + std::to_string(minVal) + "\nTry again: ");
			}
			if (val > maxVal)                     // якщо введене число більше за дозволений максимум
			{
				throw std::logic_error("\nError! Maximum allowed value: " + std::to_string(maxVal) + "\nTry again: ");
			}

			return val;                           // якщо всі перевірки пройдено, повертаємо коректне число
			break;                                // завершуємо цикл
		}
		catch (const std::invalid_argument)       // перехоплюємо помилку, якщо ввели літери замість цифр
		{
			// виводимо повідомлення про помилку
			std::cerr << "\nInput error! You must enter a whole number\nTry again: ";
		}
		catch (const std::logic_error& e)         // перехоплюємо помилки виходу за межі діапазону
		{
			std::cerr << e.what();                // виводимо текст згенерованої помилки
		}
		catch (const std::out_of_range)           // перехоплюємо помилку, якщо число занадто велике для типу int
		{
			// виводимо повідомлення про помилку
			std::cerr << "\nError! Int type size exceeded\nTry again: ";
		}
	}
}

// функція для генерації заданої кількості випадкових показників сенсорів
std::vector <SensorReading> generateRandomReadings(int count)
{
	std::vector<SensorReading> reading;                          // створюємо порожній вектор для результатів
	reading.reserve(count);                                      // резервуємо пам'ять

	std::random_device rd;                                       // отримуємо випадкове число
	std::mt19937 gen(rd());                                      // ініціалізуємо генератор випадкових чисел

	// налаштовуємо діапазони для генерації рівномірно розподілених випадкових чисел
	std::uniform_int_distribution<int> hourDist(0, 23);          // години від 0 до 23
	std::uniform_real_distribution<double> tempDist(10.0, 45.0); // температура від 10.0 до 45.0
	std::uniform_real_distribution<double> humDist(20.0, 95.0);  // вологість від 20.0 до 95.0

	int currentZoneId = 1;                                       // лічильник для зон

	// використовуємо алгоритм std::generate_n для заповнення вектора
	std::generate_n(std::back_inserter(reading), count, [&]()    
		{
			SensorReading r;                                     // створюємо тимчасову структуру для одного сенсора

			r.hour = hourDist(gen);                              // генеруємо випадкову годину
			r.zoneId = currentZoneId++;                          // присвоюємо ID зони і збільшуємо лічильник для наступної
			r.temperature = tempDist(gen);                       // генеруємо випадкову температуру
			r.humidity = humDist(gen);                           // генеруємо випадкову вологість

			return r;                                            // повертаємо створену структуру, яка додасться у вектор reading
		}
	);

	return reading;                                              // повертаємо готовий масив випадкових даних
}

void printInsructions() // Визначення функції для виведення інструкцій користувачу
{
	std::cout << "\nGREENHOUSE DSS MENU:\n\n" <<
		"1 - Show raw sensor readings\n" <<
		"2 - Transform readings (C to F, VPD)\n" <<
		"3 - Filter critical anomalies\n" <<
		"4 - Run normalization pipeline\n" <<
		"5 - Show greenhouse analytics (Avg Temp, AVG VPD)\n" <<
		"6 - Generate DSS recommendations\n" <<
		"7 - Generate new random data\n" <<
		"0 - Exit\n" << std::endl;
}

void chooseOne(const std::vector<SensorReading>& reading) // Визначення функції для обробки вибору 1
{
	std::cout << std::fixed << std::setprecision(2); // Встановлення формату виведення числа з двома знаками після коми

	std::cout << "\n--- Raw sensor readings ---\n";

	std::for_each(reading.begin(), reading.end(), [](const SensorReading& r)
		{
			std::cout << "\nArea #" << r.zoneId
				<< ":\n   Temperature: " << r.temperature
				<< "C\n   Humidity: " << r.humidity << "%\n";
		}); // Використання алгоритму for_each для виведення кожного зчитування на екран
}

void chooseTwo(const std::vector<SensorReading>& reading) // Визначення функції для обробки вибору 2
{
	std::vector<double> temps, resultVPD;

	temps.reserve(reading.size());
	resultVPD.reserve(reading.size());

	std::transform(reading.begin(), reading.end(), std::back_inserter(temps),
		[](const SensorReading& r)
		{
			return r.temperature;
		}); // Використання алгоритму transform для отримання вектора температур 

	auto resultTemp = transformReadings(temps, celsiusToFahrenheit); /* Використання функції transformReadings для перетворення
	температур з Цельсія в Фаренгейти */

	std::cout << "\n--- Temperatures in Fahrenheit / VPD Values ---\n";

	std::transform(reading.begin(), reading.end(),
		std::back_inserter(resultVPD),
		[](const SensorReading& r)
		{
			return calculateVPD(r.temperature, r.humidity);
		}); // Використання алгоритму transform для отримання вектора VPD, обчисленого на основі температури та вологості з кожного зчитування

	int i = 0; // Ініціалізація лічильника для відстеження індексу вектора результатів

	std::for_each(reading.begin(), reading.end(),
		[&resultTemp, &resultVPD, &temps, &i](const SensorReading& r)
		{
			std::cout << "\nArea #" << r.zoneId << ":\n   Temperature: "
				<< temps[i] << "C -> " << resultTemp[i] <<
				"F\n   VPD : " << resultVPD[i] << " kPa\n";
			i++; // Збільшення лічильника після виведення кожного зчитування
		}); /* Використання алгоритму for_each для виведення кожного зчитування на екран
	разом з відповідними перетвореними значеннями температури та VPD */
}

void chooseThree(const std::vector<SensorReading>& reading) // Визначення функції для обробки вибору 3
{
	std::vector<SensorReading> filteredReadings = filter(reading); /* Використання функції filter для отримання вектора зчитувань,
	що є аномаліями */

	if (filteredReadings.empty()) // Перевірка на випадок, якщо немає зчитувань, що відповідають умовам аномалії
	{
		std::cout << "\n[ATTENTION] - No critical anomalies detected!\n";
		return; // Вихід з функції
	}

	std::cout << "\n--- Critical Anomalies Detected ---\n";

	std::for_each(filteredReadings.begin(), filteredReadings.end(),
		[](const SensorReading& r)
		{
			std::cout << "\nArea #" << r.zoneId << ":\n   Temperature: "
				<< r.temperature << "C\n   Humidity: " << r.humidity << "%\n";
		}); // Використання алгоритму for_each для виведення кожного зчитування, що є аномалією, на екран
}

void chooseFour(const std::vector<SensorReading>& readings) // Визначення функції для обробки вибору 4
{
	std::cout << std::fixed << std::setprecision(2); // Встановлення формату виведення числа з двома знаками після коми

	std::vector<double> rawTemps;

	rawTemps.reserve(readings.size());

	auto normalizeTemp = [](double t)
		{
			return normalize(t, 0.0, 50.0);
		}; // Лямбда-функція для нормалізації температури, яка використовує функцію normalize

	auto applyAlertThreshold = [](double t)
		{
			return applyThreshold(t, 0.7);
		}; // Лямбда-функція для застосування порогового значення до нормалізованої температури, яка використовує функцію applyThreshold

	auto tempPipeline = compose(applyAlertThreshold, normalizeTemp); // Компонування двох лямбда-функцій у один конвеєр для обробки температури

	std::transform(readings.begin(), readings.end(),
		std::back_inserter(rawTemps),
		[](const SensorReading& r)
		{
			return r.temperature;
		}); // Використання алгоритму transform для отримання вектора сирих температур з вектора зчитувань

	std::vector <double> result = transformReadings(rawTemps, tempPipeline); /* Використання функції transformReadings для застосування
	конвеєра обробки температури до вектора сирих температур і отримання вектора результатів */

	int i = 0;

	std::cout << "\n--- Normalization Pipeline Result ---\n\n";

	std::for_each(result.begin(), result.end(), [&rawTemps, &i](double val)
		{
			std::cout << "Temperature: " << rawTemps[i] << "C -> ";

			(val == 1.0) ? (std::cout << "[ALERT! CRITICAL!]") :
				(std::cout << "Norm (coef: " << val << ")");

			std::cout << "\n";

			i++;
		}); /* Використання алгоритму for_each для виведення кожного результату нормалізації на екран разом
	з відповідною сирою температурою та статусом залежно від значення результату */
}

void chooseFive(const std::vector<SensorReading>& readings) // Визначення функції для обробки вибору 5
{
	double AVG_TEMP = calculateAVGTemp(readings); // Використання функції calculateAVGTemp для обчислення середнього значення температури

	int stressHours = countOfHourStress(readings); /* Використання функції countOfHourStress для обчислення кількості годин,
	коли рослини знаходяться в стресі */

	double AVG_VPD = calculateAVG_VPD(readings); // Використання функції calculateAVG_VPD для обчислення середнього значення VPD

	std::cout << "\n--- Greenhouse Analytics ---\n\n";

	std::cout << "Average VPD: " << AVG_VPD << " kPa\n";

	// Виведення статусу вологості на основі середнього значення VPD
	if (AVG_VPD < 0.4)
	{
		std::cout << "[WARNING!] - Too humid\n";
	}
	else if (AVG_VPD > 1.6)
	{
		std::cout << "[WARNING!] - Too dry\n";
	}
	else if (AVG_VPD == 0)
	{
		std::cout << "[WARNING!] - VPD is zero\n";
	}
	else
	{
		std::cout << "Optimal\n";
	}

	std::cout << "\n--- Average temperature in stress zones ---\n\n";

	// Виведення статусу температури на основі середнього значення температури в зонах стресу
	if (AVG_TEMP == 0.0)
	{
		std::cout << "No stress zones detected. Everything is fine.\n";
	}
	else
	{
		std::cout << "Temperature: " << AVG_TEMP << "C\n";
	}

	std::cout << "\n--- Number of the stress hours in stress zones ---\n\n";

	// Виведення статусу годин стресу на основі кількості годин, коли рослини знаходяться в стресі
	if (stressHours == 0)
	{
		std::cout << "No stress zones detected. Everything is fine.\n";
	}
	else
	{
		std::cout << "Stress hours: " << stressHours << "\n";
	}
}

void chooseSix(const std::vector<SensorReading>& readings) // Визначення функції для обробки вибору 6
{
	std::vector <std::string> recommendations;

	recommendations.reserve(readings.size());

	std::transform(readings.begin(), readings.end(),
		std::back_inserter(recommendations),
		[](const SensorReading& r)
		{
			return generateRecommendation(r);
		}); /* Використання алгоритму transform для отримання вектора рекомендацій,
	згенерованих на основі кожного зчитування за допомогою функції generateRecommendation */

	std::for_each(recommendations.begin(), recommendations.end(),
		[](const std::string& m)
		{
			std::cout << "\n" << m;
		}
	); // Використання алгоритму for_each для виведення кожної рекомендації на екран

	std::cout << std::endl;
}

std::vector<SensorReading> chooseSeven(const std::vector<SensorReading>& readings) // Визначення функції для обробки вибору 7
{
	std::vector<SensorReading> newReadings;

	newReadings = generateRandomReadings(readings.size()); /* Використання функції generateRandomReadings для генерації нового вектора
	зчитувань зі старою кількістю елементів */

	std::cout << "New random data generated successfully!\n";

	return newReadings; // Повернення нового вектора зчитувань для заміни старого вектора в головній функції
}