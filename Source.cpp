#include <iostream>
#include <math.h>
#include <fstream>

#define valuea 0.3
#define valueb 0.7
#define valuel 1.0
#define valueE pow(10,19)
#define valueJ 0.0001
#define valueP pow(10,5)
#define eps pow(10,-17)

using namespace std;

double AbsoluteValue(double a)
{
	if (a > 0) return a;
	else return -a; // berjuvberijberil
} 

double functionM(double x)
{
	if (x >= 0 && x <= 0.3)
	{
		return (valueb * valueP * x) / (valueE * valueJ * valuel);
	}
	else if (x > 0.3 && x <= 1.0)
	{
		return (valuea * valueP * (valuel - x)) / (valueE * valueJ * valuel);
	}

}

double FunctionValue(double x, double step, int n)
{
	double* value1 = new double[n + 1];
	double* value2 = new double[n + 1];

	for (int i = 0; i <= n; i++)

	{
		value1[i] = 0.0;
		value2[i] = 0.0;
	}

	value1[0] = 0.0;
	value2[0] = x;

	for (int i = 1; i <= n; i++)
	{
		value1[i] = value1[i - 1] + value2[i - 1] * step; //итер. схема метода Эйлера
		value2[i] = value2[i - 1] + functionM((i - 1) * step) * step;
	}

	double value = value1[n];
	cout << "Значение функции в l при x = " << x << " := " << value << "\n";
	delete value1;
	delete value2;
	return value;
}

double FindSolution(double a, double b, double h, double e, int& check) // a - левая граница промежутка, b - правая граница промежутка, e - точность вычислений
{
	check++;

	double c = (b + a) / 2.0; // Середина отрезка
	double fa = FunctionValue(a, h, 1.0 / h), fb = FunctionValue(b, h, 1.0 / h), fc = FunctionValue(c, h, 1.0 / h);

	if (AbsoluteValue(fa) < (e + 0.0)) // Проверка на выход из функции
	{
		return a;
	}
	else
	{
		if (AbsoluteValue(fb) < (e + 0.0))

		{
			return b;
		}
		else
		{
			if (AbsoluteValue(fc) < (e + 0.0))
			{
				return c;
			}
		}
	}

	if (fa * fc < 0) // Если знаки центра и левой границы различны, то работаем с левой половиной.
	{
		return FindSolution(a, c, h, e, check);
	}
	else // Иначе работаем с правой.
	{
		return FindSolution(c, b, h, e, check);
	}

}

int main()
{
	setlocale(LC_ALL, "Russian");
	double h = 0.0;

	cout << "Введите шаг: ";
	cin >> h;

	int check = 0, count = 1;
	double left = -100.0, right = 0.0;

	while (FunctionValue(left, h, 1 / h) * FunctionValue(right, h, 1 / h) >= 0)
	{
		left -= 100.0;
	}

	cout << "\nЛевая граница:" << left << " Правая:" << right << endl;

	double solut = FindSolution(left, right, h, eps, check);

	cout << "Условие на производную в нуле: y'(0) = " << solut << "\n";
	int n = 1.0 / h;

	double* value1 = new double[n + 1];
	double* value2 = new double[n + 1];

	for (int i = 0; i <= n; i++)
	{
		value1[i] = 0.0;
		value2[i] = 0.0;
	}

	value1[0] = 0.0;
	value2[0] = solut;

	for (int i = 1; i <= n; i++)
	{
		value1[i] = value1[i - 1] + value2[i - 1] * h; //итер. схема метода Эйлера
		value2[i] = value2[i - 1] + functionM((i - 1) * h) * h;
	}

	ofstream out("function.txt");

	for (int i = 0; i <= n; i++)
	{
		out /*<<i*h <<"\t" */ << value1[i] << "\n";
	}

	std::cout << "\nЧисло итераций: " << check << "\n";

	system("pause");
	return 0;

}