#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

ifstream fin("dbz.in");
ofstream fout("dbz.out");

vector<pair<long long, long long>>a[1502];
priority_queue<pair<long long,long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> heap; ///pastram un min-heap
vector<pair<int,int>>listaAd[1501];
vector<int>dist(1501);
vector<int>parinte(1501);

int n, m, x, y, z, durata_min, val_max=1e9;

void reinitializare()
{
    for(int i=1; i<=n; i++){
        dist[i] = val_max;
        parinte[i] = 0;
    }
    durata_min = val_max;
}

int dijkstra(int start){
    reinitializare();
    for(auto v: listaAd[start]){
        parinte[v.first] = v.first;
        dist[v.first] = v.second;
        heap.push({v.second, v.first});
    }
    dist[start]=0;
    while(!heap.empty()){
        int node = heap.top().second;
        int dist_node = heap.top().first;
        heap.pop();
        if(dist_node >= dist[node]) {
            for (auto i: listaAd[node]) {
                int V = i.first;
                int durataV = i.second;
                if (dist[node] + durataV < dist[V]) {
                    dist[V] = dist[node] + durataV;
                    parinte[V] = parinte[node];
                    heap.push({dist[V], V});
                }
            }
        }
    }
    for(int i=1; i<=n; i++){
        for(auto neighbour: listaAd[i]){
            if((parinte[neighbour.first] != parinte[i]) && (i != start || parinte[neighbour.first] != neighbour.first) && (neighbour.first != start || parinte[i] != i)) {
                int d= dist[i] + neighbour.second + dist[neighbour.first];
                durata_min = min(durata_min, d);
            }
        }
    }
    if(durata_min != val_max)
        return durata_min;
    else
        return -1;

}


int main(){
    fin>>n>>m;
    for(int i=0; i<m; i++){
        fin >> x >> y >> z;
        listaAd[x].push_back({y, z});
        listaAd[y].push_back({x, z});
    }
    for(int i=1; i<=n; i++)
        fout<<dijkstra(i)<<" ";
    return 0;
}