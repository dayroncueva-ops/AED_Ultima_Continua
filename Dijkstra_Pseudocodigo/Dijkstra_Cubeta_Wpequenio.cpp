//
// Created by Dayron Cueva on 13/11/2026.
//
#include <vector>
#include <limits>
using namespace std;

void dijkstra_cubetas(int s, int n, int W, const std::vector<std::vector<std::pair<int, int>>>& adj, std::vector<int>& dist) {
    dist = std::vector<int>(n, std::numeric_limits<int>::max());

    // VARIACIÓN: En lugar de Heap, se usa un arreglo de listas (buckets).
    // Si W es muy grande, esto agota la memoria rápidamente.
    std::vector<std::vector<int>> cubeta(n * W + 1);

    dist[s] = 0;
    cubeta[0].push_back(s);

    for (int d = 0; d <= n * W; ++d) {
        for (size_t i = 0; i < cubeta[d].size(); ++i) {
            int u = cubeta[d][i];

            if (dist[u] != d) continue; // Filtrado de obsoletos adaptado

            for (size_t j = 0; j < adj[u].size(); ++j) {
                int v = adj[u][j].first;
                int w = adj[u][j].second;

                if (d + w < dist[v]) {
                    dist[v] = d + w;
                    cubeta[dist[v]].push_back(v);
                }
            }
        }
    }
}