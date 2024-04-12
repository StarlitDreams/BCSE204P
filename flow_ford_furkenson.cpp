#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

bool bfs(vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) {
    int V = residualGraph.size();
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                if (v == sink) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                visited[v] = true;
                parent[v] = u;
            }
        }
    }
    return false;
}

int fordFulkerson(vector<vector<int>>& graph, int source, int sink) {
    int u, v;
    int V = graph.size();
    vector<vector<int>> residualGraph = graph;
    vector<int> parent(V);
    int max_flow = 0;

    while (bfs(residualGraph, source, sink, parent)) {
        int path_flow = INT_MAX;
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, residualGraph[u][v]);
        }

        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            residualGraph[u][v] -= path_flow;
            residualGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> graph(V, vector<int>(V, 0));
    int s, t, capacity;

    for (int i = 0; i < E; i++) {
        cout << "Enter source, target, and capacity of edge " << i+1 << ": ";
        cin >> s >> t >> capacity;
        graph[s][t] = capacity;
    }

    int source, sink;
    cout << "Enter source vertex: ";
    cin >> source;
    cout << "Enter sink vertex: ";
    cin >> sink;

    cout << "The maximum possible flow is " << fordFulkerson(graph, source, sink) << endl;
    
    return 0;
}
