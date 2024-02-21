#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Function to perform BFS traversal
void BFS(vector<vector<int>>& graph, int startNode) {
    int numNodes = graph.size();
    vector<bool> visited(numNodes, false); // Array to keep track of visited nodes
    queue<int> q; // Queue for BFS traversal

    // Enqueue the starting node
    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        // Dequeue a node from the queue
        int currentNode = q.front();
        q.pop();

        // Process the dequeued node (e.g., print it)
        cout << currentNode << " ";

        // Enqueue all adjacent nodes of the dequeued node that are not yet visited
        for (int neighbor : graph[currentNode]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

int main() {
    int numNodes, numEdges;
    cout << "Enter the number of nodes and edges: ";
    cin >> numNodes >> numEdges;

    // Create adjacency list representation of the graph
    vector<vector<int>> graph(numNodes);

    cout << "Enter the edges (node u to node v):\n";
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        // For undirected graph, uncomment below line
        //graph[v].push_back(u);
    }

    int startNode;
    cout << "Enter the starting node for BFS traversal: ";
    cin >> startNode;

    cout << "BFS traversal starting from node " << startNode << ": ";
    BFS(graph, startNode);
    cout << endl;

    return 0;
}

