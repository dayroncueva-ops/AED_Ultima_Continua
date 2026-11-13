// ============================================================
// D - Ruta minima
// Algoritmos del PDF usados:
//  * Alg. 1 (DFS) recursivo con padre[]  -> dfs()
//  * Reconstruccion del camino subiendo por padre[] (como en "Recuperar el ciclo")
// ADVERTENCIA (PDF Semana 13, "¿Los caminos del arbol DFS son minimos?" -> NO):
// DFS encuentra UN camino, no el mas corto. Si el enunciado pide el camino de
// MENOS aristas, hace falta BFS. Lo que si hace tu codigo: como ordenas los
// vecinos, devuelve el camino lexicograficamente menor entre los que DFS halla.
// ============================================================
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#include <list>

// Alg. 1 - DFS(u): visita, y baja al primer vecino no visitado
void dfs(vector<vector<long long> > &graph, long long u, vector<long long>& visit, vector<long long>& padre) {
    for (long long i = 0; i < graph[u].size(); i++) {      // para cada v en adj[u]
        if (!visit[graph[u][i]]) {                          // si no visitado
            visit[graph[u][i]] = true;                      // se marca y NUNCA se desmarca
            padre[graph[u][i]] = u;                         // padre[v] <- u
            dfs(graph, graph[u][i], visit, padre);          // DFS(v)
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;
    vector<vector<long long>> graph(n+1);
    for (int i = 0; i < m; i++) {
        long long a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);       // no dirigido
    }

    for (long long i = 0; i < graph.size(); i++) {
        sort(graph[i].begin(), graph[i].end());   // orden de vecinos fijo, como pide DFS "en orden"
    }
    vector<long long> visit(n+1, false);
    vector<long long> padre(n+1, -1);

    list<long long> lista;
    long long u, v;
    cin >> u >> v;

    visit[u] = true;                 // se marca la raiz (equivale a tin[s] <- t)

    dfs(graph, u, visit, padre);     // un DFS desde u: visita la componente de u
    if (visit[v]) {                  // "¿alcanzable?" = visitado[v] al terminar DFS(u)
        long long actual = v;
        while ( actual != -1) {      // se sube por padre[] desde v hasta la raiz
            lista.push_front(actual);
            actual = padre[actual];
        }
        while (!lista.empty()) {
            cout << lista.front() << " ";
            lista.pop_front();
        }
    }
    else {
        cout << "no solution";
    }
    // Recursion hasta n llamadas: con n grande hay riesgo de stack overflow (Alg. 8 lo evita).
}
