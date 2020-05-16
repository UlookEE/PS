#include<stdio.h>
using namespace std;

int N, M, H;
int arr[32][11];
int ans = 100;

inline int down(int y, int x) {
	while (++y != H + 1) {
		x += arr[y][x];
	}
	return x;
}

bool check_ans() {
	for (int i = 1; i <= N; i++) {
		if (down(0, i) != i)
			return false;
	}
	return true;
}

void dfs(int depth, int maxDepth) {
	if (depth == maxDepth + 1)
		return;
	for (int j = 1; j <= N - 1; j++) {
		for (int i = 1; i <= H; i++) {
			if (ans != 100)
				return;
			if (arr[i][j + 1] == 0 && arr[i][j] == 0 ) {
				arr[i][j] = 1;
				arr[i][j + 1] = -1;
				if (depth == maxDepth) {
					if (check_ans()) {
						ans = depth;
						return;
					}
				}
				dfs(depth + 1, maxDepth);
				arr[i][j] = 0;
				arr[i][j + 1] = 0;
				while (i != H) {
					if (arr[i + 1][j + 1] || arr[i + 1][j])
						break;
					i++;
				}
			}
		}
	}
}
	
int main() {
	scanf("%d %d %d", &N, &M, &H);
	for (int i = 0; i < M; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		arr[a][b] = 1;
		arr[a][b + 1] = -1;
	}
	if (check_ans())
		ans = 0;

	for(int i=1; i<4; i++)
		dfs(1,i);

	if (ans == 100)
		ans = -1;
	printf("%d\n", ans);
	return 0;
}
