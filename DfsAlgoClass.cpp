#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

using namespace std;

class Graph {
    unordered_map<int, vector<int>> adjList;

public:
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void dfs(int start) {
        unordered_set<int> visited;
        dfsHelper(start, visited);
    }

private:
    void dfsHelper(int node, unordered_set<int>& visited) {
        visited.insert(node);
        cout << node << " "; // Print the node being visited

        for (int neighbor : adjList[node]) {
            if (visited.find(neighbor) == visited.end()) {
                dfsHelper(neighbor, visited);
            }
        }
    }
};

int main() {
    Graph g;
    int numEdges;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout << "Enter the edges (format: 'u v', where u -> v):\n";
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int startNode;
    cout << "Enter the starting node for DFS: ";
    cin >> startNode;

    cout << "DFS traversal starting from node " << startNode << ":\n";
    g.dfs(startNode);

    return 0;
}
