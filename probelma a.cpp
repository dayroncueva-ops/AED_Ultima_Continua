//
// Created by Timana on 13/11/2026.
//
// ============================================================
// A - Ruta hasta el empleado
// Algoritmos del PDF usados:
//  * Alg. 8 (DFS-Iterativo con pares (vertice, proximo vecino)) -> recorrido()
//    (como en B y E: evita el stack overflow con n hasta 2*10^5)
//  * Reconstruccion del camino subiendo por padre[] (como en D)
// Como es un ARBOL, el camino de 1 a t es unico: DFS sirve (no hace falta BFS).
// ============================================================
#include <iostream>
#include <vector>
using namespace std;
#include <stack>
#include <list>

// Alg. 8 - DFS-Iterativo(s): la pila guarda pares (u, i) = (vertice, proximo vecino)
void recorrido(vector<vector<long long>>& graph, vector<long long>& visit, vector<long long>& padre) {
    stack<pair<long long, long long>> q;
    visit[1] = true;                          // se marca la raiz (equivale a tin[s] <- t)
    q.push({1, 0});                           // Push(P,(s,0))
    while (!q.empty()) {                      // mientras P no esta vacia
        pair<long long, long long> p = q.top();       // (u,i) <- Top(P)
        if (p.second < graph[p.first].size()) {       // si i < |adj[u]|
            q.pop();
            q.push({p.first, p.second + 1});          // Pop(P), Push(P,(u,i+1))
            long long v = graph[p.first][p.second];   // v <- adj[u][i]
            if (!visit[v]) {                          // si v no esta visitado
                visit[v] = true;                      // se marca y NUNCA se desmarca
                padre[v] = p.first;                   // padre[v] <- u
                q.push({v, 0});                       // Push(P,(v,0)): se baja a v
            }
        }
        else {
            q.pop();                                  // u termino: Pop(P)
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, t;
    cin >> n >> t;

    vector<vector<long long>> graph(n+1);
    for (long long i = 0; i < n-1; i++) {     // n-1 relaciones: es un arbol
        long long u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);                // no dirigido
    }

    vector<long long> visit(n+1, false);
    vector<long long> padre(n+1, -1);         // -1 = sin padre (la raiz)

    recorrido(graph, visit, padre);           // un solo DFS desde el director (1)

    // Reconstruir el camino: se sube por padre[] desde t hasta la raiz (como en D)
    list<long long> lista;
    long long actual = t;
    while (actual != -1) {
        lista.push_front(actual);             // push_front deja el camino en orden 1 -> t
        actual = padre[actual];
    }

    cout << lista.size() << "\n";             // k = cantidad de empleados del camino
    while (!lista.empty()) {
        cout << lista.front() << " ";
        lista.pop_front();
    }
    cout << "\n";
}