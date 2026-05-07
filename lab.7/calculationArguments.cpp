#include "calculationArguments.h" // Підключення заголовочного файлу, що потрібен для реалізації функцій, що приймають участь в обчисленні формули

double calculationC(const std::vector<double>& arrZ) // Визначення функції для обчислення значення C
{
	double sum = 0;

	for (int i = 0; i < arrZ.size(); i++)
	{
		sum += arrZ[i] * std::sin(arrZ[i]);
	}

	return sum;
}

double calculationBE(const std::vector<double>& arr, std::function<double(double)> funk) // Визначення функції для обчислення значення B або E
{
	double sum = 0;

	for (int i = 0; i < arr.size(); i++)
	{
		sum += arr[i] * funk(arr[i]);
	}

	return calculationP(arr) * sum;
}

double calculationAD(const std::vector<double>& arr, std::function<double(double)> funk) // Визначення функції для обчислення значення A або D
{
	double sum = 0;

	for (int i = 0; i < arr.size(); i++)
	{
		sum += arr[i] * funk(arr[i]);
	}

	return (calculationP(arr) + calculationS(arr)) * sum;
}

double calculationF(const std::vector<double>& arrB) // Визначення функції для обчислення значення F
{
	double sum = 0;

	for (int i = 0; i < arrB.size(); i++)
	{
		sum += arrB[i] * std::fabs(arrB[i]);
	}

	return sum;
}

double calculationP(const std::vector<double>& arr) // Визначення функції для обчислення значення P
{
	double prod = 1;

	for (int i = 0; i < arr.size(); i++)
	{
		prod *= arr[i];	
	}

	return prod;
}

double calculationS(const std::vector<double>& arr) // Визначення функції для обчислення значення S
{
	double sum = 0;

	for (int i = 0; i < arr.size(); i++)
	{
		sum += arr[i];
	}

	return sum;
}

