#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Optimización de la entrada/salida
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, a, b, c;
    if (!(cin >> n >> a >> b >> c)) return 0;

    if (n == 1) {
        cout << 0 << "\n";
        return 0;
    }

    // Usamos long long porque el costo puede exceder el límite de 32 bits (5*10^5 * 10^9 = 5*10^14)
    vector<long long> dp(n + 1, 0);
    dp[1] = 0;

    for (int i = 2; i <= n; ++i) {
        if (i % 2 == 0) {
            // Si es par, venimos del anterior sumando 1 o de su mitad multiplicando por 2
            dp[i] = min(dp[i - 1] + a, dp[i / 2] + c);
        } else {
            // Si es impar, venimos del anterior sumando 1 o nos pasamos por 1 al multiplicar su mitad superior y restamos 1
            dp[i] = min(dp[i - 1] + a, dp[(i + 1) / 2] + c + b);
        }
    }

    cout << dp[n] << "\n";
    return 0;
}
