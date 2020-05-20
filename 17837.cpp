#include<iostream>
#include<vector>
using namespace std;

// 0655
// 20분남음
int N, K;
int arr[13][13];
struct Info {
	int y;
	int x;
	int dir;
};

int dy[] = { 0,0,-1,1 };
int dx[] = { 1,-1,0,0 };
int revdir[] = { 1,0,3,2 };
inline bool in_range(int y, int x) {
	return x >= 0 && y >= 0 && x < N&& y < N;
}

Info inf[11];
vector<int> infArr[13][13];

int main() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		int y, x, dir;
		cin >> y >> x >> dir;
		y--;
		x--;
		dir--;
		inf[i] = { y, x ,dir };
		infArr[y][x].push_back(i);
	}
	int turn = 1;
	while (true) {
		if (turn > 1000) {
			turn = -1;
			break;
		}
		for (int i = 0; i < K; i++) {
			int cury = inf[i].y;
			int curx = inf[i].x;
			int curdir = inf[i].dir;

			int ny = cury + dy[curdir];
			int nx = curx + dx[curdir];

			vector<int>& curInfArr = infArr[cury][curx];
			int iIndex = 0;
			while (curInfArr[iIndex++] != i);
			iIndex--;
			int arrsiz = curInfArr.size();
			if (!in_range(ny, nx) || arr[ny][nx] == 2) {
				curdir = revdir[curdir];
				ny += (dy[curdir] * 2);
				nx += (dx[curdir] * 2);
				inf[i].dir = curdir;
				if (!in_range(ny, nx) || arr[ny][nx] == 2)
					continue;
				
				if (arr[ny][nx] == 0) {
					for (int j = iIndex; j < arrsiz; j++) {
						inf[curInfArr[j]].y = ny;
						inf[curInfArr[j]].x = nx;
						infArr[ny][nx].push_back(curInfArr[j]);
					}
					int eraseCount = arrsiz - iIndex;
					while (eraseCount--)
						curInfArr.pop_back();
					if (infArr[ny][nx].size() > 3)
						goto ESCAPELABEL;
				}
				else if (arr[ny][nx] == 1) {
					for (int j = arrsiz - 1; j >= iIndex; j--) {
						inf[curInfArr[j]].y = ny;
						inf[curInfArr[j]].x = nx;
						infArr[ny][nx].push_back(curInfArr[j]);
						curInfArr.pop_back();
					}
					if (infArr[ny][nx].size() > 3)
						goto ESCAPELABEL;
				}
			}
			else if (arr[ny][nx] == 0) {
				for (int j = iIndex; j < arrsiz; j++) {
					inf[curInfArr[j]].y = ny;
					inf[curInfArr[j]].x = nx;
					infArr[ny][nx].push_back(curInfArr[j]);
				}
				int eraseCount = arrsiz - iIndex;
				while (eraseCount--)
					curInfArr.pop_back();
				if (infArr[ny][nx].size() > 3)
					goto ESCAPELABEL;
			}
			else if (arr[ny][nx] == 1) {
				for (int j = arrsiz - 1; j >= iIndex; j--) {
					inf[curInfArr[j]].y = ny;
					inf[curInfArr[j]].x = nx;
					infArr[ny][nx].push_back(curInfArr[j]);
					curInfArr.pop_back();
				}
				if (infArr[ny][nx].size() > 3)
					goto ESCAPELABEL;
			}
		}
		turn++;
	}
ESCAPELABEL:;
	cout << turn << '\n';
	return 0;
	
}
