//
// Created by Timana on 12/11/2026.
//
// ============================================================
// F - Lexicographically Minimum Cycle (version con DFS)
// Algoritmos del PDF usados:
//  * Alg. 14 (Ciclo en grafo NO dirigido, Ciclo(u,p)) -> hay_ciclos_aux()
//  * Alg. 2  (Recorrer) -> hay_ciclos()
//  * "Recuperar el ciclo": subir por padre desde u hasta v -> construir_camino()
// Idea: un vecino visitado que NO es el padre es una arista de retroceso y cierra un ciclo.
// ADVERTENCIA: la diapositiva dice que con aristas MULTIPLES se excluye la
// arista por la que se llego, no el padre (dos aristas {u,p} ya son un ciclo).
// Aqui se excluye el padre, asi que no sirve si hay aristas repetidas.
// Tampoco garantiza el ciclo lexicograficamente minimo: devuelve el primero que halla.
// ============================================================
#include <iostream>
#include <vector>
#include <list>
using namespace std;

// Alg. 14 - Ciclo(u, p)
bool hay_ciclos_aux(vector<vector<long long>>& graph, vector<bool>& visitados, vector<long long>& padre, long long& actual, long long&inicio, long long& final) {
    visitados[actual] = true;                       // visitado[u] <- verdadero
    for (long long i = 0; i < graph[actual].size(); i++) {   // para cada v en adj[u]
        long long v = graph[actual][i];
        if (!visitados[v]) {                        // no visitado: se baja
            padre[v]=actual;                        // padre[v] <- u
            if (hay_ciclos_aux(graph, visitados, padre, v, inicio, final)) {
                return true;                        // si Ciclo(v,u) entonces devolver verdadero
            }
        }
        else {
            if (v != padre[actual]) {               // visitado y no es el padre -> retroceso
                inicio = v;                         // v es el ancestro que cierra el ciclo
                final = actual;                     // u es el extremo bajo
                return true;
            }
        }
    }
    return false;
}

// Alg. 2 - Recorrer(G): un DFS desde cada vertice sin visitar
bool hay_ciclos(vector<vector<long long>>& graph, vector<bool>& visitados, vector<long long>& padre, long long& inicio, long long & final) {
    for (long long i = 1; i < graph.size(); i++) {
        if (!visitados[i] and hay_ciclos_aux(graph, visitados, padre, i, inicio, final)) {
            return true;
        }
    }
    return false;
}

// Recuperar el ciclo: se sube por padre desde u hasta v. Cuesta lo que mide el ciclo.
void construir_camino(vector<long long>& padres, long long inicio, long long final, list<long long>& ciclo_construido) {
    long long actual = final;
    while (actual != inicio) {
        ciclo_construido.push_back(actual);
        actual = padres[actual];
    }
    ciclo_construido.push_back(inicio);
}

int main() {

    long long n, m;
    cin >> n >> m;

    vector<vector<long long>> graph(n+1);
    for (long long i = 0; i < m; i++) {
        long long u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);       // no dirigido
    }

    vector<long long> padres(n+1, -1);
    vector<bool> visitados(n+1, false);

    long long final_ciclo = -1;
    long long inicio_ciclo = -1;

    list<long long> ciclo_construido;


    if (hay_ciclos(graph, visitados, padres,  inicio_ciclo, final_ciclo)) {
        cout << "YES\n";
        construir_camino(padres, inicio_ciclo, final_ciclo, ciclo_construido);
        cout << ciclo_construido.size() << "\n";
        while (!ciclo_construido.empty()) {
            cout << ciclo_construido.back() << " ";
            ciclo_construido.pop_back();
        }
        cout << "\n";
    }
    else {
        cout << "NO\n";
    }

}
