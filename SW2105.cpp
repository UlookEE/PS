#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

int T, N;
int arr[20][20];
int visited[101];
int ans;
inline bool in_range(int y, int x) {
	return x >= 0 && y >= 0 && x < N && y < N;
}

inline void valid_square(int a, int b, int x, int y) {
	if (ans >= 2 * x + 2 * y || !(a + x + y < N && b + x < N && b - y >=0))
		return;
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i <= x; i++) {
		if (!visited[arr[a + i][b + i]])
			visited[arr[a + i][b + i]] = true;
		else
			return;
	}
	for (int i = 1; i <= y; i++) {
		if (!visited[arr[a + x + i][b + x - i]])
			visited[arr[a + x + i][b + x - i]] = true;
		else
			return;
	}
	for (int i = 1; i <= x; i++) {
		if (!visited[arr[a + x + y - i][b + x - y - i]])
			visited[arr[a + x + y - i][b + x - y - i]] = true;
		else
			return;
	}
	for (int i = 1; i < y; i++) {
		if (!visited[arr[a + y - i][b - y + i]])
			visited[arr[a + y - i][b - y + i]] = true;
		else
			return;
	}
	
	ans = 2*x + 2*y;
}

inline void process(int a, int b) {
	for (int i = N-1; i>=1; i--) {
		for (int j = N-1; j>=1; j--) {
			valid_square(a, b, i, j);
		}
	}
}

void solve() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			process(i, j);
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> N;
		ans = -1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> arr[i][j];
			}
		}
		solve();
		cout << '#' << test << ' ' << ans << '\n';
	}
	return 0;
}
