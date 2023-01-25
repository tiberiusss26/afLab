#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <iomanip>

using namespace std;

struct locatie {
    long double x, y;
};

ifstream f("retea2.in");
ofstream g("retea2.out");

long double distEucl(locatie a, locatie b) {
    long double x = (b.x - a.x) * (b.x - a.x);
    long double y = (b.y - a.y) * (b.y - a.y);
    return sqrt(x + y);
}

int main() {
    long long n, m;
    long double k = 0;
    f >> n >> m;

    vector<long long> tata(m + 1);
    locatie centrala[n + 1], bloc[m + 1];

    for (long long i = 1; i <= n; i++)
        f >> centrala[i].x >> centrala[i].y;

    for (long long i = 1; i <= m; i++)
        f >> bloc[i].x >> bloc[i].y;

    vector<long double> dCentrala(m + 2, 1e9); // distanta pana la centrala

    for (long long i = 1; i <= m; i++) {
        for (long long j = 1; j <= n; j++) {
            if (distEucl(bloc[i], centrala[j]) < dCentrala[i]) {
                dCentrala[i] = distEucl(bloc[i], centrala[j]);
                tata[i] = m + 1; // m+1 e tatal centrala
            }
        }

    }
    vector<long double> d(m + 2);
    unordered_set<long long> q;

    for (long long i = 1; i <= m + 1; i++) {
        q.insert(i);
        d[i] = dCentrala[i];
    }

    //inceput Alg Prim

    d[m + 1] = 0; // nodul centrala are distanta 0

    while (!q.empty()) {
        long long etMin = -1;
        for (auto it: q)
            if (etMin == -1 || d[it] < d[etMin]) etMin = it;

        q.erase(etMin);

        for (auto i: q) {
            if (distEucl(bloc[etMin], bloc[i]) < d[i]) {
                d[i] = distEucl(bloc[etMin], bloc[i]);
                tata[i] = etMin;
            }
        }
    }

    for (long long i = 1; i <= m; i++)
        if (tata[i] != m + 1)
            k += distEucl(bloc[i], bloc[tata[i]]);
        else
            k += dCentrala[i];


    g << fixed << setprecision(7) << k;

}
