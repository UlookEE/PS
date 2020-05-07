#include <bits/stdc++.h>
using namespace std;

int board[1600001][2];
int DP[1600001];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> board[i][0] >> board[i][1];
    for (int i = 1; i <= N; i++) {
        DP[i + board[i][0] - 1] = max(DP[i + board[i][0] - 1], DP[i - 1] + board[i][1]);
        DP[i] = max(DP[i], DP[i - 1]);
    }
    cout << DP[N] << '\n';
    return 0;
}