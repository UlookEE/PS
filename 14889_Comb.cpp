#include <iostream>

using namespace std;

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define ABS(a) ((a) >= 0 ? (a) : (-(a)))

int arr[21][21];
int min_ans = 0x7FFFFFFF;
int N;

void combination(int flag, int n, int r, int s1, int s2) {
    if (!min_ans || n < r || r < 0)
        return;

    if (n == 0) {
        min_ans = MIN(min_ans, ABS(s1 - s2));
        return;
    }
    
    int ns1 = s1;
    for (int i = N - 1; i >= n; i--)
        if ((1 << i) & (~flag))
            ns1 += (arr[i][n - 1] + arr[n - 1][i]);

    combination(flag, n - 1, r - 1, ns1, s2);

    int ns2 = s2;
    for (int i = N - 1; i >= n; i--)
        if ((1 << i) & (flag))
            ns2 += (arr[i][n - 1] + arr[n - 1][i]);

    combination(flag | (1 << (n - 1)), n - 1, r, s1, ns2);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // init
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }

    combination(0, N, N / 2, 0, 0);
    cout << min_ans << '\n';
    return 0;
}