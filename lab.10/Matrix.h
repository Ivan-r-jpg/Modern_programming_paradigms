#pragma once
#include "UserInteraction.h"
#include <iomanip>

class Matrix
{
private:

	int rows;
	int cols;
	double** data; // Двовимірний масив для зберігання елементів матриці

public:

	Matrix() : rows(0), cols(0), data(nullptr) {} // Конструктор за замовчуванням

	Matrix(int rows, int cols) : rows(rows), cols(cols) // Конструктор з параметрами 
	{
		data = new double* [rows]; // Виділення пам'яті для рядків
		for (int i = 0; i < rows; i++) // Виділення пам'яті для стовпців і ініціалізація елементів нулями
		{
			data[i] = new double[cols] {0.0};
		}
	}

	Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) // Конструктор копіювання
	{
		// Виділення пам'яті для нової матриці і копіювання елементів з іншої матриці
		data = new double* [rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = new double[cols];
			for (int j = 0; j < cols; j++)
			{
				data[i][j] = other.data[i][j];
			}
		}
	}

	~Matrix() // Деструктор для звільнення виділеної пам'яті
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}

	Matrix& operator = (const Matrix& other) // Оператор присвоєння для копіювання матриці
	{
		if (this == &other) // Перевірка на самоприсвоєння 
		{
			return *this;
		}
		if (data != nullptr) // Звільнення пам'яті, якщо вона вже була виділена
		{
			for (int i = 0; i < rows; i++)
			{
				delete[] data[i];
			}
			delete[] data;
		}
		// Виділення пам'яті для нової матриці і копіювання елементів з іншої матриці
		rows = other.rows;
		cols = other.cols;
		data = new double* [rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = new double[cols];
			for (int j = 0; j < cols; j++)
			{
				data[i][j] = other.data[i][j];
			}
		}
		return *this;
	}

	void input() // Метод для вводу елементів матриці з обробкою помилок
	{
		std::cout << "\n[ВВЕДЕННЯ] - Введіть елементи матриці (" << rows << "x" << cols << "):\n\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i][j] = inputDouble((std::numeric_limits<double>::lowest)(), 
					(std::numeric_limits<double>::max)(), "Елемент [" + std::to_string(i + 1) + "][" + std::to_string(j + 1) + "]: ");
			}
		}
		std::cout << "\n[УВАГА] - Введення матриці успішно завершено!\n";
	}

	void print() const // Метод для виводу матриці на екран
	{
		std::cout << "\nМатриця (" << rows << "x" << cols << "):\n\n";
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << std::setw(7) << data[i][j] << "\t";
			}
			std::cout << "\n";
		}
	}

	friend std::ostream& operator << (std::ostream& out, const Matrix& matrix) // Перевантаження оператора виводу для зручного виводу матриці на екран
	{
		out << "\nМатриця (" << matrix.rows << "x" << matrix.cols << "):\n\n";
		for (int i = 0; i < matrix.rows; i++)
		{
			for (int j = 0; j < matrix.cols; j++)
			{
				out << std::setw(7) << matrix.data[i][j] << "\t";
			}
			out << "\n";
		}
		return out;
	}

	Matrix operator * (const Matrix& other) const // Перевантаження оператора множення для перемноження двох матриць
	{
		if (cols != other.rows)
		{
			throw std::invalid_argument("Матриці не можна перемножити!");
		}
		Matrix result(rows, other.cols);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < other.cols; j++)
			{
				for (int k = 0; k < cols; k++)
				{
					result.data[i][j] += data[i][k] * other.data[k][j];
				}
			}
		}
		return result;
	}
};