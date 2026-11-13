//
// Created by Dayron Cueva on 12/11/2026.
//
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const long long INF = 1e18;
const int MAX = 200005;
vector<pair<int,long long>> adj[MAX];
long long distancia[MAX];
long long c[MAX];

void dijkstra(int n) {
    for (int i=1; i<=n; i++) {
        distancia[i] = INF;
    }
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> Q;
    distancia[1] = 0;
    Q.push({0, 1});
    while (!Q.empty()) {
        auto [min_acumulado, ciudad]  = Q.top();
        Q.pop();
        if (min_acumulado> distancia[ciudad]) {
            continue;
        }
        if (ciudad==n) {
            break;
        }
        long long tiempo_salida = min_acumulado;
        long long residuo = min_acumulado% c[ciudad];
        if (residuo != 0) {
            // no lleog exacto
            tiempo_salida += (c[ciudad]-residuo);
        }
        for (auto [v,minuto] : adj[ciudad]) {
            if (tiempo_salida + minuto < distancia[v]) {
                distancia[v]  = minuto + tiempo_salida;
                Q.push({distancia[v], v});
            }
        }
    }
}

int main () {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin>>c[i];
    };
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        long long w; cin >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    dijkstra(n);

    if (distancia[n]==INF) {
        cout << -1 << endl;
    }
    else {
        cout << distancia[n] << endl;
    }
    return 0;
}
