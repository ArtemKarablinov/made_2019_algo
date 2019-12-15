#include <iostream>
#include <queue>


int BFS_solve(int start, int end, std::vector<std::vector<int> >& edges){
    std::queue<int> q;

    std::vector<int> dist(edges.size(), 66000);
    std::vector<bool> isVisited(edges.size(), false);
    std::vector<int> len_paths(edges.size(), 0);

    isVisited[start] = true;
    q.push(start);
    dist[start] = 0;
    len_paths[start] = 1;
    int d = 0;
    while (!q.empty()){
        int current = q.front();
        d = dist[current];
        q.pop();
        for (int i=0; i<edges[current].size(); ++i){
            int neigh = edges[current][i];
            if(!isVisited[neigh]){
                q.push(edges[current][i]);
                isVisited[neigh] = true;
                dist[neigh] = d+1;
                for (int j=0; j<edges[neigh].size(); ++j){
                    if (dist[edges[neigh][j]] < dist[neigh])
                        len_paths[neigh] += (int)len_paths[edges[neigh][j]];
                }
                if (neigh==end)
                    break;
            }
        }
    }
    return len_paths[end];
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