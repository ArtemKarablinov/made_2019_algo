#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <unordered_map>
#include <fstream>

int main(){
    std::ifstream input("bridges.in");
    std::ofstream output("bridges.out");
    //число вершин и ребер
    int n, k;
    std::in >> n >> k;

    std::vector<std::vector<int>> graph(n);
    std::unordered_map<std::string, std::pair<int, bool> > edges{};
    set<int> b; // set of bridges
    for (auto i=0; i < k; i++){
        int v1, v2; // вершины
        std::in >> v1 >> v2;
        
    }
}



