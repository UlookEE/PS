#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

typedef pair<int, int> ii;

const int MAX_V = 502;
const int INF = 987654321;

/* 
* Dist must be long long because maximum is 
* -10000(edge max val) * 500(vertex max) * 500(max cycle size)
*/
long long dist[MAX_V];
int inQ[MAX_V];
int cycle[MAX_V];
vector<ii> adj[MAX_V];

/*
* MAX_V : MAXIMUN vertex count
* INF : VALUE OF INFINITE
* dist : distance from vertex 1
* cycle : check visit count... count >=n -> cycle
* adj : edge list
*/

/* 
* SPFA Algorithm
* Worst Time Complexity O(V*E)
* Average Time Complexity O(V+E) or O(E)

* Bellman-Ford : Update for all edge
-> SPFA : Update vertex which connected with updated vertex
*/

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

    /* Fill INF to dist array */
    fill(dist, dist + MAX_V, INF);

    /* Push updated vertex */
    queue<int> q;

    /* First push vertex is 1 */
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
            if (dist[next] > dist[here] + cost && dist)
            {
                /* Update vetices.... */
                dist[next] = dist[here] + cost;
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