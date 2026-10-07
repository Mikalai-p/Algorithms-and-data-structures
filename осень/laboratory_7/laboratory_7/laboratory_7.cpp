#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int n;
    cout << "Введите n(количество элементов): ";
    cin >> n;
    vector<int> seq(n);
    cout << "Введите последовательность: ";
    for (int i = 0; i < n; i++) {
        cin >> seq[i];
    }

    vector<int> dp(n, 1);
    vector<int> prev(n, -1);

    int maxLength = 1;
    int endIndex = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (seq[j] < seq[i]) {
                // Если находим такую же длину, но с меньшим последним элементом, обновляем
                if (dp[j] + 1 > dp[i] || (dp[j] + 1 == dp[i] && seq[j] < seq[prev[i]])) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
            }
        }
        // Обновляем максимальную длину, предпочитая последовательности с меньшими числами
        if (dp[i] > maxLength || (dp[i] == maxLength && seq[i] < seq[endIndex])) {
            maxLength = dp[i];
            endIndex = i;
        }
    }

    // Восстанавливаем подпоследовательность
    vector<int> lis;
    for (int i = endIndex; i != -1; i = prev[i]) {
        lis.push_back(seq[i]);
    }
    reverse(lis.begin(), lis.end());

    // Выводим результаты
    cout << maxLength << endl;
    for (size_t i = 0; i < lis.size(); i++) {
        if (i > 0) cout << ", ";
        cout << lis[i];
    }
    cout << endl;

    return 0;
}