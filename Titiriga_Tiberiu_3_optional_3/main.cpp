#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("noprime.in");

int prim(int n) {
    for (int d = 2; d * d <= n; d++)
        if (!(n % d)) return false;
    return true;
}

int n,s,t, flow = 0, fminn;
vector<vector<int>> listaAd, capacitate;
vector<int> viz, tata, numere, sol;

bool bf() {
    queue<int> coada;
    coada.push(s);
    for (int i = 0; i <= n + 1; i++) {
        viz[i] = 0;
        tata[i] = 0;
    }
    viz[s] = 1;
    tata[s] = 0;

    while (!coada.empty()) {
        int nod = coada.front();
        coada.pop();
        if (nod == t) return true;

        for (auto vec: listaAd[nod]) {
            if (capacitate[nod][vec] > 0 && viz[vec] == 0) {
                viz[vec] = 1;
                coada.push(vec);
                tata[vec] = nod;
            }
        }
    }
    return viz[t];
}

int main() {
    f >> n;
    s=0,t=n+1;

    listaAd.resize(n + 2);
    numere.resize(n+2);
    viz.resize(n + 2);
    tata.resize(n + 2);
    vector<int> aux(n + 2, 0);
    capacitate.clear();
    capacitate.resize(n + 2, aux);


    for (int i = 1; i <= n; i++) {
        f >> numere[i];
        if (numere[i] % 2 == 0) {  // le pastram pe cele pare in stanga
            listaAd[0].push_back(i);
            listaAd[i].push_back(0);
            capacitate[0][i] = 1;
        } else { // cele impare in dreapta
            listaAd[i].push_back(n + 1);
            listaAd[n + 1].push_back(i);
            capacitate[i][n + 1] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (prim(numere[i] + numere[j])) {
                listaAd[i].push_back(j);
                listaAd[j].push_back(i);
                if (numere[i] % 2 == 0)
                    capacitate[i][j] = 1;
                else
                    capacitate[j][i] = 1;
            }
        }
    }

    while (bf()) {
        for (auto vec: listaAd[t]) {
            if (capacitate[vec][t] > 0 && viz[vec]) {
                tata[t] = vec;

                fminn = 1e9;
                int nod = t;

                while (nod != 0) {
                    fminn = min(fminn, capacitate[tata[nod]][nod]);
                    nod = tata[nod];
                }

                if (fminn == 0) continue;

                nod = t;
                while (nod != 0) {
                    capacitate[tata[nod]][nod] -= fminn;
                    capacitate[nod][tata[nod]] += fminn;
                    nod = tata[nod];

                }

                flow += fminn;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!viz[i] && numere[i] % 2 == 0 || viz[i] && numere[i] % 2 == 1)
            sol.push_back(numere[i]);
    }
    cout << sol.size() << '\n';
    for (auto i: sol) {
        cout << i << " ";
    }
    return 0;

}
