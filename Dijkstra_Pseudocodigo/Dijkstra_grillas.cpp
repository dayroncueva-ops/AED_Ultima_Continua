//
// Created by Dayron Cueva on 13/11/2026.
//
#include <vector>
#include <queue>
#include <limits>
using namespace std;

void dijkstra_grilla(int fs, int cs, int R, int C,
                     const vector<std::vector<int>>& costo,
                     vector<vector<int>>& dist) {

    dist = vector<vector<int>>(R, vector<int>(C, std::numeric_limits<int>::max()));
    dist[fs][cs] = costo[fs][cs];

    // La cola guarda: (distancia, (fila, columna))
    std::priority_queue<pair<int, std::pair<int, int>>,
                        vector<std::pair<int, pair<int, int>>>,
                        greater<std::pair<int, pair<int, int>>>> Q;

    Q.push(make_pair(dist[fs][cs], std::make_pair(fs, cs)));

    // VARIACIÓN: Si se permite movimiento en 8 direcciones (diagonales),
    // estos arreglos deben tener tamaño 8.
    int df[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!Q.empty()) {
        int d = Q.top().first;
        int f = Q.top().second.first;
        int c = Q.top().second.second;
        Q.pop();

        if (d > dist[f][c]) continue;

        for (int k = 0; k < 4; ++k) {
            int f_prime = f + df[k];
            int c_prime = c + dc[k];

            // Condición: Límites del tablero y mejora de costo
            if (f_prime >= 0 && f_prime < R && c_prime >= 0 && c_prime < C) {
                // VARIACIÓN: A veces el costo de moverse depende de la casilla actual
                // más la siguiente. Aquí se asume que cuesta lo que vale la casilla destino.
                if (d + costo[f_prime][c_prime] < dist[f_prime][c_prime]) {
                    dist[f_prime][c_prime] = d + costo[f_prime][c_prime];
                    Q.push(std::make_pair(dist[f_prime][c_prime], std::make_pair(f_prime, c_prime)));
                }
            }
        }
    }
}