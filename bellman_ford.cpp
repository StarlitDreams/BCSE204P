#include <iostream>
#include <vector>
#include <climits>
#include <string> 

using namespace std;

struct Edge {
    int source;
    int target;
    int weight;
};

void BellmanFord(const vector<Edge>& edges, int V, int source) {
    vector<int> distance(V, INT_MAX);
    distance[source] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (const Edge& edge : edges) {
            if (distance[edge.source] != INT_MAX && distance[edge.source] + edge.weight < distance[edge.target]) {
                distance[edge.target] = distance[edge.source] + edge.weight;
            }
        }
    }

    for (const Edge& edge : edges) {
        if (distance[edge.source] != INT_MAX && distance[edge.source] + edge.weight < distance[edge.target]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    cout << "Vertex Distance from Source" << endl;
    for (int i = 0; i < V; ++i) {
        cout << i << "\t\t" << (distance[i] == INT_MAX ? "INF" : to_string(distance[i])) << endl;
    }
}

int main() {
    int V, E, source;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);
    for (int i = 0; i < E; i++) {
        cout << "Enter source, target, and weight of edge " << i + 1 << ": ";
        cin >> edges[i].source >> edges[i].target >> edges[i].weight;
    }

    cout << "Enter source vertex: ";
    cin >> source;

    BellmanFord(edges, V, source);

    return 0;
}
