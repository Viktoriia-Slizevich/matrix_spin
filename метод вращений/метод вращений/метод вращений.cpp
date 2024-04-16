
#include "stdio.h"
#include <iostream>
#include "math.h"
const double PI = 3.1415926536;

bool isSimmetrial(double** coeff, int numberOfEquation) //проверка на симметричность
{
	bool result = true;
	int i, j;
	for (i = 0; i < numberOfEquation; i++) {
		for (j = i + 1; j < numberOfEquation; j++) {
			if (coeff[i][j] != coeff[j][i]) {
				result = false;
				break;
			}
		}
		if (!result) { break; }
	}
	return result;
}
int wrachenie(double** coeff, int numberOfEquation, double** solution, double precision) //метод вращений
{
	int result = 1;
	int i, j, k;
	int maxI, maxJ;
	double max, fi;
	double** matricaPoworota;
	matricaPoworota = new double* [numberOfEquation];
	for (i = 0; i < numberOfEquation; i++) 
	{
		matricaPoworota[i] = new double[numberOfEquation];
	}
	double** temp;
	temp = new double* [numberOfEquation];
	for (i = 0; i < numberOfEquation; i++) 
	{
		temp[i] = new double[numberOfEquation];
	}
	double fault = 0.0;
	for (i = 0; i < numberOfEquation; i++) 
	{
		for (j = i + 1; j < numberOfEquation; j++) 
		{
			fault = fault + coeff[i][j] * coeff[i][j];
		}
	}
	fault = sqrt(2 * fault);
	while (fault > precision) 
	{
		max = 0.0;
		for (i = 0; i < numberOfEquation; i++) {
			for (j = i + 1; j < numberOfEquation; j++) {
				if (coeff[i][j] > 0 && coeff[i][j] > max) {
					max = coeff[i][j];
					maxI = i;
					maxJ = j;
				}
				else if (coeff[i][j] < 0 && -coeff[i][j] > max) {
					max = -coeff[i][j];
					maxI = i;
					maxJ = j;
				}
			}
		}
		for (i = 0; i < numberOfEquation; i++) {
			for (j = 0; j < numberOfEquation; j++) {
				matricaPoworota[i][j] = 0;
			}
			matricaPoworota[i][i] = 1;
		}
		if (coeff[maxI][maxI] == coeff[maxJ][maxJ]) {
			matricaPoworota[maxI][maxI] = matricaPoworota[maxJ][maxJ] = matricaPoworota[maxJ][maxI] = sqrt(2.0) / 2.0;
			matricaPoworota[maxI][maxJ] = -sqrt(2.0) / 2.0;
		}
		else {
			fi = 0.5 * atan((2.0 * coeff[maxI][maxJ]) / 
				(coeff[maxI][maxI] - coeff[maxJ][maxJ]));
			matricaPoworota[maxI][maxI] = matricaPoworota[maxJ][maxJ] = cos(fi);
			matricaPoworota[maxI][maxJ] = -sin(fi);
			matricaPoworota[maxJ][maxI] = sin(fi);
		}
		for (i = 0; i < numberOfEquation; i++) {
			for (j = 0; j < numberOfEquation; j++) {
				temp[i][j] = 0.0;
			}
		}
		for (i = 0; i < numberOfEquation; i++) {
			for (j = 0; j < numberOfEquation; j++) {
				for (k = 0; k < numberOfEquation; k++) {
					temp[i][j] = temp[i][j] + matricaPoworota[k][i] * coeff[k][j];
				}
			}
		}
		for (i = 0; i < numberOfEquation; i++) {
			for (j = 0; j < numberOfEquation; j++) {
				coeff[i][j] = 0.0;
			}
		}
		for (i = 0; i < numberOfEquation; i++) {
			for (j = 0; j < numberOfEquation; j++) {
				for (k = 0; k < numberOfEquation; k++) {
					coeff[i][j] = coeff[i][j] +
						temp[i][k] * matricaPoworota[k][j];
				}
			}
		}
		fault = 0.0;
		for (i = 0; i < numberOfEquation; i++) {
			for (j = i + 1; j < numberOfEquation; j++) {
				fault = fault + coeff[i][j] * coeff[i][j];
			}
		}
		fault = sqrt(2 * fault);
		for (i = 0; i < numberOfEquation; i++) {
			for (j = 0; j < numberOfEquation; j++) {
				temp[i][j] = 0.0;
			}
		}
		for (i = 0; i < numberOfEquation; i++) {
			for (j = 0; j < numberOfEquation; j++) {
				for (k = 0; k < numberOfEquation; k++) {
					temp[i][j] = temp[i][j] + solution[i][k] * matricaPoworota[k][j];
				}
			}
		}
		for (i = 0; i < numberOfEquation; i++) {
			for (j = 0; j < numberOfEquation; j++) {
				solution[i][j] = temp[i][j];
			}
		}
		result++;
	}
	return result;
}
using namespace std;

void main()
{
	setlocale(LC_ALL, "rus");
	int i, j;
	int size;
	double** coeff, ** solution, precision;
	cout << "Введите размерность матрицы: ";
	cin >> size;
	cout << "\nВведите элементы матрицы: ";
	coeff = new double* [size];
	solution = new double* [size];
	for (i = 0; i < size; i++) {
		coeff[i] = new double[size];
		solution[i] = new double[size];
	}
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			solution[i][j] = 0;
		}
		solution[i][i] = 1;
	}
	for (i = 0; i < size; i++) {
		cout << "введите " << i + 1 << " строку: ";
		for (j = 0; j < size; j++) {
			cin >> coeff[i][j];
		}
	}
	cout << "Введите точность расчета: ";
	cin >> precision;
	if (!isSimmetrial(coeff, size)) {
		cout << "Матрица не симметричная";
	}
	else {
		int steps = wrachenie(coeff, size, solution, precision);
		cout << "Решение:\n";
		for (i = 0; i < size; i++) {
			cout << "Собственный вектор k " << i + 1 << ":\n";
			for (j = 0; j < size; j++) {
				cout << solution[j][i] << "\n";
			}
		}
		cout << "Собственные значения:\n";
		for (i = 0; i < size; i++) {
			cout << coeff[i][i] << "\n";
		}
		cout << "Общее число шагов: " << steps;
	}
	
	
}
