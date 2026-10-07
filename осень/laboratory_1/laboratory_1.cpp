#include <iostream>
using namespace std;

void hanoi(int n, int from, int to, int tmp) {
    if (n == 1) {
        cout << "Переместить диск 1 с " << from << " на " << to << " стержень" << endl;
    }
    else {
        hanoi(n - 1, from, tmp, to);
        cout << "Переместить диск " << n << " с " << from << " на " << to << " стержень" << endl;
        hanoi(n - 1, tmp, to, from);
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    int N, k, i;

    cout << "Введите количество дисков: ";
    cin >> N;

    cout << "Введите количество стержней: ";
    cin >> k;

    if (k != 3) {
        cout << "Программа работает только для 3 стержней." << endl;
        return 0;
    }

    cout << "Введите начальный стержень (1, 2 или 3): ";
    cin >> i;

    cout << "Введите конечный стержень (1, 2 или 3): ";
    cin >> k;

    if (i < 1 || i > 3 || k < 1 || k > 3) {
        cout << "Номер стержня должен быть от 1 до 3." << endl;
        return 0;
    }

    if (i == k) {
        cout << "Начальный и конечный стержни не должны совпадать." << endl;
        return 0;
    }

    int tmp = 6 - i - k; // Поскольку 1+2+3=6

    hanoi(N, i, k, tmp);

    return 0;
}