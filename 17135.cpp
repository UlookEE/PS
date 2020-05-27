#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
using namespace std;

int N, M, D;
int arr[16][16];

struct ArrowPos {
	int y;
	int x;
};

struct EnemyPos {
	int y;
	int x;
	int targeted;
};

vector<EnemyPos> enemyVec;
vector<ArrowPos> arrowVec;
#define MIN 0
#define MAX 987654321
int answer = MIN;

inline int distance(const ArrowPos& ap, const EnemyPos& ep) {
	return abs(ap.y - ep.y) + abs(ap.x - ep.x);
}
void simulate() {
	vector<EnemyPos> enemyVecCopy = enemyVec;
	vector<EnemyPos> enemyVecTmp;
	int killCount = 0;
	EnemyPos t = EnemyPos({ MAX,MAX,0 });
	while (enemyVecCopy.size()) {
		for (auto& arrow : arrowVec) {
			EnemyPos* target = &t;
			int targetDist = 10000;
			for (auto& enemy : enemyVecCopy) {
				int dist1 = distance(arrow, enemy);
				if (dist1 <= D) {
					if (dist1 < targetDist || (dist1 == targetDist && enemy.x < target->x)) {
						enemy.targeted++;
						target->targeted--;
						target = &enemy;
						targetDist = dist1;
					}
				}
			}


		}
		enemyVecTmp.clear();
		for (auto& enemy : enemyVecCopy) {
			if (enemy.targeted)
				killCount++;
			else if (enemy.y < N - 1)
				enemyVecTmp.push_back({ enemy.y + 1, enemy.x, 0 });
		}
		enemyVecCopy = enemyVecTmp;
	}
	answer = max(answer, killCount);
}
void combination(int n, int r) {
	if (n < r || r < 0 || answer == enemyVec.size())
		return;
	if (r == 0) {
		simulate();
		return;
	}
	arrowVec.push_back({ N, M - n });
	combination(n - 1, r - 1);
	arrowVec.pop_back();
	combination(n - 1, r);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> D;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1) {
				enemyVec.push_back({ i,j,0 });
			}
		}
	}

	combination(M, 3);
	cout << answer << endl;
	return 0;
}
