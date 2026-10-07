#include<iostream>
#include<thread>
#include<stdlib.h>

using namespace std;
using namespace chrono;

unsigned long long int fibonachi(int number) {
    if (number == 0 ) {
        cout << "Некорректный ввод, отсчет начинается с 1" << endl;
        exit(0);
    }
    if (number == 1) {
        return 1;
    }

    if (number == 2) {
        return 1;
    }
    return fibonachi(number - 1) + fibonachi(number - 2);
}
int main() {
    setlocale(LC_CTYPE, "rus");
    int a = 0, b = 1, number;
    cout << "Enter number: ";
    cin >> number;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < number; i++) {
        a = a + b;
        b = a - b;
    }
    auto end = high_resolution_clock::now();
    duration<float> time_cycle = end - start;

    auto one = high_resolution_clock::now();
    cout << "Число Фибоначчи: " << fibonachi(number) << endl;
    auto two = high_resolution_clock::now();
    duration<float> time_recursion = two - one;

    double total_seconds_cycle = time_cycle.count(); 
    int minutes_cycle = static_cast<int>(total_seconds_cycle / 60); 
    double seconds_cycle = total_seconds_cycle - minutes_cycle * 60; 

    
    double total_seconds_recursion = time_recursion.count(); 
    int minutes_recursion = static_cast<int>(total_seconds_recursion / 60); 
    double seconds_recursion = total_seconds_recursion - minutes_recursion * 60; 

    
    printf("Время цикла: %d минут %.10lf секунд\n", minutes_cycle, seconds_cycle);

    
    printf("Время рекурсии: %d минут %.10lf секунд\n", minutes_recursion, seconds_recursion);
    return 0;

}