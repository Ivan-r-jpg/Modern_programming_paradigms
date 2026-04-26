#pragma once

#include <vector>                                   // підключення бібліотеки для роботи з векторами
#include <cmath>                                    // підключення бібліотеки для математичних обчислень
#include <functional>                               // підключення бібліотеки для роботи з об'єктами-функціями (std::function)
#include <algorithm>                                // підключення бібліотеки стандартних алгоритмів (std::transform)
#include <iterator>                                 // підключення бібліотеки ітераторів (std::back_inserter)

// функція для перетворення температури з Цельсія у Фаренгейт
double celsiusToFahrenheit(double c);

// функція для розрахунку дефіциту тиску пари (VPD)
double calculateVPD(double temp, double humidity);

// функція для перевірки, чи знаходиться температура в оптимальному діапазоні
bool isOptimalTemperature(double temp);

// функція вищого порядку для перетворення масиву показників за допомогою переданої функції
std::vector <double> transformReadings(const std::vector <double>& readings, const std::function<double(double)>& func);



