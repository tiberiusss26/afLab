#include <iostream>
#include <fstream>
#include<vector>

using namespace std;

ifstream f("riremito.in");
ofstream g("riremito.out");


vector<pair<int, long long> > listaAd[100001];
long long distRadacina[100001], distFrunza[100001], d[100001];
vector<bool> viz(100001, false);

void dfs(int nod) {
    viz[nod] = true;
    for(auto it : listaAd[nod])
        if(!viz[it.first]) {
            distRadacina[it.first] = distRadacina[nod] + it.second; ///dist pana la radacina
            dfs(it.first);
            distFrunza[nod] = max(distFrunza[nod], distFrunza[it.first] + it.second); /// dFrunza[nod] -> distanta maxima pana la o frunza
            d[nod] += d[it.first] + it.second + min(distFrunza[it.first] + it.second, distRadacina[nod]); /// d[nod] -> distanta necesara sa parcurg tot subarborele nodului si sa ma intorc in nod
        }
    d[nod] -= min(distRadacina[nod], distFrunza[nod]);
}

int main()
{
    int n;
    f >> n;
    for(int i = 1; i < n; ++i) {
        int x, y;
        long long c;
        f >> x >> y >> c;
        listaAd[x].push_back(make_pair(y, c));
        listaAd[y].push_back(make_pair(x, c));
    }
    int k;
    f >> k;
    while(k--) {
        int start;
        f >> start;
        for(int i = 1; i <= n; ++i) {
            viz[i] = false;
            d[i] = 0;
            distRadacina[i] = 0;
            distFrunza[i] = 0;
        }
        dfs(start);
        g << d[start] << '\n';
    }
    return 0;
}