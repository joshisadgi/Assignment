#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    // Create adjacency list to represent the network
    vector<vector<pair<int, int>>> adjList(n + 1);
    for (auto& time : times) {
        int u = time[0], v = time[1], w = time[2];
        adjList[u].push_back({v, w});
    }

    // Initialize distance array to INF
    vector<int> dist(n + 1, INF);

    // Priority queue to store nodes ordered by distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Add source node k to the queue
    pq.push({0, k});
    dist[k] = 0;

    // Run Dijkstra's algorithm
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto& edge : adjList[u]) {
            int v = edge.first, w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // Find the maximum distance among all nodes
    int maxDist = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) {
            // There is a node that is not reachable from source k
            return -1;
        }
        maxDist = max(maxDist, dist[i]);
    }

    return maxDist;
}

int main() {
    vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
    int n = 4, k = 2;
    int ans = networkDelayTime(times, n, k);
    cout << ans << endl;
    return 0;
}
