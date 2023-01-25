#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("easygraph.in");
ofstream fout("easygraph.out");

int t,n,m;
vector<int> v, d;
vector<long long> dd;
vector<vector<int>> listaAd;
queue<int> coada;

// avem de a face cu un DAG deci in timpul sortarii topologice
// actualizam si distantele
// daca distanta pana intr un nod e mai mare decat maximul, acutalizam maximul


void sortareTopologica( int n, long long &maxim) {
    for (int i = 1; i <= n; i++)
        if (d[i] == 0) { // nodurile cu grad intern 0 intra in coada
            coada.push(i);
        }
    while (!coada.empty()) {
        int x = coada.front();
        coada.pop();
        for (auto it: listaAd[x]) {
            if (v[it] + dd[x] > dd[it]) {
                dd[it] = dd[x] + v[it];
                if (maxim < dd[it])
                    maxim = dd[it];
            }
            d[it]--;
            if (d[it] == 0)
                coada.push(it);
        }
    }
}

int main() {
    fin >> t;
    for (int i = 1; i <= t; i++) {
        long long max = -1e10;
        fin >> n >> m;
        v.clear();
        d.clear();
        dd.clear();
        listaAd.clear();
        listaAd.resize(n + 1);
        v.resize(n + 1);
        d.resize(n + 1,0);
        dd.resize(n + 1);
        for (int j = 1; j <= n; j++) {
            fin >> v[j];
            dd[j] = v[j];
            if(max < dd[j])
                max = dd[j];
        }

        for (int j = 1; j <= m; j++) {
            int x, y;
            fin >> x >> y;
            listaAd[x].push_back(y);
            d[y]++; // crestem gradul intern
        }
        for (int j = 1; j <= n; j++)
            dd[j] = v[j];

        sortareTopologica(n,max);

        fout << max << "\n";


    }
}
