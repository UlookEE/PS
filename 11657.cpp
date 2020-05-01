#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> ii;

const int MAX_V = 502;
const int INF = 987654321;

int dist[MAX_V], cost[MAX_V];
int inQ[MAX_V];
int prev_v[MAX_V];
int cycle[MAX_V];

vector<ii> adj[MAX_V];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int from, to, val;
        cin >> from >> to >> val;
        adj[from].push_back({to, val});
    }

    fill(dist, dist + MAX_V, INF);
    queue<int> q;
    dist[1] = 0;
    inQ[1] = true;

    q.push(1);
    cycle[1]++;

    while (!q.empty())
    {
        int here = q.front();
        q.pop();
        inQ[here] = false;

        for (int i = 0; i < adj[here].size(); i++)
        {
            int next = adj[here][i].first;
            int cost = adj[here][i].second;
            if (dist[next] > dist[here] + cost)
            {
                dist[next] = dist[here] + cost;
                prev_v[next] = here;
                if (!inQ[next])
                {
                    cycle[next]++;
                    if (cycle[next] >= n)
                    {
                        printf("-1\n");
                        return 0;
                    }
                    q.push(next);
                    inQ[next] = true;
                }
            }
        }
    }
    for (int i = 2; i <= n; i++)
        printf("%d\n", dist[i] != INF ? dist[i] : -1);
    return 0;
}