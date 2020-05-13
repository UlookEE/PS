#include <bits/stdc++.h>
using namespace std;

//14 40

int N, T;
char cube[6][3][3];
char color[] = {'w', 'y', 'r', 'o', 'g', 'b'};
int mapcube[][4] = {{2, 4, 3, 5}, {5, 3, 4, 2}, {0, 5, 1, 4}, {4, 1, 5, 0}, {0, 2, 1, 3}, {3, 1, 2, 0}};
const char* mapcube2[][4] = {{"1r", "1r", "1r", "1r"}, {"3r", "3r", "3r", "3r"}, {"3r", "1c", "1r", "3c"}, {"1c", "3r", "3c", "1r"}, {"1c", "1c", "1c", "3c"}, {"1c", "3c", "3c", "3c"}};
int mapcuberev[][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 1}, {0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 0}};
string query;
char mapChar[256];

vector<char> get_row(int side, int num, int rev) {
    vector<char> v;
    for (int i = 0; i < 3; i++)
        v.push_back(cube[side][num][i]);
    if(rev)
        reverse(v.begin(), v.end());
    return v;
}

vector<char> get_col(int side, int num, int rev) {
    vector<char> v;
    for (int i = 0; i < 3; i++)
        v.push_back(cube[side][i][num]);
    if(rev)
        reverse(v.begin(), v.end());
    return v;
}

void set_row(int side, int num, vector<char>& v, int rev) {
    if(rev)
        reverse(v.begin(), v.end());
    for (int i = 0; i < 3; i++) {
        cube[side][num][i] = v[i];
    }
}

void set_col(int side, int num, vector<char>& v, int rev) {
    if(rev)
        reverse(v.begin(), v.end());
    for (int i = 0; i < 3; i++) {
        cube[side][i][num] = v[i];
    }
}

void rotate(int side, int dir) {
    if (dir == 1) {
        int ccube[3][3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                ccube[i][j] = cube[side][2-j][i];
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cube[side][i][j] = ccube[i][j];
            }
        }
    }
    vector<char> v[4];
    for (int i = 0; i < 4; i++) {
        int sidenum = mapcube[side][i];
        char type = mapcube2[side][i][1];
        char num = mapcube2[side][i][0] - '1';
        int rev = mapcuberev[side][i];
        if (type == 'r')
            v[i] = get_row(sidenum, num, rev);
        else
            v[i] = get_col(sidenum, num, rev);
    }
    for (int i = 0; i < 4; i++) {
        int sidenum = mapcube[side][i];
        char type = mapcube2[side][i][1];
        char num = mapcube2[side][i][0] - '1';
        int rev = mapcuberev[side][i];
        if (type == 'r')
            set_row(sidenum, num, v[(3 + i) % 4], rev);
        else
            set_col(sidenum, num, v[(3 + i) % 4], rev);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    mapChar['U'] = 0;
    mapChar['D'] = 1;
    mapChar['F'] = 2;
    mapChar['B'] = 3;
    mapChar['L'] = 4;
    mapChar['R'] = 5;
    cin >> T;
    while (T--) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cube[i][j][k] = color[i];
                }
            }
        }
        cin >> N;
        while (N--) {
            cin >> query;
            if (query[1] == '+')
                rotate(mapChar[query[0]], 1);
            else {
                for (int i = 0; i < 3; i++)
                    rotate(mapChar[query[0]], 1);
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << cube[0][i][j];
            }
            cout << '\n';
        }
    }

    return 0;
}