//
// Created by Timana on 13/11/2026.
//
// ============================================================
// E - Cycle Detection (grafo DIRIGIDO)
// Algoritmos del PDF usados:
//  * Alg. 16 (Ciclo-Dirigido, 3 colores) -> blanco / gris / negro
//  * Alg. 8  (DFS-Iterativo con pares (vertice, proximo vecino)) -> la pila s
//  * Alg. 2  (Recorrer) -> for sobre todos los vertices
//  * "Recuperar el ciclo": subir por padre[] (aqui ademas por la arista pe[])
// ============================================================
#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

void detectar_ciclo(vector<vector<pair<long long, long long>>>& graph, vector<string>& color, vector<long long>& padres, vector<long long>& pe,  long long& inicio, long long& final, long long& id_cierre) {
    stack<pair<long long, long long>> s;          // pila de pares (u, i) del Alg. 8
    for (long long i = 0; i < graph.size(); i++) {    // Alg. 2: para cada v en V
        if (color[i]=="blanco") {                 // se llama desde cada vertice que siga blanco
            color[i]="gris";                      // color[u] <- gris
            s.push({i, 0});                       // Push(P,(s,0))
            while (!s.empty()) {
                pair<long long, long long> p = s.top();       // (u,i) <- Top(P)
                if (p.second < graph[p.first].size()) {       // si i < |adj[u]|
                    s.pop();
                    s.push({p.first, p.second +1});           // Pop, Push(u, i+1)
                    pair<long long, long long> v = graph[p.first][p.second];   // v <- adj[u][i] (con id de arista)
                    if (color[v.first] == "blanco") {         // blanco: se baja
                        color[v.first] = "gris";
                        padres[v.first] = p.first;            // padre[v] <- u
                        pe[v.first] = v.second;               // id de la arista padre -> v
                        s.push({v.first, 0});
                    }
                    else if (color[v.first] == "gris") {      // GRIS: v sigue en la pila -> arista de
                        inicio = v.first;                     // retroceso -> hay ciclo (Alg. 16)
                        final = p.first;
                        id_cierre = v.second;                 // arista u -> v que cierra el ciclo
                        return;
                    }
                    // negro: ya termino, otro camino pero NO un ciclo (no se hace nada)
                }
                else {
                    color[p.first] = "negro";                 // u termino: color[u] <- negro
                    s.pop();
                }
            }
        }
    }
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    long long n, m;
    cin >> n >> m;

    vector<vector<pair<long long, long long>>> graph(n);

    for (long long i = 0; i < m; i++) {
        long long u, v;
        cin >> u >> v;
        graph[u].push_back({v, i});     // dirigido; se guarda el indice de la arista
    }

    vector<long long> padres(n, -1);
    vector<long long> pe(n, -1);
    vector<string> color(n, "blanco");
    long long inicio = -1;
    long long final = -1;
    long long id_cierre = -1;


    detectar_ciclo(graph, color, padres, pe, inicio, final, id_cierre);
    if (inicio == -1) {
        cout << "-1" << "\n";           // ninguna arista llego a un vertice gris: es un DAG
    }
    else {
        // Recuperar el ciclo: se sube por padre desde u (=final) hasta v (=inicio)
        vector<long long> c;
        c.push_back(id_cierre);
        long long actual = final;
        while (actual != inicio) {
            c.push_back(pe[actual]);
            actual = padres[actual];
        }
        cout << c.size() << "\n";
        for (long long i = c.size()  -1 ; i >= 0; i--) {   // se imprime al reves (de v hacia u)
            cout << c[i] << "\n";
        }
    }

}
