#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <unordered_map>
#include <fstream>

using std::vector;
int counter;

std::set<int>& bridge_dfs(int v, 
                        int p,
                        int timer, 
                        vector<vector<int>> &edges, 
                        vector<bool> &isVisited, 
                        vector<int> &tin, 
                        vector<int> &fup, 
                        std::set<int> &b){
    isVisited[v] = true;
    tin[v] = fup[v] = timer++;
    for (int i=0; i<edges[v].size(); ++i){
        int to = edges[v][i];
        if (to==p)
            continue;
        if (isVisited[to])
            fup[v] = fup[v]<tin[to] ? fup[v]:tin[to];
        else {
            bridge_dfs(to, v, timer, edges, isVisited, tin, fup, b);
            fup[v] = fup[v]<fup[to] ? fup[v]:fup[to];
            if (fup[to] > tin[v]){
                // std::cout<< v << to <<std::endl;
                b.insert(v);
            }
        }
    }
    return b;
}


std::set<int>& solve_bridges(vector<vector<int>> &edges, std::set<int> &b){

    int timer = 0;
    int p = -1;
    vector<int> enter(edges.size());
    vector<int> ret(edges.size());
    vector<bool> isVisited(edges.size(), false);
    for (int i=0; i<edges.size(); i++)
        if (!isVisited[i])
            b = bridge_dfs(i, -1, timer, edges, isVisited, enter, ret, b);
    return b;
}



int main(){
    std::ifstream input("bridges.in");
    std::ofstream output("bridges.out");
    //число вершин и ребер
    int n, k;
    input >> n >> k;

    //std::cin >> n >> k;
    vector<vector<int>> edges(k);
    int v1, v2; // вершины
    for (int i=0; i < k; i++){
        input >> v1 >> v2;
        //std::cin >> v1 >> v2;
        edges[v1].push_back(v2);
        edges[v2].push_back(v1);
    }
    std::set<int> b;
    b = solve_bridges(edges, b);
    output << b.size() << std::endl;
    for (auto i:b){
        // std::cout << b.size() << std::endl;
        // std::cout << i << std::endl;
        output << i << " ";
    }
    output << std::endl;
    input.close();
    output.close();
}



