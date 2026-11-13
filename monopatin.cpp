
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
using namespace std;


const long long INF = 1e18;
const int MAX = 200005;
vector<pair<int, long long>> adj [MAX];
long long distancia [MAX][2];
void dijkstra (int n) {
    for (int i=1; i<=n; i++) {
        distancia[i][0] = INF;
        distancia[i][1] = INF;
    }
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long,int,int>>> Q;
    distancia[1][0] = 0;
    Q.push({0,1,0});
    while (!Q.empty()) {
        auto [d, u, par] = Q.top();
        Q.pop();
        if (d>distancia[u][par]) {continue;}
        int sig_par = 1-par;
        for (auto [v,w] : adj[u]) {
            if (distancia[u][par]+w < distancia[v][sig_par]) {
                distancia[v][sig_par] = distancia[u][par]+w;
                Q.push({distancia[v][sig_par], v, sig_par});
            }
        }
    }
}

int main () {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        long long w;
        cin>>w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    dijkstra (n);
    if (distancia[n][0]==INF) {
        cout << -1 << endl;
    }
    else {
        cout << distancia[n][0] << endl;
    }
    return 0;
}
