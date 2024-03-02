#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Class representing a directed edge
class Edge {
public:
    int source, destination, weight;
    Edge(int source, int destination, int weight) : source(source), destination(destination), weight(weight) {}
};

// Class representing a weighted directed graph
class Graph {
public:
    int V, E; // Number of vertices and edges
    vector<Edge> edges; // Vector to store edges

    // Constructor
    Graph(int V, int E) : V(V), E(E) {}

    // Add an edge to the graph
    void addEdge(int source, int destination, int weight) {
        edges.push_back(Edge(source, destination, weight));
    }

    // Function to perform Bellman-Ford algorithm
    void bellmanFord(int source) {
        vector<int> distance(V, numeric_limits<int>::max()); // Initialize distances to infinity
        distance[source] = 0; // Distance from source to itself is 0

        // Relax all edges |V| - 1 times
        for (int i = 0; i < V - 1; ++i) {
            for (const auto& edge : edges) {
                int u = edge.source;
                int v = edge.destination;
                int w = edge.weight;
                if (distance[u] != numeric_limits<int>::max() && distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                }
            }
        }

        // Check for negative-weight cycles
        for (const auto& edge : edges) {
            int u = edge.source;
            int v = edge.destination;
            int w = edge.weight;
            if (distance[u] != numeric_limits<int>::max() && distance[u] + w < distance[v]) {
                cout << "Graph contains negative weight cycle" << endl;
                return;
            }
        }

        // Print distances from source
        cout << "Vertex   Distance from Source" << endl;
        for (int i = 0; i < V; ++i) {
            cout << i << "\t\t" << distance[i] << endl;
        }
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    Graph graph(V, E);

    cout << "Enter edges (source, destination, weight):" << endl;
    for (int i = 0; i < E; ++i) {
        int source, destination, weight;
        cin >> source >> destination >> weight;
        graph.addEdge(source, destination, weight);
    }

    int source;
    cout << "Enter source vertex: ";
    cin >> source;

    graph.bellmanFord(source);

    return 0;
}
