#include "map.h"
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>

map::map() {}

void map :: addBlock(std::pair<int, int> id)        //adds a possible path that enemies or player can move through
{
    graph[id];
}

void map :: addEdge(std::pair<int, int> from, std::pair<int, int> to, int distance)         //adds an edge between 2 blocks; weight is always 1 and can be changed if program needs
{
    if(from == to) return;

    auto &fromEdges = graph[from];
    bool found = false;
    for(auto it = fromEdges.begin(); it != fromEdges.end(); ++it) {
        if(it->first == to) {
            it->second = distance;
            found = true;
            break;
        }
    }

    if(!found) {
        fromEdges.push_back(make_pair(to, distance));
    }

    found = false;
    auto &toEdges = graph[to];
    for(auto it = toEdges.begin(); it != toEdges.end(); ++it) {
        if(it->first == from) {
            it->second = distance;
            found = true;
            break;
        }
    }

    if(!found) {
        toEdges.push_back(make_pair(from, distance));
    }
}


void map::findShortestPath(std::pair<int, int> from, std::pair<int, int> to, int& distance, std::vector<std::pair<int, int>>& path)         //applies Dijkstra to find the shortest path from start to goal
{
    std::unordered_map<std::pair<int, int>, int, pair_hash> dist;
    std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> prev;
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> pq;

    // Initialize distances
    for (auto &block : getBlocks()) {
        dist[block] = INT_MAX; // Use INT_MAX to represent infinity
        prev[block] = {-1, -1}; // Use an invalid pair to represent non-existence
    }
    dist[from] = 0;
    pq.push({0, from});

    while (!pq.empty()) {
        std::pair<int, int> u = pq.top().second;
        pq.pop();

        if (u == to) break;

        for (auto &neighbor : getEdges(u)) {
            std::pair<int, int> v = neighbor.first;
            int weight = neighbor.second;

            int alt_Path = dist[u] + weight;
            if (alt_Path < dist[v]) {
                dist[v] = alt_Path;
                prev[v] = u;
                pq.push({alt_Path, v});
            }
        }
    }

    // Build path
    path.clear();
    std::pair<int, int> current = to;
    while (current != std::pair<int, int>{-1, -1}) {
        path.push_back(current);
        current = prev[current];
    }
    std::reverse(path.begin(), path.end());

    // Set distance
    distance = dist[to];
}



std::vector<std::pair<int, int>> map :: getBlocks()         //returns a vector of the coordinates of the blocks
{
    std::vector<std::pair<int, int>> paths;
    for(const auto &kv : graph) {
        paths.push_back(kv.first);
    }
    return paths;
}

std::vector<std::pair<std::pair<int, int>, int>> map :: getEdges(std::pair<int, int> pathID)    //returns a vector of the edges
{
    return graph[pathID];
}
