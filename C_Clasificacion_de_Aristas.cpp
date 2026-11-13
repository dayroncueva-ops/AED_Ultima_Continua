//
// Created by Timana on 13/11/2026.
//
// ============================================================
// C - Clasificacion de aristas
// Algoritmos del PDF usados:
//  * Alg. 27 (DFS-Clasificar) -> DFS_claisificar()
//  * Alg. 2  (Recorrer)       -> ciclo for en main()
//  * tin/tout con un reloj t que avanza al entrar y al salir
// Grafo DIRIGIDO: aparecen los 4 tipos (arbol, retroceso, avance, cruce).
// ============================================================
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

long long t = 0;   // reloj global del DFS

// Alg. 27 - DFS-Clasificar(u)
void DFS_claisificar(vector<vector<pair<long long, string>>>& graph, vector<string>& color, long long& indice, vector<long long>& tin, vector<long long>& tout,
    vector<long long>& padre, long long& ar_arbol, long long & ar_retroceso, long long & ar_cruces, long long & ar_avance) {
    color[indice] = "gris";                 // color[u] <- gris (u esta en la pila)
    tin[indice] = t; t = t+1;               // tin[u] <- t, t <- t+1
    for (long long i = 0; i < graph[indice].size(); i++) {   // para cada v en adj[u]
        long long v = graph[indice][i].first;
        if (color[v] == "blanco") {         // v no visitado -> arista de ARBOL
            graph[indice][i].second = "arbol";
            ar_arbol++;
            padre[v] = indice;              // padre[v] <- u
            DFS_claisificar(graph, color,  v, tin, tout, padre, ar_arbol, ar_retroceso, ar_cruces, ar_avance);
        }
        else if (color[v] == "gris") {      // v sigue en la pila -> RETROCESO (cierra un ciclo)
            graph[indice][i].second = "retroceso";
            ar_retroceso++;
        }
        else if (tin[indice] < tin[v]) {    // v ya termino (negro) y entro despues de u -> AVANCE
            graph[indice][i].second = "avance";
            ar_avance++;
        }
        else {                              // v ya termino y entro antes que u -> CRUCE
            graph[indice][i].second = "cruce";
            ar_cruces++;
        }
    }
    color[indice] = "negro";                // color[u] <- negro (u termino)
    tout[indice] = t; t++;                  // tout[u] <- t, t <- t+1
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    long long n, m;
    cin >> n >> m;

    vector <vector<pair<long long, string>>> graph(n+1);

    for (long long i = 0; i < m; i++) {
        long long u, v;
        cin >> u >> v;
        graph[u].push_back({v, " "});       // grafo dirigido: solo u -> v
    }

    for (long long i = 1; i <= n; i++) {
        sort(graph[i].begin(), graph[i].end());   // vecinos en orden creciente
    }
    vector <string> color(n+1, "blanco");   // blanco = no visitado
    vector <long long> tin(n+1);
    vector <long long> tout(n+1);
    vector <long long> padre(n+1);
    vector <string> tipo(n, "");            // (sin uso: el tipo se guarda en graph[..].second)

    long long ar_arbol = 0;
    long long ar_retroceso = 0;
    long long ar_avance = 0;
    long long ar_cruces = 0;


    t = 1;                                  // Alg. 2: t <- 1
    for (long long i = 1; i <= n; i++) {    // Alg. 2: para cada v en V
        if (color[i] == "blanco") {         // si no visitado -> nuevo arbol del bosque DFS
            DFS_claisificar(graph, color, i, tin, tout, padre, ar_arbol, ar_retroceso, ar_cruces, ar_avance);
        }
    }
    cout << ar_arbol << " " << ar_retroceso << " " << ar_avance << " " << ar_cruces << endl;
}
