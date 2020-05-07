#include<iostream>
#include<string.h>
using namespace std;

int T, N, M, R, C, L;
int arr[50][50];
int dy[8][5] = {{0}, {1, -1, 0, 0}, {1, -1}, {0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1}};
int dx[8][5] = {{0}, {0, 0, 1, -1}, {0, 0}, {-1, 1}, {0, 1}, {0, 1}, {-1, 0}, {-1, 0}};
int findlink[8][8][4];
int dlen[] = {0, 4, 2, 2, 2, 2, 2, 2};
bool visited[50][50];
int ans;

int yy[100000];
int xx[100000];
int f, r;

int siz, y, x, ny, nx, val;

inline bool in_range(int y, int x) {
    return x >= 0 && y >= 0 && x < M && y < N;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;
    // calc findlink
    for (register int i = 1; i < 8; i++) {
        for (register int j = 0; j < dlen[i]; j++) {
            for (register int k = 1; k < 8; k++) {
                for (register int l = 0; l < dlen[k]; l++) {
                    if (dy[i][j] + dy[k][l] == 0 && dx[i][j] + dx[k][l] == 0){
                        findlink[i][k][j] = true;
                        break;
                    }
                }
            }
        }
    }

    for (int test = 1; test <= T; test++) {
        // init
        ans = 0;
        memset(arr, 0, sizeof(arr));
        memset(visited, 0, sizeof(visited));
        cin >> N >> M >> R >> C >> L;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cin >> arr[i][j];

        // bfs
        f = r = 0;
        yy[r] = R;
        xx[r++] = C;
        visited[R][C] = true;
        ans++;

        while (--L) {
            siz = r - f;
            while (siz--) {
                y = yy[f];
                x = xx[f++];
                val = arr[y][x];
                for (register int i = 0; i < dlen[val]; i++) {
                    ny = y + dy[val][i];
                    nx = x + dx[val][i];
                    if (in_range(ny, nx) && !visited[ny][nx] && findlink[val][arr[ny][nx]][i]) {
                        yy[r] = ny;
                        xx[r++] = nx;
                        visited[ny][nx] = true;
                        ans++;
                    }
                }
            }
        }
        cout << '#' << test << ' ' << ans << '\n';
    }

    return 0;
}