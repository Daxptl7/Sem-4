#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void dijkstra(int V, vector<vector<pair<int, int>>> &adj, int src) {
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;

  vector<int> dist(V, INT_MAX);
  dist[src] = 0;
  pq.push({0, src});

  while (!pq.empty()) {
    int u = pq.top().second;
    int d = pq.top().first;
    pq.pop();

    if (d > dist[u])
      continue;

    for (auto &edge : adj[u]) {
      int v = edge.first;
      int weight = edge.second;

      if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.push({dist[v], v});
      }
    }
  }

  cout << "Vertex\tDistance from Source" << endl;
  for (int i = 0; i < V; ++i) {
    if (dist[i] == INT_MAX)
      cout << i << "\tInfinity" << endl;
    else
      cout << i << "\t" << dist[i] << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int V, E;
  cout << "Enter number of vertices and edges: ";
  cin >> V >> E;
  if (!cin || V <= 0 || E < 0) {
    cout << "Invalid input for vertices/edges.\n";
    return 1;
  }

  vector<vector<pair<int, int>>> adj(V);

  cout << "Enter each edge as: u v weight (0-indexed, directed graph)\n";
  for (int i = 0; i < E; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    if (!cin || u < 0 || u >= V || v < 0 || v >= V || w < 0) {
      cout << "Invalid edge input.\n";
      return 1;
    }
    adj[u].push_back({v, w});
  }

  int source;
  cout << "Enter source vertex: ";
  cin >> source;
  if (!cin || source < 0 || source >= V) {
    cout << "Invalid source vertex.\n";
    return 1;
  }

  cout << "Dijkstra's Algorithm starting from source vertex " << source
       << ":\n";
  dijkstra(V, adj, source);

  return 0;
}
