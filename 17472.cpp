#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
#include<queue>
#include<math.h>
using namespace std;

//0418
constexpr int INF = 987654321;

int p[6];
int set_size[6];
int N, M;
int arr[10][10];
bool visited[10][10];
struct Pos {
	int y;
	int x;
};
struct Edge {
	int weight;
	int start;
	int end;
};
vector<Pos> islandVec[7];
vector<Edge> edgeVec;

int find(int n) {
	if (p[n] != n)
		return p[n] = find(p[n]);
	return p[n];
}

int union_set(int a, int b) {
	int pa = find(a);
	int pb = find(b);
	if (pa != pb) {
		p[pb] = pa;
		set_size[pa] += set_size[pb];
		return set_size[pa];
	}
	return 0;
}

void find_edge(int is1, int is2) {
	int minLen = INF;
	for (auto e1 : islandVec[is1]) {
		for (auto e2 : islandVec[is2]) {
			if (e1.y == e2.y && abs(e1.x - e2.x) > 2) {
				int start = min(e1.x, e2.x);
				int end = max(e1.x, e2.x);
				for (int i = start + 1; i < end; i++) {
					if (arr[e1.y][i] != 0)
						goto ESCAPELABEL1;
				}
				minLen = min(minLen, abs(e1.x - e2.x) - 1);
			}
			else if (e1.x == e2.x && abs(e1.y - e2.y) > 2) {
				int start = min(e1.y, e2.y);
				int end = max(e1.y, e2.y);
				for (int i = start + 1; i < end; i++) {
					if (arr[i][e1.x] != 0)
						goto ESCAPELABEL1;
				}
				minLen = min(minLen, abs(e1.y - e2.y) - 1);
			}
		ESCAPELABEL1:;
		}
	}
	if (minLen != INF)
		edgeVec.push_back({ minLen, is1, is2 });

}

bool in_range(int y, int x) {
	return x >= 0 && y >= 0 && y < N && x < M;
}

int dy[] = { 0,0,-1,1 };
int dx[] = { 1,-1,0,0 };
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}
	queue<Pos> q;
	int islandCount = -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!visited[i][j] && arr[i][j]) {
				islandCount++;
				q.push({ i,j });
				while (!q.empty()) {
					Pos p = q.front();
					q.pop();
					visited[p.y][p.x] = true;
					islandVec[islandCount].push_back({ p.y,p.x });
					for (int k = 0; k < 4; k++) {
						int ny = p.y + dy[k];
						int nx = p.x + dx[k];
						if (in_range(ny, nx) && !visited[ny][nx] && arr[ny][nx]) {
							visited[ny][nx] = true;
							q.push({ ny,nx });
						}
					}
				}
			}
		}
	}
	islandCount++;
	for (int i = 0; i < 6; i++) {
		for (int j = i + 1; j < 6; j++) {
			find_edge(i,j);
		}
	}
	sort(edgeVec.begin(), edgeVec.end(), [](Edge& e1, Edge& e2)->bool {return e1.weight < e2.weight; });

	for (int i = 0; i < 6; i++) {
		set_size[i] = 1;
		p[i] = i;
	}

	int answer = 0;
	bool isAnswer = false;
	for (auto ele : edgeVec) {
		int retval = union_set(ele.start, ele.end);
		if (retval == islandCount) {
			answer += ele.weight;
			isAnswer = true;
			break;
		}
		else if (retval) {
			answer += ele.weight;
		}
	}
	if (!isAnswer)
		answer = -1;
	cout << answer << '\n';
	return 0;
}
