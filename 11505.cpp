#include<iostream>
#include<cassert>

using namespace std;

#define MOD 1000000007
typedef long long ll;

class SegmentTree {
public:
	ll t[1000000 * 2];
	int N;

	void build(ll* arr, int N) {
		this->N = N;
		for (int i = 0; i < N; i++)
			t[i + N] = arr[i];
		for (int i = N - 1; i >= 1; i--)
			t[i] = t[i << 1] * t[i << 1 | 1] % MOD;
	}

	void replace(int idx, int val) {
		int rIdx = idx + N - 1;
		t[rIdx] = val;
		while (rIdx > 1) {
			t[rIdx >> 1] = t[rIdx] * t[rIdx ^ 1] % MOD;
			rIdx >>= 1;
		}
	}

	ll query(int l, int r) {
		ll res = 1;
		for (l += N-1, r += N; l < r; l >>= 1, r >>= 1) {
			if (l & 1)
				res = res * t[l++] % MOD;
			if (r & 1)
				res = res * t[--r] % MOD;
		}
		return res;
	}
};

ll arr[1000000];
SegmentTree st;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int N, M, K;
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	st.build(arr, N);

	for (int i = 0; i < M + K; i++) {
		int q, a, b;
		cin >> q >> a >> b;
		if (q == 1) {
			st.replace(a, b);
		}
		else if (q == 2) {
			cout<<st.query(a, b)<<'\n';
		}
	}
	return 0;
}
