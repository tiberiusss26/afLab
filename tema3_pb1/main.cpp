#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("fmcm.in");
ofstream g("fmcm.out");

int n, m, s, d, F=0, Fcst = 0;
vector<vector<int>> gph(355);
int capacitate[355][355], cost[355][355], p[355], distInitiala[355], distanta[355], distReala[355];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > heap;


inline bool dijkstra() {
    for (int i = 1; i <= n; i++)
        distanta[i] = 1e9;
    distanta[s] = 0;
    distReala[s] = 0;

    heap.push(make_pair(0, s));

    while (!heap.empty()) {
        int dd = heap.top().first;
        int nod = heap.top().second;

        heap.pop();

        if (distanta[nod] == dd) {
            for (auto vec: gph[nod])
                if (capacitate[nod][vec] > 0) {
                    int distNoua = distanta[nod] + cost[nod][vec] + distInitiala[nod] - distInitiala[vec];
                    if (distNoua < distanta[vec]) {
                        distanta[vec] = distNoua;
                        distReala[vec] = distReala[nod] + cost[nod][vec];
                        p[vec] = nod;
                        heap.push(make_pair(distanta[vec], vec));
                    }
                }
        }
    }

    for (int i = 1; i <= n; i++)
        distInitiala[i] = distReala[i];

    if (distanta[d] == 1e9) return false;

    int minim = 1e9;
    int aux = d;
    int costCur = 0;

    while (aux != s) {
        minim = min(minim, capacitate[p[aux]][aux]);
        costCur += cost[p[aux]][aux];
        aux = p[aux];
    }

    F += minim;
    Fcst += minim * distReala[d];

    aux = d;
    while (aux != s) {
        capacitate[p[aux]][aux] -= minim;
        capacitate[aux][p[aux]] += minim;
        aux = p[aux];
    }

    return true;
}


void bellmanFord() {
    vector<bool> inCoada(355, false);
    queue<int> coada;

    for (int i = 1; i <= n; i++)
        distInitiala[i] = 1e9;

    distInitiala[s] = 0;
    coada.push(s);
    inCoada[s] = true;
    while (!coada.empty()) {
        int nod = coada.front();
        coada.pop();
        inCoada[nod] = false;
        for (auto vec: gph[nod]) {
            if (capacitate[nod][vec]) {
                if (distInitiala[nod] + cost[nod][vec] >= distInitiala[vec]) continue;

                distInitiala[vec] = distInitiala[nod] + cost[nod][vec];

                if (inCoada[vec]) continue;

                coada.push(vec);
                inCoada[vec] = true;
            }
        }
    }
}


int main() {
    f >> n >> m >> s >> d;

    for (int i = 0; i < m; i++) {
        int x, y, c, z;
        f >> x >> y >> c >> z;
        gph[x].push_back(y);
        gph[y].push_back(x);
        capacitate[x][y] = c;
        cost[x][y] = z;
        cost[y][x] = -z;
    }

    bellmanFord();


    while (dijkstra());

    g << Fcst;
}
