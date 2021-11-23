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
		value1[i] = value1[i - 1] + value2[i - 1] * step; //èòåð. ñõåìà ìåòîäà Ýéëåðà
		value2[i] = value2[i - 1] + functionM((i - 1) * step) * step;
	}

	double value = value1[n];
	cout << "Çíà÷åíèå ôóíêöèè â l ïðè x = " << x << " := " << value << "\n";
	delete value1;
	delete value2;
	return value;
}

double FindSolution(double a, double b, double h, double e, int& check) // a - ëåâàÿ ãðàíèöà ïðîìåæóòêà, b - ïðàâàÿ ãðàíèöà ïðîìåæóòêà, e - òî÷íîñòü âû÷èñëåíèé
{
	check++;

	double c = (b + a) / 2.0; // Ñåðåäèíà îòðåçêà
	double fa = FunctionValue(a, h, 1.0 / h), fb = FunctionValue(b, h, 1.0 / h), fc = FunctionValue(c, h, 1.0 / h);

	if (AbsoluteValue(fa) < (e + 0.0)) // Ïðîâåðêà íà âûõîä èç ôóíêöèè
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

	if (fa * fc < 0) // Åñëè çíàêè öåíòðà è ëåâîé ãðàíèöû ðàçëè÷íû, òî ðàáîòàåì ñ ëåâîé ïîëîâèíîé.
	{
		return FindSolution(a, c, h, e, check);
	}
	else // Èíà÷å ðàáîòàåì ñ ïðàâîé.
	{
		return FindSolution(c, b, h, e, check);
	}

}

int main()
{
	setlocale(LC_ALL, "Russian");
	double h = 0.0;

	cout << "Ââåäèòå øàã: ";
	cin >> h;

	int check = 0, count = 1;
	double left = -100.0, right = 0.0;

	while (FunctionValue(left, h, 1 / h) * FunctionValue(right, h, 1 / h) >= 0)
	{
		left -= 100.0;
	}

	cout << "\nËåâàÿ ãðàíèöà:" << left << " Ïðàâàÿ:" << right << endl;

	double solut = FindSolution(left, right, h, eps, check);

	cout << "Óñëîâèå íà ïðîèçâîäíóþ â íóëå: y'(0) = " << solut << "\n";
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
		value1[i] = value1[i - 1] + value2[i - 1] * h; //èòåð. ñõåìà ìåòîäà Ýéëåðà
		value2[i] = value2[i - 1] + functionM((i - 1) * h) * h;
	}

	ofstream out("function.txt");

	for (int i = 0; i <= n; i++)
	{
		out /*<<i*h <<"\t" */ << value1[i] << "\n";
	}

	std::cout << "\n×èñëî èòåðàöèé: " << check << "\n";

	system("pause");
	return 0;

}
