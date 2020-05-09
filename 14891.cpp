#include <bits/stdc++.h>
using namespace std;

char arr[4][8];
int link[] = {-1, 2, 6, 2, 6, 2, 6, -1};
int K;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    // init
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> arr[i][j];
            arr[i][j] -= '0';
        }
    }

    cin >> K;
    while (K--) {
        int pos, dir;
        cin >> pos >> dir;
        pos--;
        int rotdir[4];
        memset(rotdir, 0, sizeof(rotdir));
        rotdir[pos] = dir;

        for (int i = pos; i < 3; i++) {
            if (arr[i][2] != arr[i + 1][6]) {
                rotdir[i + 1] = -rotdir[i];
            } else {
                break;
            }
        }

        for (int i = pos; i > 0; i--) {
            if (arr[i][6] != arr[i - 1][2]) {
                rotdir[i - 1] = -rotdir[i];
            } else {
                break;
            }
        }

        for (int i = 0; i < 4; i++) {
            if (rotdir[i] == 1) {
                char tmp = arr[i][7];
                for (int j = 6; j >= 0; j--)
                    arr[i][j + 1] = arr[i][j];
                arr[i][0] = tmp;
            } else if (rotdir[i] == -1) {
                char tmp = arr[i][0];
                for (int j = 1; j < 8; j++)
                    arr[i][j - 1] = arr[i][j];
                arr[i][7] = tmp;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 4; i++) {
        if (arr[i][0] == 1)
            ans += pow(2, i);
    }
    cout << ans << endl;
    return 0;
}