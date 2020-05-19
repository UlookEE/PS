#include<iostream>
using namespace std;

int val[] = { 
	-1,2,4,6,8,
	10,12,14,16,18,
	20,22,24,26,28,
	30,32,34,36,38,
	13,16,19,22,24,
	28,27,26,25,30,
	35,40,0,0,0,0,0,0,0,0 };
struct Info {
	int val;
	Info* next;
	bool isBlue;
	Info* blueNext;
};
Info inf[40];

Info* pos[4] = { 0,0,0,0 };
int mv[10];
int maxScore = 0;
void dfs(int depth, int score) {
	if (depth == 10) {
		maxScore = maxScore > score ? maxScore : score;
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (pos[i]->val == 0)
			continue;
		Info* tmpPos = pos[i];
		int mvCount = mv[depth] - 1;
		if (tmpPos->isBlue == true)
			tmpPos = tmpPos->blueNext;
		else
			tmpPos = tmpPos->next;
		while (mvCount--)
			tmpPos = tmpPos->next;
		for (int j = 0; j < 4; j++) {
			if (tmpPos == pos[j] && i != j && tmpPos->val != 0)
				break;
			if (j == 3) {
				Info* savePos = pos[i];
				pos[i] = tmpPos;
				dfs(depth + 1, score + pos[i]->val);
				pos[i] = savePos;
			}
		}
	}
}
int main() {
	for (int i = 0; i < 39; i++) 
		inf[i] = { val[i], &inf[i + 1], false, NULL };
	inf[5].isBlue = true;
	inf[10].isBlue = true;
	inf[15].isBlue = true;
	inf[5].blueNext = &inf[20];
	inf[10].blueNext = &inf[23];
	inf[15].blueNext = &inf[25];
	inf[22].next = &inf[28];
	inf[24].next = &inf[28];
	inf[27].next = &inf[28];
	inf[19].next = &inf[31];
	for (int i = 0; i < 10; i++)
		cin >> mv[i];
	for (int i = 0; i < 4; i++)
		pos[i] = &inf[0];
	dfs(0, 0);
	cout << maxScore << '\n';
	return 0;
}
