#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

int T, M, N;
int arr[20][20];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int max_ans;

struct node
{
    int y;
    int x;
    int k;
};

node q[1000000];
int f, r;

bool in_range(int y, int x)
{
    return x >= 0 && y >= 0 && x < N && y < N;
}

int cal_cost(int k)
{
    return k * k + (k - 1) * (k - 1);
}

bool visited[20][20];
int mask(int y, int x, int k)
{
    int ret = 0;
    memset(visited, 0, sizeof(visited));
    f = r = 0;
    q[r++] = {y, x, 1};

    // Using dfs does not search all areas
    while (f != r)
    {
        node &n = q[f++];
        visited[n.y][n.x] = true;
        if (arr[n.y][n.x])
            ret++;
        if (n.k != k)
        {
            for (int i = 0; i < 4; i++)
            {
                if (in_range(n.y + dy[i], n.x + dx[i]) && !visited[n.y + dy[i]][n.x + dx[i]])
                {
                    visited[n.y + dy[i]][n.x + dx[i]] = true;
                    q[r++] = {n.y + dy[i], n.x + dx[i], n.k + 1};
                }
            }
        }
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    for (int test = 1; test <= T; test++)
    {
        max_ans = 0;
        memset(arr, 0, sizeof(arr));
        cin >> N >> M;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> arr[i][j];
            }
        }
        for (int k = N + 1; k >= 1; k--)
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    int res = mask(i, j, k);
                    if (res * M >= cal_cost(k))
                        max_ans = max(max_ans, res);
                }
            }
            if (max_ans)
                break;
        }
        cout << '#' << test << ' ' << max_ans << '\n';
    }
    return 0;
}