//
// Created by Timana on 12/11/2026.
//
// ============================================================
// G - Comprobacion del arbol
// Algoritmos del PDF usados:
//  * Alg. 5 (DFS-Pila): pila simple, se MARCA AL SACAR, un vertice puede estar
//    varias veces en la pila pero se visita una sola vez.
//  * Vecinos apilados en orden inverso -> mismo orden que el DFS recursivo.
//  * Idea de arbol: conexo (todos visitados) y sin ciclos.
// formas_de_llegar[v] cuenta cuantas veces se saca v de la pila: si es > 1,
// v se alcanzo por dos caminos distintos -> hay un ciclo -> no es arbol.
// ============================================================
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Alg. 5 - DFS-Pila(s)
void solve(vector<vector<long long>>& graph, vector<long long>& formas_de_llegar, vector<bool>& visited, long long indice) {
    stack<long long> s;
    s.push(indice);                          // Push(P,s)
    while (!s.empty()) {                     // mientras P no esta vacia
        long long v = s.top();               // u <- Top(P)
        s.pop();                             // Pop(P)
        if (visited[v]) {                    // si visitado[u] entonces continuar
            formas_de_llegar[v] = formas_de_llegar[v] + 1;   // (extra) otra vez por otro camino
            continue;
        };
        visited[v] = true;                   // visitado[u] <- verdadero (se marca al sacar)
        formas_de_llegar[v] = formas_de_llegar[v] + 1;
        for (long long i = graph[v].size() -1; i>=0; i--) {  // "en orden inverso"
            if (!visited[graph[v][i]]) {     // si no visitado[v] entonces Push(P,v)
                s.push(graph[v][i]);
            }
        }
    }
}

int main() {
    long long n, m;
    cin >> n >> m;

    vector<vector<long long>> graph(n+1);
    for (long long i = 0; i < m; i++) {
        long long u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);               // no dirigido
    }

    vector<bool> visited(n+1, false);
    vector<long long> formas_de_llegar(n+1, 0);

    solve(graph, formas_de_llegar, visited, 1);   // un solo DFS desde 1: si queda algo sin visitar, no es conexo

    for (long long i = 1; i <= n; i++) {
        // no visitado -> no es conexo; formas != 1 -> llegada por 2+ caminos -> hay ciclo
        if (!visited[i] or formas_de_llegar[i] != 1) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    // Alternativa mas simple: conexo y m == n-1.
}
