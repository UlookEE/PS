#include <bits/stdc++.h>
using namespace std;

int arr[50][50];
int N, M;

typedef pair<int,int> ii;
typedef vector<ii> vii;

#define INF 0x7FFFFFFF
vii h;
vii ch;
vii uch;
int minAns = INF;

inline int chick_len(ii i1, ii i2){
    return abs(i1.first - i2.first) + abs(i1.second - i2.second);
}
void combination(int n, int r){
    if(n < r || r < 0)
        return;
    
    if(n == 0){
        int ans = 0;
        for(int i=0; i<h.size(); i++){
            int minlen = INF;
            for(int j=0; j<uch.size(); j++)
                minlen = min(minlen, chick_len(h[i], uch[j]));
            ans += minlen;
        }
        minAns = min(minAns, ans);
        return;
    }
    uch.push_back(ch[n-1]);
    combination(n-1, r-1);
    uch.pop_back();
    combination(n-1, r);
    
}
    
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>N>>M;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin>>arr[i][j];
            if(arr[i][j] == 1)
                h.push_back({i,j});
            else if(arr[i][j] == 2)
                ch.push_back({i,j});
        }
    }
    combination(ch.size(), M);
    cout<<minAns<<endl;
    return 0;
}