//
// Created by Dayron Cueva on 13/11/2026.
//
#include <vector>
#include <limits>
using namespace std;

void dijkstra_denso(int s, int n, const std::vector<std::vector<std::pair<int, int>>>& adj, std::vector<int>& dist) {
    dist = std::vector<int>(n, std::numeric_limits<int>::max());
    std::vector<bool> listo(n, false);
    dist[s] = 0;

    for (int i = 0; i < n; ++i) {
        int u = -1;

        // VARIACIÓN: Búsqueda lineal pura. En grafos dispersos esto es ineficiente,
        // pero en grafos súper densos es más rápido que mantener el Heap.
        for (int v = 0; v < n; ++v) {
            if (!listo[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        if (dist[u] == std::numeric_limits<int>::max()) break;
        listo[u] = true;

        for (size_t j = 0; j < adj[u].size(); ++j) {
            int v = adj[u][j].first;
            int w = adj[u][j].second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
}