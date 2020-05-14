#include<iostream>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;

int N, L, R;
int arr[50][50];
int visited[50][50];

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

inline bool in_range(int y, int x) {
	return x >= 0 && y >= 0 && x < N&& y < N;
}

struct pos {
	int y;
	int x;
};

inline bool is_uni(pos p1, pos p2) {
	int diff = abs(arr[p1.y][p1.x] - arr[p2.y][p2.x]);
	return  diff >= L && diff <= R;
}

int solve() {
	int retval = 0;
	queue<pos> q;
	vector<pos> v;
	while (true) {
		memset(visited, 0, sizeof(visited));
		int breakFlag = true;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!visited[i][j]) {
					v.clear();
					q.push({ i,j });
					v.push_back({ i,j });
					visited[i][j] = true;
					int sum = arr[i][j];
					int count = 1;
					while (!q.empty()) {
						auto e = q.front();
						q.pop();
						for (int i = 0; i < 4; i++) {
							int ny = e.y + dy[i];
							int nx = e.x + dx[i];
							if (in_range(ny, nx) && !visited[ny][nx] && is_uni(e, { ny, nx })) {
								visited[ny][nx] = true;
								sum += arr[ny][nx];
								count++;
								q.push({ ny,nx });
								v.push_back({ ny, nx });
							}
						}
					}
					int avg = sum / count;
					for (int i = 0; i < v.size(); i++) {
						if (arr[v[i].y][v[i].x] != avg) {
							breakFlag = false;
							arr[v[i].y][v[i].x] = avg;
						}
					}
				}
			}
		}
		if (breakFlag)
			break;
		else
			retval++;
	}
	return retval;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}

	cout << solve() << '\n';
	return 0;
}
