/*


Ребро неориентированного графа называется мостом, 
если удаление этого ребра из графа увеличивает число компонент связности.
Дан неориентированный граф, требуется найти в нем все мосты.

Формат ввода
Первая строка входного файла содержит два целых числа n и m — количество вершин и
ребер графа соответственно (1 ≤ n ≤ 20000, 1 ≤ m ≤ 200000).
Следующие m строк содержат описание ребер по одному на строке. 
Ребро номер i описывается двумя натуральными числами bi, ei — номерами концов ребра (1 ≤ bi, ei ≤ n).

*/
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <unordered_set>

using std::vector;

std::set<std::string>& bridge_dfs(int v, 
                                  int p,
                                  int timer, 
                                  vector<vector<int>> &edges, 
                                  vector<bool> &isVisited, 
                                  vector<int> &tin, 
                                  vector<int> &fup, 
                                  std::set<std::string> &b){
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
                b.insert(std::to_string(v) + "_" + std::to_string(to));
            }
        }
    }
    return b;
}


std::set<std::string>& solve_bridges(vector<vector<int>> &edges, std::set<std::string> &b){

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
    std::ifstream input("bridges1.in");
    std::ofstream output("bridges.out");
    //число вершин и ребер
    int n, k;
    input >> n >> k;

    vector<vector<int>> edges(k+1);
    std::vector<std::string> in_order;
    int v1, v2; // вершины
    for (int i=0; i < k; i++){
        input >> v1 >> v2;
        edges[v1].push_back(v2);
        edges[v2].push_back(v1);
        in_order.push_back(std::to_string(v1)+ "_" + std::to_string(v2));
    }
    std::set<std::string> b;
    std::set<int> res;
    b = solve_bridges(edges, b);
    for (auto i=0; i<in_order.size(); i++){
        if (b.find(in_order[i])!=b.end())
            res.insert(i+1);
    }
    output << b.size() << std::endl;
    for (auto i:res){
        std::cout << i << std::endl;
        output << i << " ";
    }
    output << std::endl;
    input.close();
    output.close();
}



