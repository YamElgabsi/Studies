//
// Created by YamEl on 5/19/2022.
//

#ifndef HW02_GRAPH_H
#define HW02_GRAPH_H

#include "memory"
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <set>
#include "MyWeight.h"

const int infinity = 2147483647;
const int undefined = -1;

using namespace std;

int find_min_unvisited(map<int,int> &dist, set<int> &unvisited); // helper function to Dijkstra

// Edge = {to,weight}
typedef std::pair<int,MyWeight> Edge;

typedef shared_ptr<map<int, pair<int,int>>> dijkstra_result ;

class Graph {
private:

    // ==Data Members==
    map<int, vector<Edge>> graph;
    int numOfNodes = 0;

public:
    //--The Big Five--
    Graph() = default;
    ~Graph() = default;
    Graph(const Graph& other) = delete;
    Graph& operator=(const Graph& other) = delete;
    Graph(const Graph&& other);

    //--Boolean Functions--
    bool containsVertex(int v);

    //--Manage Functions--
    bool addVertex(int v); //return false if v already in the graph
    bool removeVertex(int v); // return false if cant remove v
    int getEdge(int from, int to); //return 0 if the edge not exist
    bool addEdge(int from, int to, MyWeight weight, bool&& direct = false);//return false if from/to not in the graph or weight<=0, the function override the wight only if its smaller

    //--Functions--
    dijkstra_result Dijkstra(int source); // if the given argument is not in the graph will return nullptr;
    vector<Edge> getNeighbors(int source);
    Graph getReverse() const;
    int getMinDist(int source, int target); // if source/target not in the graph the function retun -1

    void printD(dijkstra_result& result);
    void print_graph();




};






#endif //HW02_GRAPH_H
