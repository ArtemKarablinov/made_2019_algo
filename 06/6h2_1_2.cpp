#include <iostream>
#include <queue>


int BFS_solve(int start, int end, std::vector<std::vector<int> >& edges){
    std::queue<int> q;

    std::vector<int> dist(edges.size(), 0);
    std::vector<bool> isVisited(edges.size(), false);
    std::vector<std::vector<int>> len_paths(edges.size());

    isVisited[start] = true;
    q.push(start);
    int d = 0;
    while (!q.empty()){
        int current = q.front();
        d = dist[current];
        q.pop();
        for (int i=0; i<edges[current].size(); i++){
            int neigh = edges[current][i];
            len_paths[neigh].push_back(d+1);
            if(!isVisited[neigh]){
                q.push(edges[current][i]);
                isVisited[neigh] = true;
                dist[neigh] = d+1;
            }
        }
    }

    int min_dist = dist[end];
    if (min_dist==0)
        return 0;
    int result = 0;
    for (int i=0; i<len_paths[end].size(); i++){
        if (len_paths[end][i]==min_dist)
            result++;

    }
    return result;
}

int main(){
    int n, k;
    std::cin>> n >> k;
    std:: vector<std::vector<int> > edges(k+1);
    int edge1, edge2;
    for (int i=0; i<k; i++){
        std::cin>>edge1 >> edge2;
        edges[edge1].push_back(edge2);
        edges[edge2].push_back(edge1);
    }
    int start, end;
    std::cin>>start >> end;
    int result = BFS_solve(start, end, edges);
    std::cout<< result << std::endl;
    return 0;
}