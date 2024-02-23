#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Vertex {
public:
    string name;
    int distance;
    bool visited;

    Vertex(string name) : name(name), distance(numeric_limits<int>::max()), visited(false) {}
};

class Edge {
public:
    Vertex* source;
    Vertex* destination;
    int weight;

    Edge(Vertex* source, Vertex* destination, int weight) : source(source), destination(destination), weight(weight) {}
};

class Graph {
public:
    vector<Vertex*> vertices;
    vector<Edge*> edges;

    void addVertex(string name) {
        vertices.push_back(new Vertex(name));
    }

    void addEdge(Vertex* source, Vertex* destination, int weight) {
        edges.push_back(new Edge(source, destination, weight));
    }

    void dijkstra(string sourceName) {
        Vertex* source = nullptr;
        for (Vertex* vertex : vertices) {
            if (vertex->name == sourceName) {
                source = vertex;
                break;
            }
        }

        if (source == nullptr) {
            cout << "Source vertex not found" << endl;
            return;
        }

        source->distance = 0;

        priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, greater<pair<int, Vertex*>>> pq;
        pq.push(make_pair(0, source));

        while (!pq.empty()) {
            Vertex* current = pq.top().second;
            pq.pop();

            if (current->visited) {
                continue;
            }

            current->visited = true;

            for (Edge* edge : edges) {
                if (edge->source == current) {
                    Vertex* neighbor = edge->destination;
                    int newDistance = current->distance + edge->weight;
                    if (newDistance < neighbor->distance) {
                        neighbor->distance = newDistance;
                        pq.push(make_pair(newDistance, neighbor));
                    }
                }
            }
        }
    }

    void printShortestPaths() {
        for (Vertex* vertex : vertices) {
            cout << "Shortest distance from source to vertex " << vertex->name << ": " << vertex->distance << endl;
        }
    }
};

int main() {
    Graph graph;

    // User input for vertices
    string vertexNames;
    cout << "Enter names of vertices separated by spaces: ";
    getline(cin, vertexNames);

    // Add vertices to the graph
    size_t pos = 0;
    string token;
    while ((pos = vertexNames.find(' ')) != string::npos) {
        token = vertexNames.substr(0, pos);
        graph.addVertex(token);
        vertexNames.erase(0, pos + 1);
    }
    if (!vertexNames.empty()) {
        graph.addVertex(vertexNames); // Add the last vertex
    }

    // User input for edges
    string source, destination;
    int weight;
    cout << "Enter edges in the format 'source destination weight', enter 'done' to finish:\n";
    while (true) {
        cin >> source;
        if (source == "done") {
            break;
        }
        cin >> destination >> weight;
        graph.addEdge(graph.vertices[source[0] - 'A'], graph.vertices[destination[0] - 'A'], weight);
    }

    // User input for source vertex
    string sourceName;
    cout << "Enter the source vertex: ";
    cin >> sourceName;

    graph.dijkstra(sourceName);

    cout << "Shortest distances from source vertex:" << endl;
    graph.printShortestPaths();

    return 0;
}
