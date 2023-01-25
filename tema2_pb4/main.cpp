#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start, int end) {
    vector<vector<pair<int, double>>> listaAd(n);
    for (int i = 0; i < succProb.size(); i++) {
        listaAd[edges[i][0]].push_back(make_pair(edges[i][1], succProb[i]));
        listaAd[edges[i][1]].push_back(make_pair(edges[i][0], succProb[i]));
    }

    vector<double> d(n,-1);

    //               nod , probabilitate
    priority_queue<pair<int,double>> Q; //max-heap

    Q.push(make_pair(start,1)); // prob in nodul de start e 1
    d[start] = 1;
    int nod;
    double greutate;
    while (!Q.empty()) {
        nod = Q.top().first;
        greutate = Q.top().second;
        Q.pop();
        for (auto it: listaAd[nod])
            if (d[nod] * it.second > d[it.first]) {
                d[it.first] = d[nod] * it.second;
                Q.push(make_pair(it.first, it.second));

            }
    }
    if (d[end] < 0) // daca nu exista drum pana la destinatie distanta ramane -1 de la initializare
        return 0;
    else
        return d[end];

}

int main() {
    int n = 10;
    vector<vector<int>> edges(n);
    edges[0].push_back(0);
    edges[0].push_back(3);
    edges[1].push_back(1);
    edges[1].push_back(7);
    edges[2].push_back(1);
    edges[2].push_back(2);
    edges[3].push_back(0);
    edges[3].push_back(9);
    vector<double> succProb;
    succProb.push_back(0.31);
    succProb.push_back(0.9);
    succProb.push_back(0.86);
    succProb.push_back(0.36);
    int start = 2, end = 3;
    vector<vector<pair<int, double>>> listaAd(n);
    cout << maxProbability(n, edges, succProb, start, end);
}
