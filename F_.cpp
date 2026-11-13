//
// Created by Timana on 12/11/2026.
//
// ============================================================
// F (otra version) - ciclo construido vertice a vertice
// Algoritmos del PDF usados:
//  * NO es un DFS recursivo: viable() es un BFS de alcanzabilidad
//    (el PDF dice "para ¿se puede llegar?, cualquiera de DFS o BFS").
//  * Idea de "vertices alcanzables desde s" (que calcula DFS) usada como prueba
//    de que se puede cerrar el ciclo.
//  * Cola (BFS) en lugar de pila (DFS) -> orden por capas.
// Costo: se llama a viable() O(n) veces por cada s, cada una O(n+m): mas lento que
// el DFS de Alg. 14 (O(n+m)). Se deja por referencia.
// ============================================================
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<vector<bool>> ady;    // matriz de adyacencia: consulta de arista en O(1)
vector<bool> usada;

// Recorrido tipo BFS desde w por vertices no usados: decide si se puede
// volver a s (cerrar el ciclo) sin pisar el camino ya armado.
bool viable(int w, int s, bool exigir_distinto) {
    vector<bool> vis(n + 1, false);          // "visitado" (nunca se desmarca)
    queue<int> q;
    vis[w] = true;
    q.push(w);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        // si x es vecino de s se puede cerrar (exigir_distinto evita el "ciclo" s-w-s de 2 vertices)
        if (ady[x][s] && (x != w || !exigir_distinto)) return true;
        for (int y : graph[x]) {
            if (!vis[y] && !usada[y]) {
                vis[y] = true;
                q.push(y);
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    graph.assign(n + 1, vector<int>());
    ady.assign(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        ady[u][v] = ady[v][u] = true;
    }
    for (int i = 1; i <= n; i++) sort(graph[i].begin(), graph[i].end());   // vecinos en orden

    // Se prueba cada vertice s como inicio (como Alg. 2 Recorrer)
    for (int s = 1; s <= n; s++) {
        usada.assign(n + 1, false);
        usada[s] = true;
        vector<int> camino = {s};
        bool ok = true;

        while (true) {
            int ultimo = camino.back();
            if (camino.size() >= 3 && ady[ultimo][s]) break;   // se cerro el ciclo (>= 3 vertices)

            int elegido = -1;
            for (int w : graph[ultimo]) {      // vecinos en orden: busca el menor lexicograficamente
                if (usada[w]) continue;
                if (viable(w, s, camino.size() == 1)) {
                    elegido = w;
                    break;
                }
            }
            if (elegido == -1) { ok = false; break; }
            camino.push_back(elegido);
            usada[elegido] = true;             // marcado permanente, como DFS
        }

        if (ok) {
            cout << "YES\n" << camino.size() << "\n";
            for (int v : camino) cout << v << " ";
            cout << "\n";
            return 0;
        }
    }
    cout << "NO\n";
}
