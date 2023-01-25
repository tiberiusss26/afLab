#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

ifstream fin("transport2.in");
ofstream fout("transport2.out");

int dijkstra(vector<vector<pair<int, int>>> listaAdiacenta, int n) {
    vector<int> dist(n+1, -1);

    dist[1] = 1e9;

    priority_queue<pair<int, int>> heap;

    heap.push(make_pair(1e9, 1));

    while (!heap.empty()) {
        int nod = heap.top().second;
        if (nod == n) return heap.top().first;

        heap.pop();

        for (auto vec: listaAdiacenta[nod]) {
            if (dist[vec.first] < min(dist[nod],vec.second)) {
                dist[vec.first] = min(dist[nod], vec.second);
                heap.push(make_pair(dist[vec.first],vec.first));
            }
        }
    }
    return -1;
}

int main() {
    int n, m;
    fin >> n >> m;
    priority_queue<pair<int, int>> q;
    vector<vector<pair<int, int>>> listaAd(n + 1);
    int a, b, c;
    for (int i = 0; i < m; i++) {
        fin >> a >> b >> c;
        listaAd[a].push_back(make_pair(b, c));
        listaAd[b].push_back((make_pair(a, c)));
    }

    fout<<dijkstra(listaAd, n);

}



