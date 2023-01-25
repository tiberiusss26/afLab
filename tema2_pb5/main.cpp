#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

ifstream fin("catun.in");
ofstream fout("catun.out");

void dijkstra(vector<vector<pair<int, int>>> listaAdiacenta, int n, set<int> &f, priority_queue<pair<int, int>> &q) {
    vector<int> d(n + 1, 1e5);
    vector<int> tata(n + 1, 0);
    for (int i = 1; i <= n; i++)
        tata[i] = i;
    for (auto it: f)
        d[it] = 0;
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        for (auto it: listaAdiacenta[x]) {
            if (d[x] + it.second < d[it.first]) {
                d[it.first] = d[x] + it.second;
                q.push(make_pair((-1)*d[it.first], it.first)); // inmultim cu -1 pentru a avea min-heap
                tata[it.first] = tata[x];
            } else if (d[x] + it.second == d[it.first]) { // daca au distantele egale pastram distanta
                if (tata[it.first] > tata[x])             // pana la fortareata cu nr cel mai mic de ordine
                    tata[it.first] = tata[x];
            }
        }
    }
    for (int i = 1; i <= n; i++)
        if (tata[i] != i)
            fout << tata[i] << " ";
        else fout<<0<<" ";
}

int main() {
    set<int> fortarete;
    int n, m, k, x;
    fin >> n >> m >> k;
    priority_queue<pair<int, int>> q;
    for (int i = 1; i <= k; i++) {
        fin >> x;
        fortarete.insert(x);
        q.push(make_pair(0, x)); // dist pana la o fortareata e 0
    }
    vector<vector<pair<int, int>>> listaAd(n + 1);
    int a, b, c;
    for (int i = 0; i < m; i++) {
        fin >> a >> b >> c;
        listaAd[a].push_back(make_pair(b, c));
        listaAd[b].push_back((make_pair(a, c)));
    }

    dijkstra(listaAd, n, fortarete, q);

}



