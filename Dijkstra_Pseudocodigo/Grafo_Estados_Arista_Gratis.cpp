//
// Created by Dayron Cueva on 13/11/2026.
//
#include <vector>
#include <queue>
#include <limits>

// Se usa una estructura para evitar 'std::pair' anidados pesados en la cola
struct Estado {
    int d, u, j;
    bool operator>(const Estado& otro) const {
        return d > otro.d; // Para el min-heap
    }
};

void dijkstra_gratis(int s, int t, int n, int K,
                     const std::vector<std::vector<std::pair<int, int>>>& adj) {

    // Matriz de estados: dist[nodo][aristas_gratis_usadas]
    std::vector<std::vector<int>> dist(n, std::vector<int>(K + 1, std::numeric_limits<int>::max()));

    std::priority_queue<Estado, std::vector<Estado>, std::greater<Estado>> Q;

    dist[s][0] = 0;
    Q.push({0, s, 0});

    while (!Q.empty()) {
        Estado actual = Q.top();
        Q.pop();

        int d = actual.d;
        int u = actual.u;
        int j = actual.j;

        if (d > dist[u][j]) continue;

        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            // Opción 1: Pagar el costo de la arista normalmente
            if (d + w < dist[v][j]) {
                dist[v][j] = d + w;
                Q.push({dist[v][j], v, j});
            }

            // Opción 2 (VARIACIÓN DE ESTADO): Usar el poder/pase gratis, si aún quedan
            if (j < K && d < dist[v][j + 1]) {
                dist[v][j + 1] = d; // El costo no aumenta (+0)
                Q.push({dist[v][j + 1], v, j + 1});
            }
        }
    }
}