#include <iostream>
#include <limits>
#include <cmath> 

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    char otvet;
    unsigned long long int N;

    cout << "Введите N: \n";
    cin >> N;

    
    while (cin.fail() || N <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Некорректный ввод. Пожалуйста, введите целое положительное число: \n";
        cin >> N;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int a = 1;
    unsigned long long int low = 1, high = N, X;
    unsigned long long int count = 0;

    while (a != 2) {
        X = low + (high - low) / 2; 
        cout << "Предполагаемое число: " << X << "\n";
        cout << "1 - много \n";
        cout << "2 - мало \n";
        cout << "3 - угадал \n";
        cout << "Ваш ответ: ";
        cin >> otvet;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        
        while (cin.fail() || (otvet != '1' && otvet != '2' && otvet != '3')) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод. Пожалуйста, введите 1, 2 или 3: \n";
            cout << "Ваш ответ: ";
            cin >> otvet;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        count = count + 1;

        if (otvet == '1') {
            cout << "Шаг " << count << ": Слишком много (" << X << ")\n";
            high = X - 1; 
        }
        else if (otvet == '2') {
            cout << "Шаг " << count << ": Слишком мало (" << X << ")\n";
            low = X + 1;  
        }
        else {
            a = 2; 
            cout << "Шаг " << count << ": Я угадал число " << X << " за " << count << " попыток.\n";
        }

        
        if (low > high && otvet != '3') {
            cout << "Вы жульничаете! Невозможно угадать число.\n";
            break; 
        }
    }
    int maxSteps = ceil(log2(N));

    cout << "Максимальное количество шагов = " << maxSteps << endl;
    while (N > 0) {
        cout << N << endl;
        N = N / 2;
    }

    system("pause");
    return 0;
}