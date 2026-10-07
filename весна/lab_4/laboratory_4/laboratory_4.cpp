#include <iostream>
#include <ctime>

using namespace std;

void random_sell(int* const sell, int N)
{
	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		sell[i] = rand() % 100;
	}
}

void sort(int* sell, int N)
{
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			if (i % 2 == 0)
			{
				if (sell[i] < sell[j])
				{
					swap(sell[i], sell[j]);
				}
			}
			else
			{
				if (sell[i] > sell[j])
				{
					swap(sell[i], sell[j]);
				}
			}
		}
	}
}

void print_sell(int* const sell, int N)
{
	for (int i = 0; i < N; i++)
	{
		cout << sell[i] << " ";
	}
}

void sum_price(int* const sell, int N, int sum)
{
	for (int i = 0; i < N; i++)
	{
		if (i % 2 == 0)
		{
			sum += sell[i];
		}
	}
	cout << "максимальная сумма чека: " << sum << endl;
}

void main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	int N;
	int sum = 0;
	cout << "Введите количество товаров(меньше 10000): "; cin >> N;
	if (N <= 10000) {
		int* sell = new int[N];
		random_sell(sell, N);
		sort(sell, N);
		print_sell(sell, N);
		cout << endl;
		sum_price(sell, N, sum);
	}
	else
	{
		cout << "Неверный ввод" << endl;
	}
}