#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("drumuri2.in");
ofstream g("drumuri2.out");

int n, m, e, flow = 0, fminn;
vector<vector<int>> listaAd, capacitate, flux;
vector<int> viz, tata;

bool bf() {
    queue<int> coada;
    coada.push(0);
    for (int i = 1; i <= 2 * n + 1; i++)
        viz[i] = 0;
    viz[0] = 1;

    while (!coada.empty()) {
        int nod = coada.front();
        coada.pop();
        if (nod == 2 * n + 1) continue;

        for (auto vec: listaAd[nod]) {
            if (capacitate[nod][vec] == flux[nod][vec] || viz[vec]) continue;

            viz[vec] = 1;
            coada.push(vec);
            tata[vec] = nod;
        }
    }
    if (viz[2 * n + 1] == 1) return true;
    return false;
}

int main() {
    f >> n >> m;

    listaAd.resize(2 * n + 2);
    viz.resize(2 * n + 2);
    tata.resize(2 * n + 2);
    vector<int> aux(2 * n + 2, 0);
    capacitate.clear();
    capacitate.resize(2 * n + 2, aux);
    flux.clear();
    flux.resize(2 * n + 2, aux);

    for (int i = 1; i <= m; i++) {
        int x, y;
        f >> x >> y;
        y += n;
        listaAd[x].push_back(y);
        listaAd[y].push_back(x);

        capacitate[x][y] = 1;
    }

    for (int i = 1; i <= n; i++) {
        listaAd[0].push_back(i);
        listaAd[i].push_back(0);

        listaAd[i].push_back(i + n);
        listaAd[i + n].push_back(i);

        listaAd[i + n].push_back(n * 2 + 1);
        listaAd[n * 2 + 1].push_back(i + n);

        capacitate[0][i] = 1;
        capacitate[i + n][i] = 1;
        capacitate[i + n][2 * n + 1] = 1;
    }

    vector<pair<int, int>> sol;
    while (bf()) {
        for (auto vec: listaAd[2 * n + 1]) {
            if (capacitate[vec][2 * n + 1] == flux[vec][2 * n + 1] || !viz[vec])continue;
            tata[2 * n + 1] = vec;

            fminn = 1e9;
            int nod = 2 * n + 1;

            while (nod != 0) {
                fminn = min(fminn, capacitate[tata[nod]][nod] - flux[tata[nod]][nod]);
                nod = tata[nod];
            }

            if (fminn == 0) continue;

            nod = 2 * n + 1;
            while (nod != 0) {
                flux[tata[nod]][nod] += fminn;
                flux[nod][tata[nod]] -= fminn;
                nod = tata[nod];

            }

            flow += fminn;
        }
    }
    cout << n-flow;
    g << flow << "\n";
    for (int i = 1; i <= n; i++) {
        for (auto it: listaAd[i]) {
            if (flux[i][it] == 1)
                g << i << " " << it - n << "\n";
        }
    }
    return 0;
}
