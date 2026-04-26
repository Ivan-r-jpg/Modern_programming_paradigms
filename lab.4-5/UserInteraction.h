#pragma once

#include <iostream>
#include <string>
#include <random>
#include <vector>
#include "UserInteraction.h"
#include <iomanip>
#include "Task_One.h"
#include "Task_Two.h"
#include "Task_Three.h"
#include "Task_Four.h"
#include "Task_Five.h"

// функція для безпечного введення цілих чисел з перевіркою на допустимий діапазон від minVal до maxVal
int inputProcessing(int minVal, int maxVal, std::string text);

// функція для генерації заданої кількості випадкових показників сенсорів
std::vector <SensorReading> generateRandomReadings(int count);

void printInsructions(); // Прототип функції для виведення інструкцій користувачу

void chooseOne(const std::vector<SensorReading>& reading); // Прототип функції для обробки вибору 1

void chooseTwo(const std::vector<SensorReading>& reading); // Прототип функції для обробки вибору 2

void chooseThree(const std::vector<SensorReading>& reading); // Прототип функції для обробки вибору 3

void chooseFour(const std::vector<SensorReading>& reading); // Прототип функції для обробки вибору 4

void chooseFive(const std::vector<SensorReading>& reading); // Прототип функції для обробки вибору 5

void chooseSix(const std::vector<SensorReading>& reading); // Прототип функції для обробки вибору 6

std::vector<SensorReading> chooseSeven(const std::vector<SensorReading>&
	reading); // Прототип функції для обробки вибору 7