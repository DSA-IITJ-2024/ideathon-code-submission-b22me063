#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int source, target, weight;
};

vector<int> bellmanFord(int nodes, vector<Edge>& edges, int source, int target) {
    vector<int> distances(nodes, numeric_limits<int>::max());
    vector<int> predecessors(nodes, -1);
    distances[source] = 0;

    for (int i = 0; i < nodes - 1; ++i) {
        for (const Edge& edge : edges) {
            if (distances[edge.source] + edge.weight < distances[edge.target]) {
                distances[edge.target] = distances[edge.source] + edge.weight;
                predecessors[edge.target] = edge.source;
            }
        }
    }

    for (const Edge& edge : edges) {
        if (distances[edge.source] + edge.weight < distances[edge.target]) {
            throw runtime_error("Graph contains a negative cycle");
        }
    }

    return distances;
}

void plotGraph(const vector<Edge>& edges, const vector<int>& distances, const vector<int>& predecessors, const string& algorithmName, int target) {
    // Your plotting code here (not available in C++)
}

int main() {
    int nodes = 10;
    vector<Edge> edges = {
        {0, 1, 1}, {0, 2, 4}, {0, 3, 5}, {0, 4, 3}, {0, 5, 2},
        {1, 0, 1}, {1, 2, 2}, {1, 3, 2}, {1, 4, 3}, {1, 6, 4},
        {2, 0, 4}, {2, 1, 2}, {2, 4, -3}, {2, 5, 1}, {2, 7, 2},
        {3, 0, 5}, {3, 1, 2}, {3, 4, 1}, {3, 5, 3}, {3, 8, 4},
        {4, 0, 3}, {4, 1, 3}, {4, 2, -3}, {4, 3, 1}, {4, 9, 2},
        {5, 0, 2}, {5, 2, 1}, {5, 3, 3}, {5, 6, 2}, {5, 7, 1},
        {6, 1, 4}, {6, 5, 2}, {6, 7, 3}, {6, 8, 2}, {6, 9, 3},
        {7, 2, 2}, {7, 5, 1}, {7, 6, 3}, {7, 8, 1}, {7, 9, 4},
        {8, 3, 4}, {8, 6, 2}, {8, 7, 1}, {8, 9, 3},
        {9, 4, 2}, {9, 6, 3}, {9, 7, 3}, {9, 8, 4}
    };

    int source = 0;
    int target = 9;
    string edgeColor = "blue";
    try {
        vector<int> distances = bellmanFord(nodes, edges, source, target);
        plotGraph(edges, distances, vector<int>(), "Bellman-Ford", target);
        cout << "Shortest distances (Bellman-Ford): ";
        for (int d : distances) {
            cout << d << " ";
        }
        cout << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Identify and visualize the negative cycle
    bool hasNegativeCycle = false;
    for (const Edge& edge : edges) {
        if (edge.weight < 0) {
            hasNegativeCycle = true;
            break;
        }
    }
    if (hasNegativeCycle) {
        cout << "Graph contains a negative cycle" << endl;
    } else {
        cout << "Graph does not contain a negative cycle" << endl;
    }

    return 0;
}