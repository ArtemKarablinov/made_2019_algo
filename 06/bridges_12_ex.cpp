#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <unordered_map>
#include <fstream>

using std::vector;

void bridge_dfs(int v, 
                int p,
                int timer, 
                vector<vector<int>> &edges, 
                vector<bool> &isVisited, 
                vector<int> &tin, 
                vector<int> &fup){
    isVisited[v] = true;
    tin[v] = fup[v] = timer++;
    for (int i=0; edges[v].size(); ++i){
        int to = edges[v][i];
        if (to==p)
            continue;
        if (isVisited[to])
            fup[v] = fup[v]<tin[to] ? fup[v]:tin[to];
        else {
            bridge_dfs(to, v, timer, edges, isVisited, tin, fup);
            fup[v] = fup[v]<fup[to] ? fup[v]:fup[to];
            if (fup[to] > tin[v])
                std::cout<< v << to <<std::endl;
        }
    }

}


void solve_bridges(std::vector<std::vector<int>> &edges){
    int timer = 0;
    int p = -1;
    std::vector<int> enter(edges.size());
    std::vector<int> ret(edges.size());
    // std::vector<size_t> color(edges.size(), 0);
    std::vector<bool> isVisited(edges.size(), false);
    for (int i=0; i<edges.size(); i++)
        if (!isVisited[i])
            bridge_dfs(i, p, timer, edges, isVisited, enter, ret);
}



int main(){
    // std::ifstream input("bridges.in");
    // std::ofstream output("bridges.out");
    //число вершин и ребер
    int n, k;
    // input >> n >> k;

    std::cin >> n >> k;
    std::vector<std::vector<int>> edges(k);
    // std::set<int>* b; // ptr on set of bridges
    int v1, v2; // вершины
    for (int i=0; i < k; i++){
        //input >> v1 >> v2;
        std::cin>>v1 >> v2;
        edges[v1].push_back(v2);
        edges[v2].push_back(v1);
    }
    solve_bridges(edges);
}



