#include<iostream>
#include<string.h>
#include<algorithm>
#include<assert.h>
using namespace std;

int T, N, K;
int user[2][100];

int dy[] = { 0,-1,0,1,0 };
int dx[] = { 0,0,1,0,-1 };
//1115
struct ChargePlace {
	int y;
	int x;
	int range;
	int process;
};

struct Position {
	int y;
	int x;
};

ChargePlace cp[8];
Position human[2];

int ans;

inline bool in_range(const Position& p, const ChargePlace& cp) {
	return (abs(p.y - cp.y) + abs(p.x - cp.x)) <= cp.range;
}

void dfs(int time, Position h1, Position h2, int chargeSum) {
	if (time == N+1) {
		ans = max(ans, chargeSum);
		return;
	}

	int maxCharge = 0;
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			if (i != j) {
				int charge = 0;
				if (in_range(h1, cp[i]))
					charge += cp[i].process;
				if (in_range(h2, cp[j]))
					charge += cp[j].process;
				maxCharge = max(charge, maxCharge);
			}
			else {
				if (in_range(h1, cp[j]) || in_range(h2, cp[j]))
					maxCharge = max(cp[j].process, maxCharge);
			}
		}
	}
	Position nh1 = { h1.y + dy[user[0][time]], h1.x + dx[user[0][time]] };
	Position nh2 = { h2.y + dy[user[1][time]], h2.x + dx[user[1][time]] };

	dfs(time + 1, nh1, nh2, chargeSum + maxCharge);
}

void solve() {
	ans = 0;
	human[0] = { 1,1 };
	human[1] = { 10,10 };
	dfs(0, human[0], human[1], 0);
}



int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> N >> K;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < N; j++) {
				cin >> user[i][j];
			}
		}
		for (int i = 0; i < K; i++) {
			int y, x, c, p;
			cin >> x >> y >> c >> p;
			cp[i] = { y,x,c,p };
		}

		solve();

		cout << '#' << test << ' ' << ans << '\n';
	}

	return 0;
}
