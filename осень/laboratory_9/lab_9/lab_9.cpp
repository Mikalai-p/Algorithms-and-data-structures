#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>
#include <string>
#include <map>
#include <set>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjacencyMatrix;
    vector<string> cityNames;
    map<string, int> cityIndex;
    const int INF = 1000000; // Большое число для обозначения отсутствия пути

public:
    Graph() {
        // Инициализация графа с 8 городами России
        cityNames = {
            "Москва", "Санкт-Петербург", "Казань", "Нижний Новгород",
            "Екатеринбург", "Новосибирск", "Ростов-на-Дону", "Сочи"
        };

        for (int i = 0; i < cityNames.size(); i++) {
            cityIndex[cityNames[i]] = i;
        }

        
        adjacencyMatrix = vector<vector<int>>(8, vector<int>(8, INF));

        
        setDistance("Москва", "Санкт-Петербург", 700);
        setDistance("Москва", "Казань", 800);
        setDistance("Москва", "Нижний Новгород", 400);
        setDistance("Москва", "Ростов-на-Дону", 1100);
        setDistance("Москва", "Сочи", 1600);
        setDistance("Москва", "Екатеринбург", 1400);
        setDistance("Москва", "Новосибирск", 2800);

        
        setDistance("Санкт-Петербург", "Казань", 1500);
        setDistance("Санкт-Петербург", "Нижний Новгород", 1100);
        setDistance("Санкт-Петербург", "Москва", 720);
        setDistance("Санкт-Петербург", "Екатеринбург", 2100);

        
        setDistance("Казань", "Нижний Новгород", 400);
        setDistance("Казань", "Екатеринбург", 900);
        setDistance("Казань", "Москва", 810);
        setDistance("Казань", "Санкт-Петербург", 1520);
        setDistance("Казань", "Ростов-на-Дону", 1200);

       
        setDistance("Нижний Новгород", "Екатеринбург", 1200);
        setDistance("Нижний Новгород", "Москва", 410);
        setDistance("Нижний Новгород", "Санкт-Петербург", 1120);
        setDistance("Нижний Новгород", "Казань", 410);
        setDistance("Нижний Новгород", "Ростов-на-Дону", 1000);

        
        setDistance("Екатеринбург", "Новосибирск", 1500);
        setDistance("Екатеринбург", "Казань", 920);
        setDistance("Екатеринбург", "Москва", 1420);
        setDistance("Екатеринбург", "Нижний Новгород", 1220);
        setDistance("Екатеринбург", "Санкт-Петербург", 2120);

        
        setDistance("Новосибирск", "Ростов-на-Дону", 3000);
        setDistance("Новосибирск", "Екатеринбург", 1520);
        setDistance("Новосибирск", "Москва", 2820);

        
        setDistance("Ростов-на-Дону", "Сочи", 500);
        setDistance("Ростов-на-Дону", "Москва", 1120);
        setDistance("Ростов-на-Дону", "Нижний Новгород", 1020);
        setDistance("Ростов-на-Дону", "Казань", 1220);
        setDistance("Ростов-на-Дону", "Новосибирск", 3020);

        
        setDistance("Сочи", "Ростов-на-Дону", 510);
        setDistance("Сочи", "Москва", 1600);
        setDistance("Сочи", "Ростов-на-Дону", 510);

        
        for (int i = 0; i < cityNames.size(); i++) {
            adjacencyMatrix[i][i] = 0;
        }
    }

    void setDistance(const string& fromCity, const string& toCity, int distance) {
        int fromIdx = cityIndex[fromCity];
        int toIdx = cityIndex[toCity];
        adjacencyMatrix[fromIdx][toIdx] = distance;
    }

    int getDistance(int fromCity, int toCity) const {
        if (fromCity < 0 || fromCity >= cityNames.size() ||
            toCity < 0 || toCity >= cityNames.size()) {
            return INF;
        }
        return adjacencyMatrix[fromCity][toCity];
    }

    int getDistance(const string& fromCity, const string& toCity) const {
        if (cityIndex.find(fromCity) == cityIndex.end() ||
            cityIndex.find(toCity) == cityIndex.end()) {
            return INF;
        }
        return getDistance(cityIndex.at(fromCity), cityIndex.at(toCity));
    }

    int getCityCount() const {
        return cityNames.size();
    }

    string getCityName(int index) const {
        if (index < 0 || index >= cityNames.size()) {
            return "Unknown";
        }
        return cityNames[index];
    }

    void printGraph() const {
        cout << "Матрица смежности направленного графа:" << endl;
        cout << "Города: ";
        for (int i = 0; i < cityNames.size(); i++) {
            cout << i << ":" << cityNames[i] << " ";
        }
        cout << endl << endl;

        cout << "Из\\В ";
        for (int i = 0; i < cityNames.size(); i++) {
            cout << i << "     ";
        }
        cout << endl;

        for (int i = 0; i < cityNames.size(); i++) {
            cout << i << "   ";
            for (int j = 0; j < cityNames.size(); j++) {
                if (adjacencyMatrix[i][j] == INF) {
                    cout << "INF   ";
                }
                else {
                    printf("%-5d ", adjacencyMatrix[i][j]);
                }
            }
            cout << endl;
        }
    }

    vector<pair<int, int>> getEdges() const {
        vector<pair<int, int>> edges;
        for (int i = 0; i < cityNames.size(); i++) {
            for (int j = 0; j < cityNames.size(); j++) {
                if (adjacencyMatrix[i][j] != INF && adjacencyMatrix[i][j] > 0 && i != j) {
                    edges.push_back({ i, j });
                }
            }
        }
        return edges;
    }
};

class GeneticTSP {
private:
    Graph graph;
    int populationSize;
    int offspringCount;
    int generations;
    vector<vector<int>> population;
    double mutationRate = 0.1;

    random_device rd;
    mt19937 gen;

public:
    GeneticTSP(const Graph& g, int popSize, int offspring, int gen)
        : graph(g), populationSize(popSize), offspringCount(offspring), generations(gen), gen(rd()) {
    }

    void initializePopulation() {
        population.clear();
        vector<int> baseRoute(graph.getCityCount());
        for (int i = 0; i < graph.getCityCount(); i++) {
            baseRoute[i] = i;
        }

        for (int i = 0; i < populationSize; i++) {
            vector<int> route = baseRoute;
            shuffle(route.begin(), route.end(), gen);

            // Проверяем, что маршрут допустим (все связи существуют)
            bool valid = true;
            for (int j = 0; j < route.size() - 1; j++) {
                if (graph.getDistance(route[j], route[j + 1]) >= 1000000) {
                    valid = false;
                    break;
                }
            }
            if (valid && graph.getDistance(route.back(), route[0]) < 1000000) {
                population.push_back(route);
            }
        }


        while (population.size() < populationSize) {
            vector<int> route = baseRoute;
            shuffle(route.begin(), route.end(), gen);
            population.push_back(route);
        }
    }

    int calculateRouteLength(const vector<int>& route) {
        int length = 0;
        for (int i = 0; i < route.size() - 1; i++) {
            int dist = graph.getDistance(route[i], route[i + 1]);
            if (dist >= 1000000) {
                
                return INT_MAX;
            }
            length += dist;
        }
        // Возвращаемся в начальный город
        int dist_back = graph.getDistance(route.back(), route[0]);
        if (dist_back >= 1000000) {
            return INT_MAX;
        }
        length += dist_back;
        return length;
    }

    vector<int> tournamentSelection(int tournamentSize = 3) {
        vector<int> tournament;
        uniform_int_distribution<> dist(0, population.size() - 1);

        for (int i = 0; i < tournamentSize; i++) {
            tournament.push_back(dist(gen));
        }

        int bestIndex = tournament[0];
        int bestLength = calculateRouteLength(population[tournament[0]]);

        for (int i = 1; i < tournamentSize; i++) {
            int currentLength = calculateRouteLength(population[tournament[i]]);
            if (currentLength < bestLength) {
                bestLength = currentLength;
                bestIndex = tournament[i];
            }
        }

        return population[bestIndex];
    }

    pair<vector<int>, vector<int>> crossover(const vector<int>& parent1, const vector<int>& parent2) {
        uniform_int_distribution<> dist(1, graph.getCityCount() - 2);
        int start = dist(gen);
        int end = dist(gen);

        if (start > end) swap(start, end);

        vector<int> child1(graph.getCityCount(), -1);
        vector<int> child2(graph.getCityCount(), -1);

        for (int i = start; i <= end; i++) {
            child1[i] = parent1[i];
            child2[i] = parent2[i];
        }

        fillChild(child1, parent2, start, end);
        fillChild(child2, parent1, start, end);

        return { child1, child2 };
    }

    void fillChild(vector<int>& child, const vector<int>& parent, int start, int end) {
        int currentPos = (end + 1) % graph.getCityCount();

        for (int i = 0; i < parent.size(); i++) {
            int city = parent[(end + 1 + i) % parent.size()];
            if (find(child.begin(), child.end(), city) == child.end()) {
                child[currentPos] = city;
                currentPos = (currentPos + 1) % graph.getCityCount();
            }
        }
    }

    void mutate(vector<int>& route) {
        uniform_real_distribution<> probDist(0.0, 1.0);
        if (probDist(gen) < mutationRate) {
            uniform_int_distribution<> posDist(0, route.size() - 1);
            int pos1 = posDist(gen);
            int pos2 = posDist(gen);
            swap(route[pos1], route[pos2]);
        }
    }

    void run() {
        initializePopulation();

        for (int generation = 0; generation < generations; generation++) {
            vector<vector<int>> newPopulation = population;

            for (int i = 0; i < offspringCount / 2; i++) {
                vector<int> parent1 = tournamentSelection();
                vector<int> parent2 = tournamentSelection();

                auto children = crossover(parent1, parent2);
                mutate(children.first);
                mutate(children.second);

                newPopulation.push_back(children.first);
                newPopulation.push_back(children.second);
            }

            
            sort(newPopulation.begin(), newPopulation.end(),
                [this](const vector<int>& a, const vector<int>& b) {
                    return calculateRouteLength(a) < calculateRouteLength(b);
                });

            
            population.clear();
            for (int i = 0; i < populationSize && i < newPopulation.size(); i++) {
                population.push_back(newPopulation[i]);
            }

            printGenerationInfo(generation);
        }
    }

    void printGenerationInfo(int generation) {
        auto bestRoute = *min_element(population.begin(), population.end(),
            [this](const vector<int>& a, const vector<int>& b) {
                return calculateRouteLength(a) < calculateRouteLength(b);
            });

        int bestLength = calculateRouteLength(bestRoute);

        cout << "Популяция " << generation + 1 << ":" << endl;
        cout << "Лучший маршрут: ";
        for (int city : bestRoute) {
            cout << graph.getCityName(city) << " -> ";
        }
        cout << graph.getCityName(bestRoute[0]) << endl;
        cout << "Длина маршрута: " << (bestLength == INT_MAX ? "Недопустимый маршрут" : to_string(bestLength) + " км") << endl;
        cout << "------------------------" << endl;
    }

    void printFinalResult() {
        auto bestRoute = *min_element(population.begin(), population.end(),
            [this](const vector<int>& a, const vector<int>& b) {
                return calculateRouteLength(a) < calculateRouteLength(b);
            });

        int bestLength = calculateRouteLength(bestRoute);

        cout << "\n=== ФИНАЛЬНЫЙ РЕЗУЛЬТАТ ===" << endl;
        cout << "Оптимальный маршрут: ";
        for (int i = 0; i < bestRoute.size(); i++) {
            cout << graph.getCityName(bestRoute[i]);
            if (i < bestRoute.size() - 1) cout << " -> ";
        }
        cout << " -> " << graph.getCityName(bestRoute[0]) << endl;

        if (bestLength == INT_MAX) {
            cout << "ВНИМАНИЕ: Маршрут содержит несуществующие связи!" << endl;
        }
        else {
            cout << "Общая длина: " << bestLength << " км" << endl;

            cout << "\nДетали маршрута:" << endl;
            int total = 0;
            for (int i = 0; i < bestRoute.size(); i++) {
                int from = bestRoute[i];
                int to = bestRoute[(i + 1) % bestRoute.size()];
                int dist = graph.getDistance(from, to);
                total += dist;
                cout << graph.getCityName(from) << " -> " << graph.getCityName(to)
                    << ": " << dist << " км" << endl;
            }
            cout << "Суммарное расстояние: " << total << " км" << endl;
        }
    }
};

void printDirectedGraphVisualization() {
    cout << "\n=== ВИЗУАЛИЗАЦИЯ НАПРАВЛЕННОГО ГРАФА ===" << endl;
    cout << endl;
    cout << "                  Москва" << endl;
    cout << "                  / | \\" << endl;
    cout << "                 /  |  \\" << endl;
    cout << "                /   |   \\" << endl;
    cout << "               /    |    \\" << endl;
    cout << "              /     |     \\" << endl;
    cout << "             /      |      \\" << endl;
    cout << "            /       |       \\" << endl;
    cout << "  Санкт-Петербург   |    Ростов-на-Дону" << endl;
    cout << "           | \\      |      / |" << endl;
    cout << "           |  \\     |     /  |" << endl;
    cout << "           |   \\    |    /   |" << endl;
    cout << "           |    \\   |   /    |" << endl;
    cout << "           |     \\  |  /     |" << endl;
    cout << "           |      \\ | /      |" << endl;
    cout << "        Казань -> Екатеринбург -> Новосибирск" << endl;
    cout << "           \\       / \\       /" << endl;
    cout << "            \\     /   \\     /" << endl;
    cout << "             \\   /     \\   /" << endl;
    cout << "              \\ /       \\ /" << endl;
    cout << "      Нижний Новгород   Сочи" << endl;
    cout << endl;

    cout << "Ключевые связи (-> обозначает направление):" << endl;
    cout << "Москва -> Санкт-Петербург, Казань, Нижний Новгород, Ростов-на-Дону" << endl;
    cout << "Санкт-Петербург -> Москва, Казань, Нижний Новгород" << endl;
    cout << "Казань -> Москва, Санкт-Петербург, Нижний Новгород, Екатеринбург" << endl;
    cout << "Нижний Новгород -> Москва, Санкт-Петербург, Казань, Екатеринбург, Ростов-на-Дону" << endl;
    cout << "Екатеринбург -> Москва, Казань, Нижний Новгород, Новосибирск" << endl;
    cout << "Новосибирск -> Москва, Екатеринбург, Ростов-на-Дону" << endl;
    cout << "Ростов-на-Дону -> Москва, Нижний Новгород, Казань, Новосибирск, Сочи" << endl;
    cout << "Сочи -> Москва, Ростов-на-Дону" << endl;
}

void printGraphDetails(const Graph& graph) {
    cout << "\n=== ДЕТАЛИ ГРАФА ===" << endl;
    cout << "Направленные связи между городами:" << endl;
    cout << endl;

    auto edges = graph.getEdges();
    int count = 0;
    for (const auto& edge : edges) {
        cout << graph.getCityName(edge.first) << " -> "
            << graph.getCityName(edge.second) << ": "
            << graph.getDistance(edge.first, edge.second) << " км";
        count++;
        if (count % 2 == 0) cout << endl;
        else cout << " | ";
    }

    cout << "\nВсего направленных связей: " << edges.size() << endl;
}
int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== ГЕНЕТИЧЕСКИЙ АЛГОРИТМ ДЛЯ ЗАДАЧИ КОММИВОЯЖЕРА ===" << endl;
    cout << "              (НАПРАВЛЕННЫЙ ГРАФ - ГОРОДА РОССИИ)" << endl;

    Graph graph;
    graph.printGraph();
    printDirectedGraphVisualization();
    printGraphDetails(graph);

    int populationSize, offspringCount, generations;

    cout << "\nВведите параметры генетического алгоритма:" << endl;
    cout << "Размер начальной популяции: ";
    cin >> populationSize;
    cout << "Количество потомков при скрещивании: ";
    cin >> offspringCount;
    cout << "Количество поколений: ";
    cin >> generations;

    GeneticTSP tspSolver(graph, populationSize, offspringCount, generations);
    tspSolver.run();
    tspSolver.printFinalResult();

    return 0;
}