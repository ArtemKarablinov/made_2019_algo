
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

template<typename T>
class DSU{
private:
    vector<T> parent;
    vector<int> r; //rank
public:
    explicit DSU(int size):parent(size, -1), r(size, 0){};
    T find(T val);
    void merge(T left, T right);
};

template<typename T>
class myGraph{
private:
    vector<vector<T>> v;
    vector<std::tuple<T, T, T>> edges;
public:
    void AddEdge(int b, int e, T w);
    int MinWeight();
    explicit myGraph(T n, T m): v(n), edges(m){};
};

template<typename T>
void myGraph<T>::AddEdge(int b, int e, T w){
    v[b].push_back(e);
    v[e].push_back(b);
    edges.push_back(std::make_tuple(b, e, w));
}

template<typename T>
int myGraph<T>::MinWeight(){
    DSU<T> g(v.size());
    std::sort(edges.begin(), 
              edges.end(),
              [](const std::tuple<T, T, T> &mytuple1,
                 const std::tuple<T, T, T> &mytuple2){

                return std::get<2>(mytuple1) < std::get<2>(mytuple2); 
              });

    int w = 0;
    for (auto &edge : edges){
        T b = std::get<0>(edge);
        T e = std::get<1>(edge);
        T b_ = g.find(b);
        T e_ = g.find(e);

        if (e_ != b_){
            g.merge(b_, e_);
            w += std::get<2>(edge);
        }
    }
    return w;
}

template<typename T>
T DSU<T>::find(T val){
    if(parent[val] == -1)
        return val;
    return parent[val] = find(parent[val]);
}

template<typename T>
void DSU<T>::merge(T left, T right){
    const T d_left = find(left);
    const T d_right = find(right);

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
    myGraph<int> edges(n, m);

    for (int i=0; i<m; i++){
        int b, e, w;
        std::cin >> b >> e >> w;
        edges.AddEdge(b-1, e-1, w);
    }

    int result = edges.MinWeight();
    std::cout << result << std::endl;
    return 0;
}

