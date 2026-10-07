#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <memory>
#include <iomanip>

using namespace std;

class Graph {
public:
    virtual ~Graph() = default;
    virtual void addEdge(int v, int w) = 0;
    virtual vector<int> getNeighbors(int v) const = 0;
    virtual int getNumVertices() const = 0;
    virtual void printGraph(ostream& os) const = 0;

    vector<int> BFS(int startVertex) const {
        vector<int> order;          // Порядок обхода вершин
        vector<bool> visited(getNumVertices(), false); 
        queue<int> q;               // Очередь для BFS
        q.push(startVertex);        // Начинаем со стартовой вершины
        visited[startVertex] = true;

        while (!q.empty()) {
            int current = q.front(); // Берем вершину из начала очереди
            q.pop();
            order.push_back(current); // Добавляем в порядок обхода

            for (int neighbor : getNeighbors(current)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;  
                    q.push(neighbor);          
                }
            }
        }
        return order;
    }

    vector<int> DFS(int startVertex) const {
        vector<int> order;          // Порядок обхода вершин
        vector<bool> visited(getNumVertices(), false); // Отслеживание посещенных вершин
        stack<int> s;               // Стек для DFS
        s.push(startVertex);        
        visited[startVertex] = true;

        while (!s.empty()) {
            int current = s.top();  
            s.pop();
            order.push_back(current); 

            // Получаем всех соседей текущей вершины
            for (int neighbor : getNeighbors(current)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;  
                    s.push(neighbor);          
                }
            }
        }
        return order;
    }
};

// Представление списком смежности
class AdjListGraph : public Graph {
    vector<vector<int>> adjList;
public:
    AdjListGraph(int n) : adjList(n) {}

    void addEdge(int v, int w) override {
        adjList[v].push_back(w);
        adjList[w].push_back(v);
    }

    vector<int> getNeighbors(int v) const override {
        return adjList[v];
    }

    int getNumVertices() const override {
        return adjList.size();
    }

    void printGraph(ostream& os) const override {
        os << "Список смежности:\n";
        for (int i = 0; i < adjList.size(); ++i) {
            os << "Вершина " << i + 1 << ": ";
            for (int neighbor : adjList[i]) {
                os << neighbor + 1 << " ";
            }
            os << "\n";
        }
    }
};

// Представление матрицей смежности
class AdjMatrixGraph : public Graph {
    vector<vector<bool>> adjMatrix;
public:
    AdjMatrixGraph(int n) : adjMatrix(n, vector<bool>(n, false)) {}

    void addEdge(int v, int w) override {
        adjMatrix[v][w] = true;
        adjMatrix[w][v] = true;
    }

    vector<int> getNeighbors(int v) const override {
        vector<int> neighbors;
        for (int i = 0; i < getNumVertices(); ++i) {
            if (adjMatrix[v][i]) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }

    int getNumVertices() const override {
        return adjMatrix.size();
    }

    void printGraph(ostream& os) const override {
        os << "Матрица смежности:\n  ";
        for (int i = 0; i < adjMatrix.size(); ++i) {
            os << setw(2) << i + 1;
        }
        os << "\n";

        for (int i = 0; i < adjMatrix.size(); ++i) {
            os << i + 1 << " ";
            for (int j = 0; j < adjMatrix[i].size(); ++j) {
                os << setw(2) << (adjMatrix[i][j] ? "1" : "0");
            }
            os << "\n";
        }
    }
};

// Представление списком ребер
class EdgeListGraph : public Graph {
    vector<pair<int, int>> edges;
    int numVertices;
public:
    EdgeListGraph(int n) : numVertices(n) {}

    void addEdge(int v, int w) override {
        edges.emplace_back(v, w);
    }

    vector<int> getNeighbors(int v) const override {
        vector<int> neighbors;
        for (const auto& edge : edges) {
            if (edge.first == v) {
                neighbors.push_back(edge.second);
            }
            else if (edge.second == v) {
                neighbors.push_back(edge.first);
            }
        }
        return neighbors;
    }

    int getNumVertices() const override {
        return numVertices;
    }

    void printGraph(ostream& os) const override {
        os << "Список ребер:\n";
        for (const auto& edge : edges) {
            os << "(" << edge.first + 1 << ", " << edge.second + 1 << ") ";
        }
        os << "\n";
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    const int numVertices = 10;
    vector<pair<int, int>> edges = {
        {0,1}, {0,4}, {1,6}, {1,7}, {6,7},
        {7,2}, {4,5}, {5,3}, {5,8}, {3,8}, {8,9}
    };

    // Создаем графы с разными представлениями
    AdjListGraph adjListGraph(numVertices);
    AdjMatrixGraph adjMatrixGraph(numVertices);
    EdgeListGraph edgeListGraph(numVertices);

    // Добавляем ребра во все графы
    for (const auto& edge : edges) {
        adjListGraph.addEdge(edge.first, edge.second);
        adjMatrixGraph.addEdge(edge.first, edge.second);
        edgeListGraph.addEdge(edge.first, edge.second);
    }

    // Выводим представления графов
    adjListGraph.printGraph(cout);
    cout << "\n";
    adjMatrixGraph.printGraph(cout);
    cout << "\n";
    edgeListGraph.printGraph(cout);
    cout << "\n";

    // Обход из вершины 0 (вершина 1)
    cout << "BFS порядок (начиная с вершины 1): ";
    vector<int> bfsOrder = adjListGraph.BFS(0);
    for (int v : bfsOrder) {
        cout << v + 1 << " ";
    }
    cout << "\nDFS порядок (начиная с вершины 1): ";
    vector<int> dfsOrder = adjListGraph.DFS(0);
    for (int v : dfsOrder) {
        cout << v + 1 << " ";
    }
    cout << endl;

    return 0;
}