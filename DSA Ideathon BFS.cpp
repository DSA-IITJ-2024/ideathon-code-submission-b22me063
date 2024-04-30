#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <algorithm>

using namespace std;

struct Node {
    int id;
    vector<Node*> neighbors;
};

pair<vector<int>, int> bfsShortestPath(unordered_map<int, Node*>& graph, int source, int target) {
    unordered_map<int, int> distances;
    unordered_map<int, int> predecessors;
    deque<Node*> queue;

    queue.push_back(graph[source]);
    distances[source] = 0;
    predecessors[source] = -1;

    while (!queue.empty()) {
        Node* current = queue.front();
        queue.pop_front();

        if (current->id == target) {
            break;
        }

        for (Node* neighbor : current->neighbors) {
            if (distances.find(neighbor->id) == distances.end()) {
                distances[neighbor->id] = distances[current->id] + 1;
                predecessors[neighbor->id] = current->id;
                queue.push_back(neighbor);
            }
        }
    }

    if (distances.find(target) == distances.end()) {
        return make_pair(vector<int>(), -1);
    }

    vector<int> path;
    int current = target;
    while (current != -1) {
        path.push_back(current);
        current = predecessors[current];
    }
    reverse(path.begin(), path.end());

    return make_pair(path, distances[target]);
}

int main() {
    unordered_map<int, Node*> graph;
    for (int i = 0; i < 10; ++i) {
        graph[i] = new Node{i};
    }

    vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5},
        {1, 6}, {1, 2}, {1, 3}, {1, 4},
        {2, 7}, {2, 3}, {2, 4},
        {3, 8}, {3, 4},
        {4, 9},
        {5, 6}, {5, 7},
        {6, 8}, {6, 9},
        {7, 8}, {7, 9},
        {8, 9}
    };

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        graph[u]->neighbors.push_back(graph[v]);
    }

    int source = 0;
    int target = 9;

    auto result = bfsShortestPath(graph, source, target);

    cout << "Shortest distance using BFS: " << result.second << endl;
    
    return 0;
}