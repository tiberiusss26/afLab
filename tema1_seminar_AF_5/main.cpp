#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("graf.in");
ofstream g("graf.out");

int n;
// facem un bfs pentru a afla drumul cel mai scurt al unui nod la un punct de control
int bfs(int nod, vector<vector<int>> listaAdiacenta, vector<int> pctControl) {
    vector<int> dist(n+1,0);  // vector de distanta pentru a ne putea afla care e distanta de la nod la pct de control
    for (auto it: pctControl) // daca nodul coincide cu punctul de control drumul este 0
        if (it == nod)
            return 0;
    vector<bool> visited(n + 1, false);
    queue<int> coadaBfs;
    coadaBfs.push(nod);
    visited[nod] = true;
    while (!coadaBfs.empty()) {
        nod = coadaBfs.front();
        coadaBfs.pop();
        for (auto vec: listaAdiacenta[nod]) {
            dist[vec] = dist[nod] +1; // distanta pana la vecin creste cu 1 fata de distanta pana la tata
            for (auto it: pctControl)
                if (it == vec)
                    return dist[vec];
            if (!visited[vec]) {
                visited[vec] = true;
                coadaBfs.push(vec);
            }
        }
    }
}

int main() {
    int m, x, y;
    vector<int> control;
    f >> n >> m;
    vector<vector<int>> listaAd(n + 1);
    for (int i = 0; i < m; i++) {
        f >> x >> y;
        listaAd[x].push_back(y);
        listaAd[y].push_back(x);
    }
    while (f >> x)
        control.push_back(x);

    for (int i = 1; i <= n; i++)
        cout << bfs(i, listaAd, control)<<" ";

}
