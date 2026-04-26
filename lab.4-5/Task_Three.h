#pragma once

#include <functional>                      // підключення бібліотеки для роботи з об'єктами-функціями (std::function)

// функція для нормалізації значення у діапазон [0, 1]
double normalize(double x, double min, double max);

// функція що повертає 1.0 якщо більше порогу, інакше саме значення)
double applyThreshold(double x, double threshold);

// функція вищого порядку що приймає дві функції і об'єднує їх у нову функцію
std::function<double(double)> compose(const std::function<double(double)>& f, const std::function<double(double)>& g);