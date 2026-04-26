#pragma once

#include "Task_Two.h"                      // підключення заголовного файлу для доступу до структури SensorReading
#include <string>                          // підключення бібліотеки для роботи з текстовими рядками

// функція для перетворення числового значення температури у текстовий статус
std::string classifyTemperature(double temp);

// функція для перетворення числового значення вологості у текстовий статус
std::string classifyHumidity(double humidity);

// функція, що генерує вказівку до дії на основі статусів температури та вологості
std::string generateAlert(const std::string& tempStatus, const std::string& humidStatus);

// функція, що збирає результати попередніх функцій для створення фінальної рекомендації по зоні
std::string generateRecommendation(const SensorReading& r);
