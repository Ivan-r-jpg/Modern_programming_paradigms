#pragma once

#include <vector> // Підключення бібліотеки для використання векторів 
#include <cmath> // Підключення бібліотеки для використання математичних функцій
#include <functional> // Підключення бібліотеки для реалізації передачі функції як аргумента в іншу функції
#include <iostream> // Підключення бібліотеки дял використання простору імен std

double calculationC(const std::vector<double>& arrZ); // Прототип функції для обчислення значення C

double calculationBE(const std::vector<double>& arr, std::function<double(double)> funk); // Прототип функції для обчислення значення B або E

double calculationAD(const std::vector<double>& arr, std::function<double(double)> funk); // Прототип функції для обчислення значення A або D

double calculationF(const std::vector<double>& arrB); // Прототип функції для обчислення значення F

double calculationP(const std::vector<double>& arr); // Прототип функції для обчислення значення P

double calculationS(const std::vector<double>& arr); // Прототип функції для обчислення значення S

