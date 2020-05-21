#include<iostream>
#include<string.h>
using namespace std;

//1100

int R, C, T;
int arr[51][51];
int carr[51][51];

int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

struct Pos {
	int y;
	int x;
};

Pos machine[2];

bool in_range(int y, int x) {
	return x >= 0 && y >= 0 && x < C&& y < R;
}
void spread() {
	memset(carr, 0, sizeof(carr));
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			int dust = arr[i][j];
			int spDust = arr[i][j] / 5;
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (in_range(ny, nx) && arr[ny][nx] != -1) {
					arr[i][j] -= spDust;
					carr[ny][nx] += spDust;
				}
			}
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			arr[i][j] += carr[i][j];
		}
	}
}

void erase() {
	int dir[4] = { 0,3,1,2 };
	int y = machine[0].y;
	int x = machine[0].x;
	int saveDust = 0;
	for (int i = 0; i < 4; i++) {
		while (true) {
			int ny = y + dy[dir[i]];
			int nx = x + dx[dir[i]];
			if (in_range(ny, nx) && arr[ny][nx] != -1) {
				int tmp = arr[ny][nx];
				arr[ny][nx] = saveDust;
				saveDust = tmp;
				y = ny;
				x = nx;
			}
			else {
				break;
			}
		}
	}
	dir[1] = 2;
	dir[3] = 3;
	y = machine[1].y;
	x = machine[1].x;
	saveDust = 0;

	for (int i = 0; i < 4; i++) {
		while (true) {
			int ny = y + dy[dir[i]];
			int nx = x + dx[dir[i]];
			if (in_range(ny, nx) && arr[ny][nx] != -1) {
				int tmp = arr[ny][nx];
				arr[ny][nx] = saveDust;
				saveDust = tmp;
				y = ny;
				x = nx;
			}
			else {
				break;
			}
		}
	}
}

int main() {
	cin >> R >> C >> T;
	int machineInd = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == -1) {
				machine[machineInd++] = { i,j };
			}
		}
	}

	while (T--) {
		spread();
		erase();
	}

	int sum = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			sum += arr[i][j];
		}
	}
	sum += 2;
	cout << sum << '\n';
	return 0;
}
