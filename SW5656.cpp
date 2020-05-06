#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

int T, N, W, H;
int arr[20][20];
int top[20];
int ans;

void calc_top()
{
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < H; j++)
        {
            if (arr[j][i] != 0)
            {
                top[i] = j;
                break;
            }
        }
    }
}

bool in_range(int y, int x)
{
    return x >= 0 && y >= 0 && y < H && x < W;
}

void break_block(int y, int x)
{
    int val = arr[y][x];
    arr[y][x] = 0;
    // break wall

    if (val != 0)
    {

        for (int i = 1; i < val; i++)
        {
            if (in_range(y + i, x))
                break_block(y + i, x);
            if (in_range(y - i, x))
                break_block(y - i, x);
            if (in_range(y, x + i))
                break_block(y, x + i);
            if (in_range(y, x - i))
                break_block(y, x - i);
        }
    }
}

void erase_gap()
{
    for (int j = 0; j < W; j++)
    {
        int pos = H - 1;
        for (int i = H - 1; i >= 0; i--)
        {
            if (arr[i][j])
            {
                while (arr[pos][j])
                {
                    pos--;
                };
                if (pos > i)
                {
                    arr[pos][j] = arr[i][j];
                    arr[i][j] = 0;
                }
            }
        }
    }
}
void dfs(int depth)
{
    if (depth == N)
    {
        // count block
        int bc = 0;
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                if (arr[i][j] != 0)
                    bc++;
            }
        }
        ans = min(ans, bc);
        return;
    }
    int carr[20][20]; // Copy array must be here
    memcpy(carr, arr, sizeof(arr));

    for (int i = 0; i < W; i++)
    {
        calc_top();
        break_block(top[i], i);
        erase_gap();
        dfs(depth + 1);
        memcpy(arr, carr, sizeof(arr));
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    for (int test = 1; test <= T; test++)
    {
        ans = 1000;
        memset(arr, 0, sizeof(arr));
        cin >> N >> W >> H;
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                cin >> arr[i][j];
            }
        }

        dfs(0);
        cout << '#' << test << ' ' << ans << '\n';
    }
    return 0;
}