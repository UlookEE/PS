#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;

int N, M;
int arr[50][50];

//0435
struct pos {
	int y;
	int x;
};

struct qnode {
	int y;
	int x;
	int time;
};
typedef deque<qnode> QP;
typedef vector<pos> VP;
VP vp;
QP qp;
int emptyCount = 0;

int dy[] = { -1,1,0,0};
int dx[] = { 0,0,-1,1 };

bool in_range(int y, int x) {
	return x >= 0 && y >= 0 && x < N&& y < N;
}

int answer = 1234123;
void process(QP q) {
	int carr[50][50];
	memcpy(carr, arr, sizeof(arr));
	int count = vp.size();
	int maxTime = 0;
	while (!q.empty()) {
		if (count == emptyCount)
			break;
		auto ele = q.front();
		q.pop_front();
		carr[ele.y][ele.x] = 3;
		for (int i = 0; i < 4; i++) {
			int ny = ele.y + dy[i];
			int nx = ele.x + dx[i];
			if (in_range(ny, nx)) {
				if (carr[ny][nx] == 0) {
					carr[ny][nx] = 3;
					count++;
					q.push_back({ ny, nx, ele.time + 1 });
					maxTime = max(maxTime, ele.time + 1);
				}
				else if (carr[ny][nx] == 2) {
					carr[ny][nx] = 3;
					q.push_back({ ny, nx, ele.time + 1 });
					maxTime = max(maxTime, ele.time + 1);
				}
			} 
		}
	}
	if (count == emptyCount)
		answer = min(answer, maxTime);
}

void combination(int n, int r) {
	if (n < 0 || r < 0 || n < r)
		return;
	if (n == 0) {
		process(qp);
		return;
	}


	qp.push_back({vp[vp.size() - n].y, vp[vp.size() - n].x, 0});
	combination(n - 1, r - 1);
	qp.pop_back();
	combination(n - 1, r);
}

void solve() {
	combination(vp.size(), M);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 2) {
				emptyCount++;
				vp.push_back({ i,j });
			}
			else if (arr[i][j] == 0)
				emptyCount++;
		}
	}
	solve();
	if (answer == 1234123)
		answer = -1;
	cout << answer << '\n';
	return 0;
}
