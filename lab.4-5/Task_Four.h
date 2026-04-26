#pragma once

// Підключення заголовочних файлів
#include "Task_Two.h"
#include "Task_One.h"

#include <vector> // Підключення бібліотеки для роботи з векторами
#include <numeric> // Підключення бібліотеки для використання алгоритму accumulate
#include <algorithm> // Підключення бібліотеки для використання алгоритму count_if
#include <iterator> // Підключення бібліотеки для використання ітераторів

double calculateAVGTemp(const std::vector<SensorReading>& reading); // Прототип функції для обчислення середнього значення температури

int countOfHourStress(const std::vector<SensorReading>& reading); /* Прототип функції для підрахунку кількості годин,
коли рослини знаходяться в стресі */

double calculateAVG_VPD(const std::vector<SensorReading>& reading); // Прототип функції для обчислення середнього значення VPD
