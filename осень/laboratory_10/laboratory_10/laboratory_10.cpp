#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <random>

using namespace std;

class AntColony {
private:
    int n; 
    vector<vector<double>> distance; 
    vector<vector<double>> pheromone; 
    double alpha, beta; 
    double initialPheromone; 
    int iterations; 
    vector<int> bestTour; 
    double bestTourLength; 

public:
    AntColony(int numCities, double initPher, double a, double b, int iter)
        : n(numCities), initialPheromone(initPher), alpha(a), beta(b), iterations(iter) {
        // Инициализация матриц
        distance.resize(n, vector<double>(n, 0.0));
        pheromone.resize(n, vector<double>(n, initialPheromone));
        generateDistances();
        bestTourLength = numeric_limits<double>::max();
    }

    // Генерация случайных расстояний между городами
    void generateDistances() {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(1.0, 50.0);

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double dist = dis(gen);
                distance[i][j] = dist;
                distance[j][i] = dist;
            }
        }
    }

    int selectNextCity(int current, vector<bool>& visited) {
        vector<double> probabilities(n, 0.0);
        double sum = 0.0;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                double pheromoneLevel = pow(pheromone[current][i], alpha);
                double heuristic = pow(1.0 / distance[current][i], beta);
                probabilities[i] = pheromoneLevel * heuristic;
                sum += probabilities[i];
            }
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, sum);
        double roulette = dis(gen);
        double cumulative = 0.0;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                cumulative += probabilities[i];
                if (cumulative >= roulette) {
                    return i;
                }
            }
        }
        return -1;
    }

    vector<int> constructTour() {
        vector<bool> visited(n, false);
        vector<int> tour(n);

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, n - 1);

        tour[0] = dis(gen);
        visited[tour[0]] = true;

        for (int i = 1; i < n; ++i) {
            tour[i] = selectNextCity(tour[i - 1], visited);
            visited[tour[i]] = true;
        }
        return tour;
    }

    double calculateTourLength(const vector<int>& tour) {
        double length = 0.0;
        for (int i = 0; i < n - 1; ++i) {
            length += distance[tour[i]][tour[i + 1]];
        }
        length += distance[tour[n - 1]][tour[0]]; // Возврат в начальный город
        return length;
    }

    void updatePheromones(const vector<vector<int>>& tours, const vector<double>& tourLengths) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                pheromone[i][j] *= 0.9; // Коэффициент испарения 0.9
            }
        }

        for (size_t k = 0; k < tours.size(); ++k) {
            double contribution = 1.0 / tourLengths[k];
            for (int i = 0; i < n - 1; ++i) {
                pheromone[tours[k][i]][tours[k][i + 1]] += contribution;
                pheromone[tours[k][i + 1]][tours[k][i]] += contribution;
            }
            // Феромон для последнего ребра
            pheromone[tours[k][n - 1]][tours[k][0]] += contribution;
            pheromone[tours[k][0]][tours[k][n - 1]] += contribution;
        }
    }

    void run() {
        for (int iter = 0; iter < iterations; ++iter) {
            vector<vector<int>> tours(n);
            vector<double> tourLengths(n);

            for (int i = 0; i < n; ++i) {
                tours[i] = constructTour();
                tourLengths[i] = calculateTourLength(tours[i]);

                if (tourLengths[i] < bestTourLength) {
                    bestTourLength = tourLengths[i];
                    bestTour = tours[i];
                }
            }

            // Обновление феромонов
            updatePheromones(tours, tourLengths);

            // Вывод информации на текущей итерации
            cout << "Итерация " << iter + 1 << ":\n";
            cout << "Лучший маршрут: ";
            for (int city : bestTour) {
                cout << city << " ";
            }
            cout << "\nДлина маршрута: " << fixed << setprecision(2) << bestTourLength << "\n\n";
        }
    }

    void printDistanceMatrix() {
        cout << "Матрица расстояний:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << setw(6) << fixed << setprecision(1) << distance[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    int n, iterations;
    double initialPheromone, alpha, beta;

    cout << "Введите количество городов: ";
    cin >> n;
    cout << "Введите начальное значение феромонов: ";
    cin >> initialPheromone;
    cout << "Введите параметр alpha: ";
    cin >> alpha;
    cout << "Введите параметр beta: ";
    cin >> beta;
    cout << "Введите количество итераций: ";
    cin >> iterations;

    AntColony colony(n, initialPheromone, alpha, beta, iterations);
    colony.printDistanceMatrix();
    colony.run();

    return 0;
}