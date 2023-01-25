#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k) {
    vector<vector<pair<int, int>>> listaAd(n);
    for (auto it: flights) {
        listaAd[it[0]].push_back(make_pair(it[1], it[2]));
    }

    //pastram un max-heap cu distanta pana la un nod si nr de opriri pana la el
    //pentru cazul in care avem un drum mai bun dar e prea lung
    //si asa pastram drumul mai costisitor

    priority_queue<pair<int, pair<int, int>>> coadaa;
    vector<int> d(n, 1e9);
    d[src] = 0;



    coadaa.push(make_pair(0, make_pair(src, 0)));


    // facem dijkstra
    while (!coadaa.empty()) {
        int nod = coadaa.top().second.first;
        int kk = coadaa.top().second.second;
        int dist = coadaa.top().first;

        coadaa.pop();

        for(auto it: listaAd[nod]){
            //adaugam conditia suplimentara ca drumul pana la nod sa nu aiba mai multe opriri decat nr de opriri posibile
            if(dist+it.second< d[it.first] && kk  <= k){
                d[it.first] = dist + it.second;
                coadaa.push(make_pair(d[it.first], make_pair(it.first,kk+1)));
            }
        }
    }
    if (d[dst] != 1e9) // daca distanta e modificata inseamna ca exista un drum pana la destinatie si il returnam
        return d[dst];
    else return -1;


}

int main() {
    int n = 5, src = 0, dst = 4, k = 2;
    vector<vector<int>> flights = {{0, 1, 1},
                                   {0, 2, 5},
                                   {1, 2, 1},
                                   {2, 3, 1},
                                   {3, 4, 1}};
    cout << findCheapestPrice(n, flights, src, dst, k);

}
