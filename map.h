#ifndef MAP_H
#define MAP_H
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <functional> // for std::hash

struct pair_hash {                              //a hash function to implement the unordered_map correctly as it gave an error
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);  // Hash the first item
        auto hash2 = std::hash<T2>{}(pair.second); // Hash the second item

        // Combine the two hash values: this is one of many ways to do it
        return hash1 ^ (hash2 << 1);  // Shift and XOR
    }
};

class map
{
    private:
    std::unordered_map<std::pair<int, int>, std::vector<std::pair<std::pair<int , int>, int>>, pair_hash> graph;
    public:
        map();
        void addBlock(std::pair<int, int> id);          //adds a block or a possible path the player or enemy can move through
        void addEdge(std::pair<int, int> from, std::pair<int, int> to, int distance);       //adds edge between blocks, weight is always 1 can be adjusted if needed
        void findShortestPath(std::pair<int, int> from, std::pair<int, int> to, int& distance, std::vector<std::pair<int, int>>& path);     //applies Dijkstra's algorith to find the shortest path's distance and stores the path in a vector
        std::vector<std::pair<int, int>> getBlocks();
        std::vector<std::pair<std::pair<int, int>, int>> getEdges(std::pair<int, int> pathID);


};

#endif // MAP_H
