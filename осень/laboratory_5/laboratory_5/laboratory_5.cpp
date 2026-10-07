#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

// Структура для представления ребра
struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// Функция для сравнения рёбер по весу (для сортировки)
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}


class DSU {
private:
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
            else if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Алгоритм Краскала
vector<Edge> kruskalMST(vector<Edge>& edges, int n) {
    sort(edges.begin(), edges.end(), compareEdges);
    DSU dsu(n);
    vector<Edge> mst;
    for (const Edge& e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            mst.push_back(e);
        }
    }
    return mst;
}

// Алгоритм Прима
vector<Edge> primMST(vector<vector<pair<int, int>>>& graph, int n) {
    vector<bool> inMST(n, false);
    vector<Edge> mst;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    
    inMST[0] = true;
    for (const auto& neighbor : graph[0]) {
        pq.push(make_tuple(neighbor.second, 0, neighbor.first));
    }

    while (!pq.empty()) {
        int weight, u, v;
        tie(weight, u, v) = pq.top();
        pq.pop();
        if (inMST[v]) continue;
        inMST[v] = true;
        mst.push_back(Edge(u, v, weight));
        for (const auto& neighbor : graph[v]) {
            if (!inMST[neighbor.first]) {
                pq.push(make_tuple(neighbor.second, v, neighbor.first));
            }
        }
    }
    return mst;
}

int main() {
    int n = 8; 
    vector<Edge> edges = {
        {0, 1, 2}, {0, 3, 8}, {0, 4, 2},
        {1, 2, 3}, {1, 3, 10}, {1, 4, 5},
        {2, 4, 12}, {2, 7, 7},
        {3, 4, 14}, {3, 5, 3}, {3, 6, 1},
        {4, 5, 11}, {4, 7, 8},
        {5, 6, 6},
        {6, 7, 9}  
    };

    // Построение графа для алгоритма Прима
    vector<vector<pair<int, int>>> graph(n);
    for (const Edge& e : edges) {
        graph[e.u].push_back({ e.v, e.weight });
        graph[e.v].push_back({ e.u, e.weight });
    }

    // Алгоритм Краскала
    vector<Edge> mstKruskal = kruskalMST(edges, n);
    cout << "Kruskal MST Edges:\n";
    int totalWeightKruskal = 0;
    for (const Edge& e : mstKruskal) {
        cout << "V" << e.u + 1 << " - V" << e.v + 1 << " = " << e.weight << "\n";
        totalWeightKruskal += e.weight;
    }
    cout << "Total Weight: " << totalWeightKruskal << "\n\n";

    // Алгоритм Прима
    vector<Edge> mstPrim = primMST(graph, n);
    cout << "Prim MST Edges:\n";
    int totalWeightPrim = 0;
    for (const Edge& e : mstPrim) {
        cout << "V" << e.u + 1 << " - V" << e.v + 1 << " = " << e.weight << "\n";
        totalWeightPrim += e.weight;
    }
    cout << "Total Weight: " << totalWeightPrim << "\n";

    return 0;
}