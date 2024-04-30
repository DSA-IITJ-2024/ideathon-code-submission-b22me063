#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits> // Include this line instead of <climits>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Edge {
    int target;
    int weight;
    Edge(int t, int w) : target(t), weight(w) {}
};

vector<int> astar(const vector<vector<Edge>>& graph, int source, int target) {
    int n = graph.size();
    vector<int> distances(n, numeric_limits<int>::max()); // Use numeric_limits<int>::max() instead of INT_MAX
    vector<int> predecessors(n, -1);
    distances[source] = 0;

    auto heuristic = [](int node, int target) { return abs(node - target); };
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0 + heuristic(source, target), source});

    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();

        if (u == target) break;

        for (const auto& edge : graph[u]) {
            int v = edge.target;
            int w = edge.weight;
            int alt = distances[u] + w;
            if (alt < distances[v]) {
                distances[v] = alt;
                predecessors[v] = u;
                pq.push({alt + heuristic(v, target), v});
            }
        }
    }

    return predecessors;
}

void plotGraph(const vector<vector<Edge>>& graph, const vector<int>& predecessors, int source, int target) {
    cout << "Graph Visualization:\n";
    for (int i = 0; i < graph.size(); ++i) {
        cout << "Node " << i << ": ";
        for (const auto& edge : graph[i]) {
            cout << "(" << edge.target << ", " << edge.weight << ") ";
        }
        cout << endl;
    }

    vector<int> path;
    while (target != -1) {
        path.push_back(target);
        target = predecessors[target];
    }
    reverse(path.begin(), path.end());

    if (path.size() > 1) {
        cout << "Shortest Path: ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found to the target" << endl;
    }
}

int main() {
    vector<vector<Edge>> graph = {
        {{1, 1}, {2, 4}, {3, 5}, {4, 3}, {5, 2}},
        {{0, 1}, {2, 2}, {3, 2}, {4, 3}, {6, 4}},
        {{0, 4}, {1, 2}, {4, -3}, {5, 1}, {7, 2}},
        {{0, 5}, {1, 2}, {4, 1}, {5, 3}, {8, 4}},
        {{0, 3}, {1, 3}, {2, -3}, {3, 1}, {9, 2}},
        {{0, 2}, {2, 1}, {3, 3}, {6, 2}, {7, 1}},
        {{1, 4}, {5, 2}, {7, 3}, {8, 2}, {9, 3}},
        {{2, 2}, {5, 1}, {6, 3}, {8, 1}, {9, 4}},
        {{3, 4}, {6, 2}, {7, 2}, {9, 1}},
        {{4, 2}, {6, 3}, {7, 3}, {8, 4}}
    };

    int source = 0;
    int target = 9;

    vector<int> predecessors = astar(graph, source, target);
    plotGraph(graph, predecessors, source, target);

    return 0;
}


