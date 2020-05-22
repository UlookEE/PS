#include<iostream>
#include<vector>
#include<string.h>
#include<math.h>
using namespace std;

int R, C, M;

//0655
struct Shark {
	int y;
	int x;
	int speed;
	int dir;
	int size;
};

vector<Shark> vs;
int arr[100][100];
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,1, -1 };
int revdir[] = { 1,0,3,2 };
bool in_range(int y, int x) {
	return x >= 0 && y >= 0 && x < C&& y < R;
}
void move() {
	for (int i = 1; i < vs.size(); i++) {
		if (vs[i].y == -1)
			continue;
		arr[vs[i].y][vs[i].x] = 0;
	}

	for (int i = 1; i < vs.size(); i++) {
		if (vs[i].y == -1)
			continue;
		auto ele = vs[i];
		ele.y = vs[i].y + ele.speed * dy[ele.dir];
		ele.x = vs[i].x + ele.speed * dx[ele.dir];

		if (ele.y < 0) {
			ele.dir = revdir[ele.dir];
			ele.y *= -1;
		}
		if (ele.x < 0) {
			ele.dir = revdir[ele.dir];
			ele.x *= -1;
		}
		ele.y = ele.y % (2 * (R - 1));
		ele.x = ele.x % (2 * (C - 1));
		if (ele.y >= R) {
			ele.dir = revdir[ele.dir];
			ele.y = 2 * R - 2 - ele.y;
		}
		if (ele.x >= C) {
			ele.dir = revdir[ele.dir];
			ele.x = 2 * C - 2 - ele.x;
		}

		if (arr[ele.y][ele.x] == 0) {
			arr[ele.y][ele.x] = i;
			vs[i] = ele;
		}
		else {
			auto& friendShark = vs[arr[ele.y][ele.x]];
			if (ele.size > friendShark.size) {
				arr[ele.y][ele.x] = i;
				friendShark.y = -1;
				vs[i] = ele;
			}
			else {
				vs[i].y = -1;
			}
		}
	}
}
int solve() {
	int sum = 0;
	for (int j = 0; j < C; j++) {
		for (int i = 0; i < R; i++) {
			if (arr[i][j] != 0) {
				sum += vs[arr[i][j]].size;
				vs[arr[i][j]].y = -1;
				arr[i][j] = 0;
				break;
			}
		}
		move();
	}
	return sum;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> R >> C >> M;
	vs.push_back({ -1,-1,-1,-1,-1 });
	for (int i = 0; i < M; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		r--;
		c--;
		d--;
		vs.push_back({ r, c, s, d, z });
		arr[r][c] = i + 1;
	}

	cout << solve() << '\n';
	return 0;
}
