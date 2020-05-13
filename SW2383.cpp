#include<bits/stdc++.h>

using namespace std;
int N, T;
int arr[10][10];
typedef vector<pair<int, int>> vii;
typedef vector<int> vi;
#define y first
#define x second
#define INF 100000000
vii p;
vii st;
int times[10][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;

    for (int test = 1; test <= T; test++) {
        p.clear();
        st.clear();
        cin >> N;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> arr[i][j];
                if (arr[i][j] == 1)
                    p.push_back({i, j});
                if (arr[i][j] > 1)
                    st.push_back({i, j});
            }
        }
        for (int i = 0; i < p.size(); i++) {
            for (int j = 0; j < st.size(); j++) {
                times[i][j] = abs(p[i].y - st[j].y) + abs(p[i].x - st[j].x);
            }
        }

        int lc = 1 << p.size();
        int minans = INF;
        vi v[2];
        for (int i = 0; i < lc; i++) {
            v[0].clear();
            v[1].clear();
            for (int j = 0; (1 << j) < (1 << p.size()); j++) {
                if (i & (1 << j))
                    v[0].push_back(times[j][0]);
                else
                    v[1].push_back(times[j][1]);
            }
            sort(v[0].begin(), v[0].end());
            sort(v[1].begin(), v[1].end());

            int time[2] = {0, 0};
            int proc;
            for (int j = 0; j < 2; j++) {
                proc = 0;
                int downtime = arr[st[j].y][st[j].x] + 1;
                while (proc != v[j].size()) {
                    time[j]++;
                    if(time[j] >= minans)
                        goto ESCAPELABEL;
                    int downcount = 0;
                    for (int k = proc; k < v[j].size(); k++) {
                        if (v[j][k] > 0 || downcount != 3)
                            v[j][k]--;
                        if (v[j][k] == -downtime)
                            proc++;
                        else if (v[j][k] < 0)
                            downcount++;
                    }
                }
            }
            ESCAPELABEL:
            int ans = max(time[0], time[1]);
            minans = min(ans, minans);
        }

        cout << '#' << test << ' ' << minans << '\n';
    }
}

