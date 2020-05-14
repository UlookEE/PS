#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

int T, N, K;
int arr[8][8];
bool visited[8][8];
int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

inline bool in_range(int y, int x) {
	return x >= 0 && y >= 0 && x < N && y < N;
}

int maxDepth;
void dfs(int depth, int minVal, int y, int x, int used) {
	if (depth > maxDepth)
		maxDepth = depth;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (in_range(ny, nx) && !visited[ny][nx]) {
			if (minVal > arr[ny][nx]) {
				visited[ny][nx] = true;
				dfs(depth + 1, arr[ny][nx], ny, nx, used);
				visited[ny][nx] = false;
			}
			else if (used && (arr[ny][nx] - minVal < K)) {
				visited[ny][nx] = true;
				dfs(depth + 1, minVal - 1, ny, nx, false);
				visited[ny][nx] = false;
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> N >> K;
		maxDepth = 0;
		memset(visited, 0, sizeof(visited));
		int maxHeight = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> arr[i][j];
				maxHeight = max(maxHeight, arr[i][j]);
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (arr[i][j] == maxHeight) {
					visited[i][j] = true;
					dfs(1, arr[i][j], i, j, 1);
					visited[i][j] = false;
				}
			}
		}
		cout << '#' << test << ' ' << maxDepth << '\n';
	}

	return 0;
}
