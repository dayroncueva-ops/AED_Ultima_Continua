#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e18; // Un valor lo suficientemente grande para representar infinito

int main() {
    // Optimización de la entrada/salida
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Lista de adyacencia: adj[u] contendrá pares {v, w}
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Grafo bidireccional
    }

    // dist[i][0] guarda la distancia mínima a la ciudad i
    // dist[i][1] guarda la segunda distancia mínima estricta a la ciudad i
    vector<vector<long long>> dist(n + 1, vector<long long>(2, INF));
    
    // Cola de prioridad que guarda pares {distancia, nodo} (Menor distancia primero)
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    // Empezamos en la ciudad 1
    dist[1][0] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // Si la distancia que sacamos es mayor a la segunda mejor, no sirve para optimizar nada.
        if (d > dist[u][1]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            long long w = edge.second;
            long long d2 = d + w;

            // Encontramos un nuevo camino más corto principal
            if (d2 < dist[v][0]) {
                dist[v][1] = dist[v][0]; // El más corto viejo ahora es el segundo más corto
                dist[v][0] = d2;
                pq.push({dist[v][0], v});
                // Si había una distancia válida previa, la metemos a la cola
                if (dist[v][1] != INF) {
                    pq.push({dist[v][1], v});
                }
            } 
            // Encontramos un nuevo segundo mejor camino estricto
            else if (d2 > dist[v][0] && d2 < dist[v][1]) {
                dist[v][1] = d2;
                pq.push({dist[v][1], v});
            }
        }
    }

    // Si la segunda mejor distancia al destino nunca se actualizó, es imposible llegar
    if (dist[n][1] == INF) {
        cout << -1 << "\n";
    } else {
        cout << dist[n][1] << "\n";
    }

    return 0;
}
