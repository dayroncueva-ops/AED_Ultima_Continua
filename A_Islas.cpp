// ============================================================
// A - Islas
// Algoritmos del PDF usados:
//  * Alg. 12 (Tamaño)      -> funcion tamanio()
//  * Alg. 2  (Recorrer)    -> funcion ciclos() (ciclo principal)
//  * Alg. 10 (Etiquetar)   -> idea de "una isla nueva por cada raiz" (cant++)
// El grafo es IMPLICITO: cada casilla '#' es un vertice, unido a sus 4 vecinas.
// Las islas son las componentes conexas.
// ============================================================
#include <iostream>
#include <vector>
using namespace std;

// Desplazamientos df[k], dc[k] del Alg. 12 (derecha, izquierda, abajo, arriba)
vector<int> dx = {0, 0, 1, -1};
vector<int> dy = {1, -1, 0, 0};

// Alg. 12 - Tamaño(f, c): la casilla (i,j) es tierra y no esta visitada
long long tamanio(vector<vector<bool>>& graph, vector<vector<bool>>& visit, long long i, long long j) {

    visit[i][j] = true;          // visitado[f][c] <- verdadero (nunca se desmarca)
    long long contador = 1;      // s <- 1
    for (long long k = 0; k < 4; k++) {   // para k <- 0 a 3
        long long  nx = i + dx[k]; long long  ny = j + dy[k];   // f' <- f+df[k], c' <- c+dc[k]

        // "(f',c') esta en la grilla"
        if (nx <0 || nx >= graph.size() || ny <0 || ny >= graph[0].size()) {continue;}
        // "es tierra y no esta visitada" -> se baja (llamada recursiva)
        if (!visit[nx][ny] and graph[nx][ny] ) {
            contador = contador + tamanio(graph, visit, nx, ny);   // s <- s + Tamaño(f',c')
        }
    }
    return contador;             // devolver s
}

// Alg. 2 - Recorrer(G): lanza un DFS desde cada vertice sin visitar.
// Cada lanzamiento = una isla nueva (una etiqueta nueva por cada raiz, Alg. 10).
void ciclos(vector<vector<bool>>& graph, vector<vector<bool>>& visit, long long& tam_isl, long long& cant) {

    for (long long i = 0; i < graph.size(); i++) {
        for (long long j = 0; j < graph[i].size(); j++) {
            if (graph[i][j] and !visit[i][j]) {      // casilla de tierra sin visitar
                cant = cant+1;                        // c <- c+1: nueva componente
                long long tamanio_new = tamanio(graph, visit, i, j);  // flood fill
                if (tamanio_new > tam_isl) { tam_isl = tamanio_new; } // maximo
            }
        }
    }

}

int main() {
    long long n, m;
    cin >> n >> m;

    vector<vector<bool>> graph(n, vector<bool>(m, false));
    vector<vector<bool>> visit(n, vector<bool>(m, false));   // hace de "no visitado"

    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            char c; cin >> c;
            if (c == '#') {graph[i][j] = true;}
        }
    }

    long long tam_isl = 0;
    long long cant = 0;

    ciclos(graph, visit, tam_isl, cant);
    cout << cant << " " << tam_isl << endl;
    // OJO: la recursion puede llegar a n*m llamadas anidadas (grilla 1000x1000
    // toda de tierra) -> stack overflow. Solucion: DFS-Pila (Alg. 5) o
    // DFS-Iterativo con pares (Alg. 8), como dice la diapositiva "Una isla muy grande".
}
