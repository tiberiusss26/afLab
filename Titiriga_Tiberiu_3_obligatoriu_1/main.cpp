#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("maxflow.in");
ofstream g("maxflow.out");

int n, m, capacitate[1001][1001], viz[1001], flux[1001][1001], tata[1001];
vector<vector<int>> listaAd(1001);

bool bf() {
    queue<int> coada;
    coada.push(1);
    for (int i = 2; i <= n; i++)
        viz[i] = 0;
    viz[1] = 1;

    while (!coada.empty()) {
        int nod = coada.front();
        coada.pop();
        if (nod == n) continue;

        for (auto vec: listaAd[nod]) {
            if (capacitate[nod][vec] == flux[nod][vec] || viz[vec])continue;
            viz[vec] = 1;
            coada.push(vec);
            tata[vec] = nod;
        }
    }
    if (viz[n] == 1) return true;
    return false;
}

int main() {
    f >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y, c;
        f >> x >> y >> c;
        listaAd[x].push_back(y);
        listaAd[y].push_back(x);
        capacitate[x][y] = c;
    }

    int flow = 0, fmin;

    while (bf()) {
        for (auto vec: listaAd[n]) {
            if (capacitate[vec][n] == flux[vec][n] || !viz[vec]) continue;
            tata[n] = vec;

            fmin = 1e9;

            int nod = n;

            while (nod != 1) {
                fmin = min(fmin, capacitate[tata[nod]][nod] - flux[tata[nod]][nod]);
                nod = tata[nod];
            }

            if (fmin == 0) continue;

            nod = n;
            while (nod != 1) {
                flux[tata[nod]][nod] += fmin;
                flux[nod][tata[nod]] -= fmin;
                nod = tata[nod];
            }
            flow += fmin;
        }
    }
    g << flow;

    //Modificațialgoritmul de la punctul a) astfel încât să afișați tăietura minima între  sursa și  orice  alt vârf,
    // adică o mulțime de arce cu costul total minim pe care dacă le eliminăm din rețea cel puțin un vârf care era accesibil
    // inițial din sursă după eliminare nu mai este accesibil.

    vector<int> taietura;
    for (int i = 1; i <= n; i++) {
        if (viz[i] == 1)
            taietura.emplace_back(i);
    }
    for (auto it: taietura) {
        for (auto itt: listaAd[it]) {
            if (find(taietura.begin(), taietura.end(), itt) == taietura.end())
                cout << it << "," << it << " " << flux[it][itt] << "\n";
        }
    }
}