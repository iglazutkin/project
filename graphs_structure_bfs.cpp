#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <set>
#include <queue>
 
using namespace std;
 
enum Color {
    white,
    grey,
    black
};
 
struct Node {
    explicit Node(int _id) : id(_id), color(white) {}
 
    int id;
    Color color;
    std::set<int> neighbors;
};
 
struct Graph {
 
    void addNode(int id) {
        auto node = make_shared<Node>(id);
        nodes.insert(make_pair(id, node));
        std::cout << "\nNode " << id << " added.";
    }
 
    void removeNode(int targetId) {
        if (nodes.find(targetId) == nodes.end()) {
            std::cout << "\nNode " << targetId << " does not exist.";
            return;
        }
        for (auto &entry : nodes[targetId]->neighbors) {
            nodes[entry]->neighbors.erase(targetId);
            connections_count--;
        }
        nodes.erase(targetId);
        std::cout << "\nNode " << targetId << " removed.";
    }
 
    void addConnection(int node1, int node2) {
        bool exit = false;
        if (nodes.find(node1) == nodes.end()) {
            std::cout << "\nNode " << node1 << " does not exist.";
            exit = true;
        }
        if (nodes.find(node2) == nodes.end()) {
            std::cout << "\nNode " << node2 << " does not exist.";
            exit = true;
        }
        if (exit) return;
 
        nodes[node1]->neighbors.insert(node2);
        nodes[node2]->neighbors.insert(node1);
        std::cout << "\nConnection from " << node1 << " to " << node2 << " added.";
        connections_count++;
    }
 
    void removeConnection(int node1, int node2) {
        bool exit = false;
        if (nodes.find(node1) == nodes.end()) {
            std::cout << "\nNode " << node1 << " does not exist.";
            exit = true;
        }
        if (nodes.find(node2) == nodes.end()) {
            std::cout << "\nNode " << node2 << " does not exist.";
            exit = true;
        }
        if (exit) return;
 
        nodes[node1]->neighbors.erase(node2);
        nodes[node2]->neighbors.erase(node1);
        std::cout << "\nConnection from " << node1 << " to " << node2 << " removed.";
        connections_count--;
    }
 
    unsigned nodesCount() {
        return static_cast<unsigned int>(nodes.size());
    }
 
    unsigned connectionsCount() {
        return connections_count;
    }
 
    void cleanColors() {
        for (auto &node : nodes) {
            node.second->color = white;
        }
    }
 
    void bfs(int startId) {
        cleanColors();
        std::unordered_map<int, int> path;
        queue<int> q;
        q.push(startId);
        nodes[startId]->color = grey;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto &entry : nodes[cur]->neighbors) {
                if (nodes[entry]->color == white) {
                    nodes[entry]->color = grey;
                    q.push(entry);
                    path[entry] = cur;
                }
            }
        }
        std::cout << "\nPath: ";
        for (auto &entry : nodes) {
            std::cout << "\nto node " << entry.first << ": ";
            if (entry.second->color == white) {
                std::cout << "No path";
            } else {
                int curNode = entry.first;
                while (curNode != startId) {
                    std::cout << curNode << " <- ";
                    curNode = path[curNode];
                }
                std::cout << curNode << std::endl;
            }
        }
    }
 
private:
    std::unordered_map<int, std::shared_ptr<Node>> nodes;
    unsigned connections_count = 0;
};
 
int main() {
    Graph g;
    g.addNode(1);
    g.addNode(2);
    g.addNode(4);
    g.addNode(5);
    g.addNode(3);
    g.addNode(6);
    g.addConnection(1, 2);
    g.addConnection(2, 3);
    g.addConnection(2, 5);
    g.addConnection(5, 3);
    g.addConnection(5, 4);
    g.addConnection(1, 6);
    g.addConnection(5, 6);
    g.bfs(5);
 
    return 0;
}
