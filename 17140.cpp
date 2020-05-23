#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
#include<math.h>
using namespace std;

int r, c, k;

typedef vector<vector<int>> VII;
typedef vector<int> VI;
typedef vector<pair<int, int>> VPII;
VII vii;

int time = 0;
void solve() {
	while (true) {
		int rlen = vii.size();
		int clen = vii[0].size();
		if (r < rlen && c < clen && vii[r][c] == k)
			break;
		time++;
		if (time == 101) {
			time = -1;
			break;
		}
		if (rlen < clen) {
			VII tvii;
			for (int i = 0; i < clen; i++) {
				VI vi;
				for (int j = 0; j < rlen; j++)
					vi.push_back(vii[j][i]);
				tvii.push_back(vi);
			}
			vii = tvii;
		}
		int max_rlen = 0;
		VII tvii;
		for (int i = 0; i < vii.size(); i++) {
			VPII vpii;
			sort(vii[i].begin(), vii[i].end());
			for (int j = 0; j < vii[i].size(); j++) {
				if (vii[i][j] == 0)
					continue;
				if (vpii.size() == 0) {
					vpii.push_back({ 1,vii[i][j] });
					continue;
				}
				if (vii[i][j] != vpii.back().second)
					vpii.push_back({ 1,vii[i][j] });
				else
					vpii.back().first++;
			}
			max_rlen = max(max_rlen, (int)vpii.size() * 2);
			sort(vpii.begin(), vpii.end());
			VI vi;
			for (int j = 0; j < vpii.size(); j++) {
				if (vi.size() == 100)
					break;
				vi.push_back(vpii[j].second);
				vi.push_back(vpii[j].first);
			}

			tvii.push_back(vi);
		}
		for (int i = 0; i < tvii.size(); i++) {
			for (int j = tvii[i].size(); j < max_rlen && j < 100; j++)
				tvii[i].push_back(0);
		}

		vii = tvii;

		if (rlen < clen) {
			VII tvii;
			for (int i = 0; i < vii[0].size(); i++) {
				VI vi;
				for (int j = 0; j < vii.size(); j++)
					vi.push_back(vii[j][i]);
				tvii.push_back(vi);
			}
			vii = tvii;
		}

	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> r >> c >> k;
	r--;
	c--;
	for (int i = 0; i < 3; i++) {
		VI vi;
		for (int j = 0; j < 3; j++) {
			int tmp; cin >> tmp;
			vi.push_back(tmp);
		}
		vii.push_back(vi);
	}
	solve();
	cout << time << '\n';
	return 0;
}
