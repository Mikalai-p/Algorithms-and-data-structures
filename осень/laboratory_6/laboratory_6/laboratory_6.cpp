#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <iomanip>

using namespace std;


struct Node {
    char ch;
    int freq;
    Node* left, * right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};


struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};


void buildCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (!root) return;

    if (!root->left && !root->right) {
        codes[root->ch] = code;
        return;
    }

    buildCodes(root->left, code + "0", codes);
    buildCodes(root->right, code + "1", codes);
}


pair<unordered_map<char, string>, Node*> huffmanEncode(const string& text) {
    
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    
    unordered_map<char, string> codes;
    Node* root = nullptr;
    if (!pq.empty()) {
        root = pq.top();
        buildCodes(root, "", codes);
    }

    return make_pair(codes, root);
}

string huffmanDecode(const string& encodedText, Node* root) {
    if (!root) return "";

    string decodedText = "";
    Node* current = root;

    for (char bit : encodedText) {
        
        if (bit == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        
        if (current && !current->left && !current->right) {
            decodedText += current->ch;
            current = root;
        }
    }

    return decodedText;
}


void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    setlocale(LC_ALL, "rus");
    string text;
    cout << "Введите текст для кодирования: ";
    getline(cin, text);

    if (text.empty()) {
        cout << "Текст не введен!" << endl;
        return 0;
    }

    
    auto result = huffmanEncode(text);
    unordered_map<char, string> codes = result.first;
    Node* root = result.second;

    
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    
    cout << "\nТаблица встречаемости символов:" << endl;
    cout << "---------------------------------" << endl;
    cout << "| Символ | Количество | Процент |" << endl;
    cout << "---------------------------------" << endl;

    int totalChars = text.length();
    for (auto& pair : freq) {
        double percentage = (pair.second * 100.0) / totalChars;
        cout << "|" << setw(8) << pair.first << " |"
            << setw(11) << pair.second << " |"
            << setw(8) << fixed << setprecision(2) << percentage << "% |" << endl;
    }
    cout << "---------------------------------" << endl;

    
    cout << "\nТаблица кодов Хаффмана:" << endl;
    cout << "----------------------" << endl;
    cout << "| Символ | Код       |" << endl;
    cout << "----------------------" << endl;
    for (auto& pair : codes) {
        cout << "|" << setw(7) << pair.first << " |"
            << setw(10) << pair.second << " |" << endl;
    }
    cout << "----------------------" << endl;

    
    string encodedText = "";
    for (char ch : text) {
        encodedText += codes[ch];
    }

    
    cout << "\nЗакодированная последовательность:\n" << encodedText << endl;

    
    string decodedText = huffmanDecode(encodedText, root);

    
    cout << "\nДекодированная последовательность:\n" << decodedText << endl;

    
    cout << "\nСтатистика:" << endl;
    cout << "Исходный размер: " << totalChars * 8 << " бит" << endl;
    cout << "Закодированный размер: " << encodedText.length() << " бит" << endl;
    if (encodedText.length() > 0) {
        cout << "Коэффициент сжатия: " << fixed << setprecision(2)
            << (double)(totalChars * 8) / encodedText.length() << endl;
    }
    else {
        cout << "Коэффициент сжатия: 0" << endl;
    }

   
    deleteTree(root);

    return 0;
}