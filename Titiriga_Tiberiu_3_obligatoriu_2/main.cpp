#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("cuplaj.in");
ofstream g("cuplaj.out");

int n, m, e,flow= 0,fminn;
vector<vector<int>> listaAd, capacitate, flux;
vector<int> viz,tata;

bool bf(){
    queue<int> coada;
    coada.push(0);
    for(int i =1;i<=n+m+1;i++)
        viz[i] = 0;
    viz[0] = 1;

    while(!coada.empty()){
        int nod = coada.front();
        coada.pop();
        if(nod == n+m+1) continue;

        for(auto vec:listaAd[nod]){
            if(capacitate[nod][vec]==flux[nod][vec] || viz[vec]) continue;

            viz[vec] = 1;
            coada.push(vec);
            tata[vec] = nod;
        }
    }
    if(viz[n+m+1]==1) return true;
    return false;
}

int main() {
    f >> n >> m >> e;

    listaAd.resize(n + m + 2);
    viz.resize(n + m + 2);
    tata.resize(n + m + 2);
    vector<int> aux(n + m + 2, 0);
    capacitate.clear();
    capacitate.resize(n + m + 2, aux);
    flux.clear();
    flux.resize(n + m + 2, aux);

    for (int i = 1; i <= e; i++) {
        int x, y;
        f >> x >> y;
        y += n;
        listaAd[x].push_back(y);
        listaAd[y].push_back(x);
        listaAd[0].push_back(x);
        listaAd[x].push_back(0);
        listaAd[y].push_back(n + m + 1);
        listaAd[n + m + 1].push_back(y);

        capacitate[x][y] = 1;
        capacitate[0][x] = 1;
        capacitate[y][n + m + 1] = 1;
    }

    vector<pair<int, int>> sol;
    while (bf()) {
        for (auto vec: listaAd[n + m + 1]) {
            if (capacitate[vec][n + m + 1] == flux[vec][n + m + 1] || !viz[vec])continue;
            tata[n + m + 1] = vec;

            fminn = 1e9;
            int nod = n + m + 1;

            while (nod != 0) {
                fminn = min(fminn, capacitate[tata[nod]][nod] - flux[tata[nod]][nod]);
                nod = tata[nod];
            }

            if (fminn == 0) continue;

            nod = n + m + 1;
            while (nod != 0) {
                flux[tata[nod]][nod] += fminn;
                flux[nod][tata[nod]] -= fminn;
                nod = tata[nod];

            }

            flow += fminn;
        }
    }

    g << flow << "\n";
    for (int i = 1; i <= n; i++) {
        for (auto it: listaAd[i]) {
            if (flux[i][it] == 1)
                g << i << " " << it - n << "\n";
        }
    }
    return 0;
}