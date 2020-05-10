#include<iostream>
#include<string.h>
using namespace std;

int N, M;
int arr[8][8];
int maxRot[] = {-1,4,2,4,4,1,-1};
int curCount[] = {0,1,2,2,3,4,0};
int dy[7][4][4] =   {{{}},
                    {{0,1,0,-1}},
                    {{0,1},{0,-1}},
                    {{0,1,0,-1},{-1,0,1,0}},
                    {{0,1,0,-1},{0,-1,0,1},{-1,0,1,0}},
                    {{0},{1},{0},{-1}},
                    {{0}}};
int dx[7][4][4] =   {{{}},
                    {{1,0,-1,0}},
                    {{1,0},{-1,0}},
                    {{1,0,-1,0},{0,1,0,-1}},
                    {{1,0,-1,0},{-1,0,1,0},{0,1,0,-1}},
                    {{1},{0},{-1},{0}},
                    {{0}}};

struct Node{
    int y;
    int x;
    int val;
};

Node vn[8];
int vnsize;
int maxDepth;
int ans = 1000;

inline bool in_range(int y, int x){
    return x>=0 && y>=0 && x<M && y<N;
}

void dfs(int depth, int bs){
    if(depth == vnsize){
        ans = min(ans, bs);
        return;
    }

    int carr[8][8];
    memcpy(carr,arr,sizeof(arr));

    for(int i=0; i<maxRot[vn[depth].val]; i++){
        int nbs = bs;
        for(int j=0; j<curCount[vn[depth].val]; j++){
            int diry = dy[vn[depth].val][j][i];
            int dirx = dx[vn[depth].val][j][i];
            int py = vn[depth].y;
            int px = vn[depth].x;
            while(true){
                px += dirx;
                py += diry;
                if(!in_range(py, px) || arr[py][px] == 6){
                    break;
                }
                if(arr[py][px] == 0){
                    arr[py][px] = '#';
                    nbs--;
                }
            }
        }
        dfs(depth + 1, nbs);
        memcpy(arr,carr,sizeof(arr));
    }
}

void solve(){
    int bs = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(arr[i][j] == 0)
                bs++;
        }
    }

    dfs(0, bs);
}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    // init
    cin>>N>>M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin>>arr[i][j];
            if(arr[i][j] > 0 && arr[i][j] < 6)
                vn[vnsize++] = {i,j,arr[i][j]};
        }
    }

    solve();
    cout<<ans<<endl;
    
    return 0;
}