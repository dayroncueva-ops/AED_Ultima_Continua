//
// Created by Dayron Cueva on 12/11/2026.
//
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 100005;
const long long INF = 1e18;
vector<pair<int,long long>> adj[MAX];
priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long, int> >> Q;


vector<long long> Dijkstra (int n, int r) {
    vector<long long> distancia (n, INF);
    distancia[r] = 0;
    Q.push({0,r});
    while (!Q.empty()) {
        auto [d, u] = Q.top();
        Q.pop();
        if (d>distancia[r]) { continue;}
        for (auto [v,w] : adj[u]) {
            if (distancia[u]+w < distancia[v]) {
                distancia[v] = distancia[u]+w;
                Q.push({distancia[v],v});
            }
            Q.push(make_pair(distancia[v], v));
        }
    }
    return distancia;
}

int main () {
    cin.tie(0)->sync_with_stdio(false);
    int n, m, r;
    cin >> n >> m >> r;
    for (int i=0; i<m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    for (int i = 0; i<n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }
    vector<long long> caminos_cortos = Dijkstra (n, r);
    for (long long x: caminos_cortos) {
        if (x!= INF)
            cout << x << '\n';
        else
            cout<<"INF"<<'\n';
    }
    return 0;
}
