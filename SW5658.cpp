#include <bits/stdc++.h>
using namespace std;

int T, N, K;
string str;
map<int, bool> m;
vector<int> v;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    for (int test = 1; test <= T; test++) {
        m.clear();
        v.clear();
        cin >> N >> K;
        cin >> str;
        for(int i=0; i<str.length(); i++){
            int val = 0;
            int mul = 1;
            for(int j=0; j<N/4; j++){
                char c = str[(i+str.length()-j)%str.length()];
                if(c >= '0' && c<= '9')
                    c-='0';
                else
                    c = c - 'A' + 10;
                
                val += c * mul;
                mul *= 16;
            }
            if(m.find(val) == m.end()){
                m.insert({val, true});
                v.push_back(val);
            }
        }
        sort(v.begin(), v.end());
        cout << '#' << test << ' ' << v[v.size()-K] << '\n';
    }
    return 0;
}