#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int target;
    int weight;
    
    Edge(int t, int w) : target(t), weight(w) {}
};

struct Node {
    int id;
    vector<Edge> neighbors;
    int distance;
    bool visited;
    
    Node(int i) : id(i), distance(numeric_limits<int>::max()), visited(false) {}
};

class Graph {
public:
    vector<Node> nodes;
    
    Graph(int n) {
        nodes.reserve(n);
        for (int i = 0; i < n; ++i) {
            nodes.emplace_back(i);
        }
    }
    
    void addEdge(int source, int target, int weight) {
        nodes[source].neighbors.emplace_back(target, weight);
    }
    
    void dijkstra(int source) {
        nodes[source].distance = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, source});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            if (nodes[u].visited) {
                continue;
            }
            nodes[u].visited = true;
            
            for (const Edge& edge : nodes[u].neighbors) {
                int v = edge.target;
                int weight = edge.weight;
                
                if (!nodes[v].visited && nodes[u].distance + weight < nodes[v].distance) {
                    nodes[v].distance = nodes[u].distance + weight;
                    pq.push({nodes[v].distance, v});
                }
            }
        }
    }
    
    int getShortestDistance(int target) {
        return nodes[target].distance;
    }
};

int main() {
    int n = 10; // Number of nodes
    Graph graph(n);
    
    // Add edges to the graph
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(0, 3, 5);
    graph.addEdge(0, 4, 3);
    graph.addEdge(0, 5, 2);
    graph.addEdge(1, 6, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 3);
    // Add remaining edges similarly...

    int source = 0;
    int target = 9;

    graph.dijkstra(source);
    int shortestDistance = graph.getShortestDistance(target);

    cout << "Shortest distance from node " << source << " to node " << target << ": " << shortestDistance << endl;

    return 0;
}