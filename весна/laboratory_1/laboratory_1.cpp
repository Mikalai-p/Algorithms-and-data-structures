#include <iostream>
#include <thread>

using namespace std;
using namespace chrono;

unsigned long int fibonacci(int number)
{
    if (number == 0)
        return 0;
    if (number == 1)
        return 1;
    return fibonacci(number - 1) + fibonacci(number - 2);
}

int main()
{
    setlocale(LC_ALL, "ru");
    int number, a = 0, b = 1;
    float c = 0.8;
    cout << "Enter number: "; cin >> number;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < number; i++)
    {
        a = a + b;
        b = a - b;
    }
    auto one = high_resolution_clock::now();
    cout << "Число Фибонначи: " << fibonacci(number) << endl;
    auto two = high_resolution_clock::now();
    duration<float> boobs = two - one;
    auto end = high_resolution_clock::now();
    duration<float> duration = (end - start);
    cout << "Время цикла: " << duration.count() << " sec." << endl;
    cout << "Время рекурсии: " << boobs.count() << " sec." << endl;
    return 0;
}