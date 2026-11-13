// ============================================================
// B - Es mi superior
// Algoritmos del PDF usados:
//  * Alg. 8  (DFS-Iterativo con pares (vertice, proximo vecino)) -> recorrido()
//  * tin/tout (Alg. 1) e "intervalos anidados": ancestro en O(1)
// ============================================================
#include <iostream>
#include <vector>
using namespace std;
#include <stack>

// Alg. 8 - DFS-Iterativo(s): la pila guarda pares (u, i) = (vertice, proximo vecino).
// Cada par guarda lo mismo que un marco de la pila de llamadas: mismos tin/tout
// que la recursion, pero sin stack overflow.
void recorrido(vector<vector<long long>>& graph, vector<long long>& tin, vector<long long>& tout) {
    long long t = 1; tin[1] = t; t = t+1;     // tin[s] <- t, t <- t+1
    stack<pair<long long, long long>> q;
    q.push({1,0});                            // Push(P,(s,0))
    while (!q.empty()) {                      // mientras P no esta vacia
        pair<long long, long long> p = q.top();   // (u,i) <- Top(P)
        if (p.second < graph[p.first].size()) {   // si i < |adj[u]|
            q.pop();
            q.push({p.first,p.second+1});         // Pop(P), Push(P,(u,i+1))
            long long v = graph[p.first][p.second];   // v <- adj[u][i]
            if (tin[v]  == -1) {                  // tin[v] = nulo (aqui nulo = -1): no visitado
                tin[v] = t, t = t+1;              // tin[v] <- t, t <- t+1 (padre[v] no se necesita)
                q.push({v,0});                    // Push(P,(v,0)): se baja a v
            }
        }
        else {
            tout[p.first] = t, t = t+1;           // tout[u] <- t, t <- t+1: u termino
            q.pop();                              // Pop(P)
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, q;
    cin >> n >> q;
    vector<vector<long long>> graph(n+1);

    for (long long i = 0; i < n-1; i++) {     // n-1 aristas: es un arbol, una sola componente
        long long u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<long long> tin(n+1, -1);
    vector<long long> tout(n+1, -1);

    recorrido(graph, tin, tout);   // un solo DFS desde la raiz 1 (no hace falta Recorrer)

    for (long long i = 0; i < q; i++) {
        long long u, v;
        cin >> u >> v;
        // "Intervalos anidados": u es ancestro de v  <=>  tin[u] <= tin[v] y tout[v] <= tout[u]
        // Pregunta en O(1) despues de un recorrido de O(n+m).
        if (tin[u]<=tin[v] and tout[u] >= tout[v]) {cout << "SI\n";}
        else {cout << "NO\n";}
    }
}
