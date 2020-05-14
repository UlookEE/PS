#include<iostream>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;

// 1220
int N;
int arr[20][20];
int visited[20][20];
int fishSize = 2;
int eatCount = 0;

int dy[] = { -1,0,0,1 };
int dx[] = { 0,-1,1,0 };

struct pos {
	int y;
	int x;
	int time;
};

pos fishPos;
pos minPos;
inline bool in_range(int y, int x) {
	return x >= 0 && y >= 0 && x < N&& y < N;
}

inline pos min(pos p1, pos p2) {
	if (p1.y != p2.y) {
		if (p1.y < p2.y)
			return p1;
		else
			return p2;
	}
	else {
		if (p1.x < p2.x)
			return p1;
		else
			return p2;
	}

}

int time = 0;
void solve() {
	bool findFlag = true;
	while (findFlag) {
		memset(visited, 0, sizeof(visited));
		findFlag = false;
		queue<pos> q;
		minPos = { 100000,100000,100000};
		q.push(fishPos);
		visited[fishPos.y][fishPos.x] = true;
		while (!q.empty()) {
			auto e = q.front();
			q.pop();
			if (e.time > minPos.time)
				break;
			for (int i = 0; i < 4; i++) {
				int ny = e.y + dy[i];
				int nx = e.x + dx[i];
				if (in_range(ny, nx) && !visited[ny][nx]) {
					if (arr[ny][nx] && arr[ny][nx] < fishSize) {
						pos tmp = { ny, nx, e.time };
						minPos = min(minPos, tmp);
						findFlag = true;
					}
					else {
						visited[ny][nx] = true;
						if(!findFlag && arr[ny][nx] <= fishSize)
							q.push({ ny,nx,e.time + 1 });
					}
				}
			}
		}
		if (findFlag) {
			arr[fishPos.y][fishPos.x] = 0;
			arr[minPos.y][minPos.x] = 9;
			eatCount++;
			time += minPos.time + 1;
			if (eatCount == fishSize) {
				eatCount = 0;
				fishSize++;
			}
			fishPos = { minPos.y,minPos.x };
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 9)
				fishPos = { i,j,0 };
		}
	}
	solve();
	cout << time << '\n';
	return 0;
}

//0111
