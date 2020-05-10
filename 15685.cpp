#include <bits/stdc++.h>
using namespace std;

int N, x, y, g, d;
int arr[101][101];

int dy[] = {0, -1, 0, 1};
int dx[] = {1, 0, -1, 0};

pair<int, int> lastpoint;
pair<int, int> tlastpoint;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    while(N--) {
        cin >> x >> y >> d >> g;
        vector<pair<int, int>> vii;
        vii.push_back({y, x});
        vii.push_back({y + dy[d], x + dx[d]});
        arr[y][x] = 1;
        arr[y + dy[d]][x + dx[d]] = 1;
        lastpoint = vii[1];
        while (g--) {
            int siz = vii.size();
            for (int i = 0; i < siz; i++) {
                pair<int, int> p = {vii[i].first - lastpoint.first, vii[i].second - lastpoint.second};
                int tmp = p.second;
                p.second = -p.first;
                p.first = tmp;
                p.first += lastpoint.first;
                p.second += lastpoint.second;
                arr[p.first][p.second] = 1;
                vii.push_back(p);
                if (vii[i].first == y && vii[i].second == x) {
                    tlastpoint = p;
                }
                
            }
            lastpoint = tlastpoint;
        }
    }
    int ans = 0;
    for(int i=0; i<100; i++){
        for(int j=0; j<100; j++){
            if(arr[i][j] && arr[i+1][j] && arr[i][j+1] && arr[i+1][j+1])
                ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}