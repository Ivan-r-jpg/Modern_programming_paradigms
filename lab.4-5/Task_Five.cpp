#include "Task_five.h"                   // підключаємо заголовний файл з оголошеннями функцій

// функція для перетворення числового значення температури у текстовий статус
std::string classifyTemperature(double temp)
{
	std::string result;                  // змінна для збереження текстового статусу

	// розподіляємо значення температури по відповідних категоріях
	if (temp >= 35)                      // критично висока
	{
		result = "CRITICAL_HIGH";
	}
	else if (temp >= 26)                 // висока
	{
		result = "HIGH";
	}
	else if (temp >= 18)                 // оптимальна
	{
		result = "OPTIMAL";
	}
	else if (temp >= 16)                 // низька
	{
		result = "LOW";
	}
	else                                 // критично низька
	{
		result = "CRITICAL_LOW";
	}

	return result;                       // повертаємо статус
}

// функція для перетворення числового значення вологості у текстовий статус
std::string classifyHumidity(double humidity)
{
	std::string result;                  // змінна для збереження текстового статусу

	// розподіляємо значення вологості по категоріях
	if (humidity < 40)                   // занадто сухо
	{
		result = "TOO_DRY";
	}
	else if (humidity > 70)              // занадто волого
	{
		result = "TOO_WET";
	}
	else                                 // оптимальна вологість
	{
		result = "OPTIMAL";
	}

	return result;                      // повертаємо статус
}

// функція, що генерує вказівку до дії на основі статусів температури та вологості
std::string generateAlert(const std::string& tempStatus, const std::string& humidStatus)
{
	std::string result;                 // змінна для збереження рекомендації

	// перевіряємо всі можливі комбінації станів
	if (tempStatus == "OPTIMAL" && humidStatus == "OPTIMAL") // якщо все в нормі
	{
		result = "All indicators are normal";
	}
	else if ((tempStatus == "CRITICAL_HIGH" || tempStatus == "HIGH") && humidStatus == "OPTIMAL") // якщо потрібне охолодження
	{
		result = "Turn on cooling";
	}
	else if ((tempStatus == "LOW" || tempStatus == "CRITICAL_LOW") && humidStatus == "OPTIMAL") // якщо потрібен обігрів
	{
		result = "Throw firewood";
	}
	else if (humidStatus == "TOO_DRY" && tempStatus == "OPTIMAL") // якщо потрібен полив
	{
		result = "Watering";
	}
	else if (humidStatus == "TOO_WET" && tempStatus == "OPTIMAL") // якщо потрібно висушити повітря
	{
		result = "Air drying";
	}
	else if ((tempStatus == "CRITICAL_HIGH" || tempStatus == "HIGH") && humidStatus == "TOO_DRY") // якщо потрібен полив + охолодження
	{
		result = "Watering and turn on cooling";
	}
	else if ((tempStatus == "CRITICAL_HIGH" || tempStatus == "HIGH") && humidStatus == "TOO_WET") // якщо потрібне сушіння + охолодження
	{
		result = "Air drying and turn on cooling";
	}
	else if ((tempStatus == "LOW" || tempStatus == "CRITICAL_LOW") && humidStatus == "TOO_DRY") // якщо потрібен полив + обігрів
	{
		result = "Watering and throw firewood";
	}
	else if ((tempStatus == "LOW" || tempStatus == "CRITICAL_LOW") && humidStatus == "TOO_WET") // якщо потрібне сушіння + обігрів
	{
		result = "Air drying and throw firewood";
	}
	else                                                                                        // останній випадок
	{
		result = "Throw away the greenhouse";
	}

	return result;       // повертаємо вказівку до дії
}

// функція, що збирає результати попередніх функцій для створення фінальної рекомендації по зоні
std::string generateRecommendation(const SensorReading& r)
{
	std::string tempStatus = classifyTemperature(r.temperature);  // отримуємо статус температури
	std::string humidStatus = classifyHumidity(r.humidity);       // отримуємо статус вологості

	std::string message = generateAlert(tempStatus, humidStatus); // генеруємо вказівку на основі отриманих статусів

	return "Zone " + std::to_string(r.zoneId) + ": " + message;   // формуємо фінальний рядок з прив'язкою до ідентифікатора зони
}