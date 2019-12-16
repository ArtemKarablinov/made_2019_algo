#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <unordered_map>
#include <fstream>

std::set<int>* DFS(std::vector<std::vector<int>> edges){
    int time = 0;
    std::vector<bool> isVisited(edges.size(), false);
    std::vector<size_t> color(edges.size(), 0);



}




int main(){
    std::ifstream input("bridges.in");
    std::ofstream output("bridges.out");
    //число вершин и ребер
    int n, k;
    std::in >> n >> k;

    std::vector<std::vector<int>> graph(n);
    std::set<int>* b; // ptr on set of bridges
    for (int i=0; i <= k; i++){
        int v1, v2; // вершины
        std::in >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
    b = DFS(graph);
}



