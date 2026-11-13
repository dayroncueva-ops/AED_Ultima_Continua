//
// Created by Dayron Cueva on 13/11/2026.
//
#include <vector>
#include <queue>
#include <limits>
using namespace std;

void contar_caminos(int s, int n,
                    const std::vector<std::vector<std::pair<int, int>>>& adj,
                    std::vector<int>& dist,
                    std::vector<int>& cnt) {

    dist = std::vector<int>(n, std::numeric_limits<int>::max());
    cnt = std::vector<int>(n, 0);

    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> Q;

    dist[s] = 0;
    cnt[s] = 1; // Un solo camino para quedarse en el inicio
    Q.push(std::make_pair(0, s));

    while (!Q.empty()) {
        int d = Q.top().first;
        int u = Q.top().second;
        Q.pop();

        if (d > dist[u]) continue;

        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            // VARIACIÓN: En problemas competitivos, el arreglo 'cnt' puede desbordar.
            // Si piden la respuesta módulo M, se cambia a: cnt[v] = (cnt[v] + cnt[u]) % M.
            if (d + w < dist[v]) {
                dist[v] = d + w;
                cnt[v] = cnt[u]; // Se descarta lo anterior y se hereda
                Q.push(std::make_pair(dist[v], v));
            }
            else if (d + w == dist[v]) {
                cnt[v] += cnt[u]; // Empate en costo mínimo: se suman los caminos
            }
        }
    }
}