#include <iostream>
#include <string>
#include <stack>
using namespace std;
bool brackets(const string& operation) {
    for (char symbol : operation) {
        if (symbol == '(' || symbol == ')' || symbol == '{' || symbol == '}' || symbol == '[' || symbol == ']') {
            return true;
        }
    }
    return false;
}
bool verification(const string& operation) {
    stack<char> steck;
    for (char symbol : operation) {
        if (symbol == '(' || symbol == '{' || symbol == '[') {
            steck.push(symbol);
        }
        else if (symbol == ')' || symbol == '}' || symbol == ']') {
            if (steck.empty()) {
                return false;
            }
            if ((symbol == ')' && steck.top() != '(') || (symbol == '}' && steck.top() != '{') || (symbol == ']' && steck.top() != '[')) {
                return false;
            }
            steck.pop();
        }
    }
    return steck.empty();
}
int main() {
    setlocale(LC_CTYPE, "Russian");
    string  operation;
    cout << "Введите строку, которая может содержать цифры, буквы, знаки математических операций (+, -, *, /) и три вида скобок: (), [] и {}\n";
    cin >> operation; cout << endl;
    if (!brackets(operation)) {
        cout << "Скобки отсутствуют\n";
    }
    else if (verification(operation)) {
        cout << "Скобки расставлены верно\n";
    }
    else {
        cout << "Скобки расставлены не верно\n";
    }
    return 0;
}