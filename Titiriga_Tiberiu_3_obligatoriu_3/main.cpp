#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("harta.in");
ofstream g("harta.out");

vector<vector<int>> listaAd(202);
int n, capacitate[202][202], flux[202][202], viz[202], tata[202];

bool bf() {
    queue<int> coada;
    coada.push(0);
    for (int i = 1; i <= 2 * n + 1; i++)
        viz[i] = 0;
    viz[0] = 1;

    while (!coada.empty()) {
        int nod = coada.front();
        coada.pop();
        if (nod == 2*n+1) continue;

        for (auto vec: listaAd[nod]) {
            if (capacitate[nod][vec] == flux[nod][vec] || viz[vec])continue;
            viz[vec] = 1;
            coada.push(vec);
            tata[vec] = nod;
        }
    }
    if (viz[2 * n + 1] == 1) return true;
    return false;
}

int main() {
    f >> n;
    queue<int> yy;

    for (int i = 1; i <= n; i++) {
        int x, y;
        f >> x >> y;
        yy.push(y);
        listaAd[0].push_back(i);
        listaAd[i].push_back(0);
        capacitate[0][i] = x;
    }

    for (int i = n + 1; i <= 2 * n; i++) {
        int y = yy.front();
        yy.pop();
        for (int j = 1; j <= n; j++) {
            if (j != i - n) {
                listaAd[j].push_back(i);
                listaAd[i].push_back(j);
                capacitate[j][i] = 1;
            }
        }
        listaAd[i].push_back(2 * n + 1);
        listaAd[2 * n + 1].push_back(i);
        capacitate[i][2 * n + 1] = y;

    }
    int fmin, flow = 0;

    while (bf()) {
        for (auto vec: listaAd[2 * n + 1]) {
            if (capacitate[vec][2 * n + 1] == flux[vec][2 * n + 1] || !viz[vec]) continue;
            tata[2 * n + 1] = vec;

            fmin = 1e9;

            int nod = 2*n+1;

            while(nod!=0){
                fmin = min(fmin, capacitate[tata[nod]][nod]-flux[tata[nod]][nod]);
                nod = tata[nod];
            }

            if(fmin == 0) continue;

            nod = 2*n+1;

            while(nod!=0){
                flux[tata[nod]][nod] += fmin;
                flux[nod][tata[nod]] -= fmin;
                nod = tata[nod];
            }
            flow+=fmin;
        }
    }
    g<<flow<<"\n";
    for(int i =1;i<=n;i++){
        for(int j=n+1;j<=2*n;j++)
            if(flux[i][j]==1)
                g<<i<<" "<<j-n<<"\n";
    }
}