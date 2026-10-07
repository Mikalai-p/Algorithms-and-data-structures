#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
#include <unordered_map>
#include <algorithm>
#include <stack>

using namespace std;

struct Vertex {
    char id;
    int distance;

    Vertex(char id, int distance) : id(id), distance(distance) {}

    bool operator>(const Vertex& other) const {
        return distance > other.distance;
    }
};

// Структура для хранения результатов алгоритма Дейкстры
struct DijkstraResult {
    unordered_map<char, int> distances;
    unordered_map<char, char> previous;
};

DijkstraResult dijkstra(const unordered_map<char, vector<pair<char, int>>>& graph, char start) {
    DijkstraResult result;
    priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

    for (const auto& node : graph) {
        result.distances[node.first] = INT_MAX;
    }
    result.distances[start] = 0;
    pq.push(Vertex(start, 0));

    while (!pq.empty()) {
        Vertex current = pq.top();
        pq.pop();

        if (current.distance > result.distances[current.id]) {
            continue;
        }

        for (const auto& neighbor : graph.at(current.id)) {
            char neighborId = neighbor.first;
            int weight = neighbor.second;
            int newDistance = current.distance + weight;

            if (newDistance < result.distances[neighborId]) {
                result.distances[neighborId] = newDistance;
                result.previous[neighborId] = current.id;
                pq.push(Vertex(neighborId, newDistance));
            }
        }
    }

    return result;
}

// Функция для восстановления пути от стартовой вершины до целевой
vector<char> getPath(const unordered_map<char, char>& previous, char target) {
    vector<char> path;
    if (previous.find(target) == previous.end()) {
        return path; // Путь не существует
    }

    char current = target;
    while (previous.find(current) != previous.end()) {
        path.push_back(current);
        current = previous.at(current);
    }
    path.push_back(current);
    reverse(path.begin(), path.end());
    return path;
}

// Функция для отображения пути в виде строки
string pathToString(const vector<char>& path) {
    string result;
    for (size_t i = 0; i < path.size(); ++i) {
        result += path[i];
        if (i < path.size() - 1) {
            result += " -> ";
        }
    }
    return result;
}

// Функция для проверки связности графа
bool isConnected(const unordered_map<char, vector<pair<char, int>>>& graph, char start) {
    DijkstraResult result = dijkstra(graph, start);
    for (const auto& d : result.distances) {
        if (d.second == INT_MAX) {
            return false;
        }
    }
    return true;
}

// Функция для визуализации графа
void visualizeGraph(const unordered_map<char, vector<pair<char, int>>>& graph) {
    cout << "\nСтруктура графа:\n";
    for (const auto& node : graph) {
        cout << node.first << " -> ";
        for (const auto& neighbor : node.second) {
            cout << neighbor.first << "(" << neighbor.second << ") ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    unordered_map<char, vector<pair<char, int>>> graph;

    graph['A'] = { {'B', 7}, {'C', 10} };
    graph['B'] = { {'A', 7}, {'G', 27}, {'F', 9} };
    graph['C'] = { {'A', 10}, {'F', 8}, {'E', 31} };
    graph['D'] = { {'I', 21}, {'E', 32}, {'H', 17} };
    graph['E'] = { {'C', 31}, {'D', 32} };
    graph['F'] = { {'B', 9}, {'C', 8}, {'H', 11} };
    graph['G'] = { {'B', 27}, {'I', 15} };
    graph['H'] = { {'F', 11}, {'I', 15}, {'D', 17} };
    graph['I'] = { {'G', 15}, {'H', 15}, {'D', 21} };

    // Визуализация графа
    visualizeGraph(graph);

    char startVertex;
    cout << "Введите стартовую вершину (A-I): ";
    cin >> startVertex;
    startVertex = toupper(startVertex);

    if (graph.find(startVertex) == graph.end()) {
        cout << "Ошибка: вершина не найдена в графе" << endl;
        return 1;
    }

    // Проверка связности графа
    if (!isConnected(graph, startVertex)) {
        cout << "Внимание: граф не является связным из вершины " << startVertex << endl;
    }

    DijkstraResult result = dijkstra(graph, startVertex);

    cout << "\nКратчайшие расстояния от вершины " << startVertex << ":" << endl;
    for (char vertex = 'A'; vertex <= 'I'; vertex++) {
        if (result.distances.find(vertex) != result.distances.end()) {
            cout << "До вершины " << vertex << ": ";
            if (result.distances[vertex] == INT_MAX) {
                cout << "недостижима";
            }
            else {
                cout << result.distances[vertex];

                
                vector<char> path = getPath(result.previous, vertex);
                if (!path.empty()) {
                    cout << " (путь: " << pathToString(path) << ")";
                }
            }
            cout << endl;
        }
    }

    

    return 0;
}