//
// Created by YamEl on 5/19/2022.
//


#include "Graph.h"


bool Graph::containsVertex(int v) {
    if (graph.find(v) == graph.end())   return false;
    return true;
}

int Graph::getEdge(int from, int to) {
    auto key = graph.find(from);
    if (key == graph.end())   return 0;
    if (graph.find(to) == graph.end())  return 0;

    for(auto edge: key->second){
        if (edge.first == to)   return edge.second.getWeight();
    }
    return 0;
}

bool Graph::addVertex(int v) {
    auto key = graph.find(v);
    if (key != graph.end())   return false;
    graph[v];
    numOfNodes++;
    return true;
}

bool Graph::removeVertex(int v) {
    auto key = graph.find(v);
    if (key == graph.end()) return false;
    graph.erase(key);
    numOfNodes--;
    return true;
}
int find_min_unvisited(map<int,int> &dist, set<int> &unvisited){
    int min = infinity, v = -1;
    for (auto iter = unvisited.begin(); iter != unvisited.end(); ++iter){
        if (min > dist[*iter]){
            min = dist[*iter];
            v = *iter;
        }
    }
    return v;
}

dijkstra_result Graph::Dijkstra(int source) {
    if (graph.find(source) == graph.end())  return nullptr;

    map<int,int> dist;
    map<int,int> prev;
    set<int> unvisited;

    for (auto iter = graph.begin(); iter != graph.end() ; ++iter) {
        dist[iter->first] = infinity;
        prev[iter->first] = undefined;
        unvisited.insert(iter->first);
    }

    dist[source] = 0;

    int min = find_min_unvisited(dist,unvisited);
    while ( min != -1){
        unvisited.erase(min);
        for(auto iter = graph[min].begin(); iter != graph[min].end(); ++iter){
            auto neighbor = iter->first;
            int alt;
            dist[min] == infinity? alt = infinity : alt = dist[min]+iter->second.getWeight();
            if (alt < dist[neighbor]){
                dist[neighbor] = alt;
                prev[neighbor] = min;
            }
        }
        min = find_min_unvisited(dist,unvisited);
    }
    dijkstra_result result = make_shared<map<int, pair<int,int>>>( map<int, pair<int,int>>());
    for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
        (*result)[iter->first] = {dist[iter->first], prev[iter->first]};
    }

    return result;






}

void Graph::print_graph() {
    cout << "== Graph ==" << endl;
    for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
        cout << "Vertex: " << iter->first << ": ";
        auto neighbors = iter->second;
        for (auto neighbor = neighbors.begin(); neighbor != neighbors.end(); ++neighbor) {
            cout << "( " << neighbor->first << " , " << neighbor->second << " )";
        }
        cout << endl;
    }

}

bool Graph::addEdge(int from, int to, MyWeight weight, bool&& direct) {
    auto key = graph.find(from);
    if (key == graph.end())   return false;
    if (graph.find(to) == graph.end())  return false;
    if (weight <= 0)       return false;

    bool found = false;

    for( auto iter = graph[from].begin(); iter != graph[from].end(); ++iter){
        if (iter->first == to){
            if (iter->second > weight)
                iter->second = weight;
            found = true;
            break;
        }
    }
    if (!found) graph[from].push_back({to,weight});

    if (direct){
        found = false;
        for( auto iter = graph[to].begin(); iter != graph[to].end(); ++iter){
            if (iter->first == from){
                iter->second = weight;
                found = true;
            }
        }
        if(!found)  graph[to].push_back({from,weight});
    }
    return true;
}

void Graph::printD(dijkstra_result& result) {
    for(auto iter = result->begin(); iter != result->end(); ++iter){
        cout << iter->first << "-> D:" << iter->second.first << " , F:" << iter->second.second << endl;
    }

}

vector<Edge> Graph::getNeighbors(int source) {
    auto key = graph.find(source);
    if (key == graph.end())   return {};

    return graph[source];
}

Graph Graph::getReverse() const {
    Graph reverse;

    for(const auto & v : this->graph){
        reverse.addVertex(v.first);
    }

    for(const auto & v : this->graph){
        for( const auto& e : v.second){
            reverse.addEdge(e.first, v.first, e.second);
        }
    }

    return reverse;


}

Graph::Graph(const Graph &&other) {
    this->numOfNodes = other.numOfNodes;
    this->graph = other.graph;
}

int Graph::getMinDist(int source, int target) {
    auto key = graph.find(source);
    if (key == graph.end())   return -1;
    key = graph.find(target);
    if (key == graph.end())   return -1;

    dijkstra_result res = Dijkstra(source);
    for(auto & iter : *res) {
        if (iter.first == target) return iter.second.first;
    }
    return -1;//the program never be at this line
}
