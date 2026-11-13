//
// Created by Dayron Cueva on 13/11/2026.
//
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;
// VARIACIÓN: Si los pesos pueden sumar más de 2*10^9, cambiar 'int' a 'long long'
// en los vectores 'dist' y en los pares de la cola para evitar desbordamiento.
void dijkstra_estandar(int s, int t, int n,
                       const vector<vector<pair<int, int>>>& adj,
                       vector<int>& dist,
                       vector<int>& padre) {

    dist = vector<int>(n, std::numeric_limits<int>::max());
    padre = vector<int>(n, -1);

    priority_queue<pair<int, int>,
                        vector<pair<int, int>>,
                        greater<std::pair<int, int>>> Q;

    dist[s] = 0;
    Q.push(std::make_pair(0, s));

    while (!Q.empty()) {
        int d = Q.top().first;
        int u = Q.top().second;
        Q.pop();

        if (d > dist[u]) continue;

        // VARIACIÓN (Algoritmos 7 y 8): Si solo interesa llegar a 't', se detiene
        // la búsqueda inmediatamente cuando 't' sale de la cola.
        if (u == t) break;

        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if (d + w < dist[v]) {
                dist[v] = d + w;
                padre[v] = u;
                Q.push(std::make_pair(dist[v], v));
            }
        }
    }
}

// Algoritmos 5 y 6: Reconstruir el camino desde 's' hasta 't'
vector<int> reconstruir_camino(int s, int t, const std::vector<int>& padre, const std::vector<int>& dist) {
    if (dist[t] == std::numeric_limits<int>::max()) return {}; // "no hay camino"

    vector<int> c;
    for (int v = t; v != -1; v = padre[v]) {
        c.push_back(v);
    }
    reverse(c.begin(), c.end());

    // VARIACIÓN: Si el problema requiere imprimir el tamaño del camino en lugar
    // de los nodos, se devuelve `c.size() - 1` (cantidad de aristas).
    return c;
}