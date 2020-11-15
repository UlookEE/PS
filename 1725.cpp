#include<iostream>
#include<cassert>

using namespace std;

class ii {
public:
	int f;
	int s;
};
class Stack {
public:
	ii arr[100001];
	int size = 0;

	void push(ii&& ii) {
		assert(size < 100001);
		arr[size++] = ii;
	}

	ii top() {
		assert(size != 0);
		return arr[size - 1];
	}

	void pop() {
		size--;
	}

	bool empty() {
		return size == 0;
	}
};

int arr[100001];
Stack s;

int main() {
	int N; cin >> N;
	for (int i = 0; i < N; i++)
		cin >> arr[i];

	s.push({ 0, arr[0]});
	int max_size = 0;

	for (int i = 1; i < N; i++) {
		if (s.empty() || s.top().s < arr[i])
			s.push({ i, arr[i] });
		else if (s.top().s > arr[i]) {
			int start = 0;
			while (!s.empty() && s.top().s > arr[i]) {
				ii ii = s.top();
				s.pop();
				int new_size = (i - ii.f) * ii.s;
				max_size = max_size > new_size ? max_size : new_size;
				start = ii.f;
			}
			s.push({ start, arr[i] });
		}
	}
	while (!s.empty()) {
		ii ii = s.top();
		s.pop();
		int new_size = (N - ii.f) * ii.s;
		max_size = max_size > new_size ? max_size : new_size;
	}
	cout << max_size << endl;
	return 0;
}
