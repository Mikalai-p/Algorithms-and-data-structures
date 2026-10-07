#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    int N;
    cout << "Введите количество участников: ";
    cin >> N;

    if (N <= 0 || N >= 10000) {
        cout << "Некорректное количество участников!" << endl;
        return 1;
    }

    int* results = new int[N]; 

    
    for (int i = 0; i < N; ++i) {
        results[i] = rand() % 100 + 1; 
    }

    
    cout << "Результаты участников: ";
    for (int i = 0; i < N; ++i) {
        cout << results[i] << " ";
    }
    cout << endl;

    
    sort(results, results + N, [N](int a, int b)
        { return a > b;
        });

    
    int uniqueScores[3] = { 0 }; 
    int uniqueCount = 0;       

    for (int i = 0; i < N && uniqueCount < 3; ++i) {
        if (i == 0 || results[i] != results[i - 1]) {
            uniqueScores[uniqueCount++] = results[i];
        }
    }

    
    int threshold = (uniqueCount == 3) ? uniqueScores[2] : 0;

    
    int prizeCount = 0;
    for (int i = 0; i < N; ++i) {
        if (results[i] >= threshold) {
            prizeCount++;
        }
        else {
            break;
        }
    }

    cout << "Количество призеров: " << prizeCount << endl;
    delete[] results;
    return 0;
}