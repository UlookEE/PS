#include <bits/stdc++.h>
using namespace std;

int arr[100][100];
int N, L;
int ans;
int used[100][100];
inline bool in_range(int x) {
    return x >= 0 && x < N;
}

void calc(int n) {
    for (int i = 1; i < N; i++) {
        if (abs(arr[i][n] - arr[i - 1][n]) > 1)
            return;

        if (arr[i][n] - arr[i - 1][n] == 1) {
            for (int j = 1; j <= L; j++) {
                if (!in_range(i - j) || arr[i - 1][n] != arr[i - j][n] || used[i - j][n])
                    return;
                used[i - j][n] = true;
            }
        } else if (arr[i][n] - arr[i - 1][n] == -1) {
            for (int j = 0; j < L; j++) {
                if (!in_range(i + j) || arr[i][n] != arr[i + j][n] || used[i + j][n])
                    return;
                used[i + j][n] = true;
            }
        }
    }
    ans++;
}

void calc2(int n) {
    for (int i = 1; i < N; i++) {
        if (abs(arr[n][i] - arr[n][i - 1]) > 1)
            return;

        if (arr[n][i] - arr[n][i - 1] == 1) {
            for (int j = 1; j <= L; j++) {
                if (!in_range(i - j) || arr[n][i - 1] != arr[n][i - j] || used[n][i - j])
                    return;
                used[n][i - j] = true;
            }
        } else if (arr[n][i] - arr[n][i - 1] == -1) {
            for (int j = 0; j < L; j++) {
                if (!in_range(i + j) || arr[n][i] != arr[n][i + j] || used[n][i + j])
                    return;
                used[n][i + j] = true;
            }
        }
    }
    ans++;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    // init
    cin >> N >> L;
    ans = 0;
    memset(arr, 0, sizeof(arr));
   
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }
    memset(used, 0, sizeof(used));
    for (int i = 0; i < N; i++) 
        calc(i);
    memset(used, 0, sizeof(used));
    for (int i = 0; i < N; i++) 
        calc2(i);
    
    cout << ans << endl;
    return 0;
}