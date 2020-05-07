#include <bits/stdc++.h>
using namespace std;

int arr[21][21];
int min_ans = 0x7FFFFFFF;
int N;

int calc_diff(int flag){
    int sum1 = 0;
    int sum2 = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(((1<<i) & flag) && ((1<<j) & flag))
                sum1 += arr[i][j];
            else if(((1<<i) & (~flag)) && ((1<<j) & (~flag)))
                sum2 += arr[i][j];
        }
    }
    return abs(sum2-sum1);
}
void brute_force(int flag, int pos, int sel){
    if(sel == N/2){
        min_ans = min(min_ans, calc_diff(flag));
        return;
    }
    if(pos == N)
        return;

    brute_force(flag | (1<<pos), pos + 1, sel + 1);
    brute_force(flag, pos + 1, sel);

}
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    // init
    cin>>N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin>>arr[i][j];
        }
    }

    brute_force(0,0,0);
    cout<<min_ans<<endl;
    return 0;
}