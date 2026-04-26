#include "Task_Three.h"                           // підключаємо заголовний файл з оголошеннями функцій

// функція нормалізації показників до діапазону [0, 1]
double normalize(double x, double min, double max)
{
	return (x - min) / (max - min);               // математична формула приведення значення x до діапазону
}

// функція перевірки порогового значення
double applyThreshold(double x, double threshold)
{
	return (x > threshold) ? 1.0 : x;             // тернарний оператор для перевірки порогового значення
}

// функція-композитор, що будує нову функцію f(g(x)) з двох існуючих
std::function <double(double)> compose(const std::function <double(double)>& f, const std::function<double(double)>& g)
{
	return [f, g](double x) {return f(g(x)); };   // повертаємо лямбда-вираз
}
