
/*
Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.

    Вариант 2. С помощью алгоритма Крускала.

Формат ввода

Первая строка содержит два натуральных числа n и m —
количество вершин и ребер графа соответственно (1 ≤ n ≤ 20000, 0 ≤ m ≤ 100000).
Следующие m строк содержат описание ребер по одному на строке.
Ребро номер i описывается тремя натуральными числами bi, ei и wi —
номера концов ребра и его вес соответственно (1 ≤ bi, ei ≤ n, 0 ≤ wi ≤ 100000). 

*/
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using std::vector;


class DSU{
private:
    vector<int> parent;
    vector<int> r; //rank
    int size;
public:
    explicit DSU(int size):parent(size, -1), r(size, 0){};
    int find(int val);
    void merge(int left, int right);
};


class myGraph{
private:
    vector<vector<int>> v;
    vector<std::tuple<int, int, int>> edges;
public:
    void AddEdge(int b, int e, int w);
    int MinWeight();
    explicit myGraph(int n, int m): v(n), edges(m){};
};

void myGraph::AddEdge(int b, int e, int w){
    v[b].push_back(e);
    v[e].push_back(b);
    edges.push_back(std::make_tuple(b, e, w));
}

int myGraph::MinWeight(){
    DSU g(v.size());
    std::sort(edges.begin(), 
              edges.end(),
              [](const std::tuple<int, int, int> &mytuple1,
                 const std::tuple<int, int, int> &mytuple2){

                return std::get<2>(mytuple1) < std::get<2>(mytuple2); 
              });

    int w = 0;
    for (auto &edge : edges){
        int b = std::get<0>(edge);
        int e = std::get<1>(edge);
        int b_ = g.find(b);
        int e_ = g.find(e);

        if (e_ != b_){
            g.merge(b_, e_);
            w += std::get<2>(edge);
        }
    }
    return w;
}

int DSU::find(int val){
    if(parent[val] == -1)
        return val;
    return parent[val] = find(parent[val]);
}

void DSU::merge(int left, int right){
    const int d_left = find(left);
    const int d_right = find(right);

    if (r[d_left] == r[d_right]){
        parent[d_right] = d_left;
        r[d_left]++;
    }
    else if(r[d_left] > r[d_right]){
        parent[d_right] = d_left;
    }
    else {
        parent[d_left] = d_right;
    }
}

int main(){
    int n, m;
    std::cin >> n >> m;
    myGraph edges(n, m);

    for (int i=0; i<m; i++){
        int b, e, w;
        std::cin >> b >> e >> w;
        edges.AddEdge(b-1, e-1, w);
    }

    int result = edges.MinWeight();
    std::cout << result << std::endl;
    return 0;
}

