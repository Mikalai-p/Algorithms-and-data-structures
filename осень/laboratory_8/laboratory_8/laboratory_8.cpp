#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

struct Item {
    string name;
    int weight;
    int value;
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int capacity;
    cout << "Введите вместимость рюкзака: ";
    cin >> capacity;

    int n;
    cout << "Введите количество предметов: ";
    cin >> n;

    vector<Item> items(n);
    for (int i = 0; i < n; ++i) {
        cout << "Введите название, вес и стоимость предмета " << i + 1 << ": ";
        cin >> items[i].name >> items[i].weight >> items[i].value;
    }

    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w],
                    dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int maxValue = dp[n][capacity];
    cout << "Максимальная стоимость: " << maxValue << endl;

    vector<Item> selectedItems;
    int w = capacity;
    for (int i = n; i > 0 && maxValue > 0; --i) {
        if (maxValue != dp[i - 1][w]) {
            selectedItems.push_back(items[i - 1]);
            maxValue -= items[i - 1].value;
            w -= items[i - 1].weight;
        }
    }

    cout << "Предметы в рюкзаке:" << endl;
    for (const auto& item : selectedItems) {
        cout << item.name << " (Вес: " << item.weight << ", Стоимость: " << item.value << ")" << endl;
    }

    return 0;
}