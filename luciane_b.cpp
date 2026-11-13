//
// Created by Dayron Cueva on 13/11/2026.
//
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e18; // 10^18 es seguro para evitar desbordamientos y superar el camino más largo posible

// Función Dijkstra que recibe el número de nodos y el grafo
vector<long long> dijkstra(int n, const vector<vector<pair<int, long long>>>& adj) {
    vector<long long> dist(n + 1, INF);
    // Min-Heap: almacena {distancia_acumulada, nodo_actual}
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // Descartar si encontramos un camino más corto previamente procesado
        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            long long w = edge.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    // Optimización rápida de I/O
    cin.tie(0)->sync_with_stdio(false);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Grafo original y grafo invertido
    vector<vector<pair<int, long long>>> adj(n + 1);
    vector<vector<pair<int, long long>>> rev_adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        rev_adj[v].push_back({u, w});
    }

    // Ejecutar Dijkstra en ambos grafos desde la ciudad central (1)
    vector<long long> dist_ida = dijkstra(n, adj);
    vector<long long> dist_regreso = dijkstra(n, rev_adj);

    int count = 0;
    long long total_time = 0;

    // Filtrar y sumar para las ciudades que se pueden atender ida y vuelta
    for (int i = 1; i <= n; ++i) {
        if (dist_ida[i] != INF && dist_regreso[i] != INF) {
            count++;
            total_time += dist_ida[i] + dist_regreso[i];
        }
    }

    cout << count << " " << total_time << "\n";

    return 0;
}
