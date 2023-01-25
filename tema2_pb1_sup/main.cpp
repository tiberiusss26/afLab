#include <iostream>
#include <vector>

using namespace std;

int distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int Reprez(int u, vector<int> &tata) {
    while (tata[u] != u)
        u = tata[u];
    return u;
}

void Reuneste(int u, int v, vector<int> &tata, vector<int> &rank) {
    int ru, rv;
    ru = Reprez(u, tata);
    rv = Reprez(v, tata);
    if (rank[ru] > rank[rv])
        tata[rv] = ru;
    else {
        tata[ru] = rv;
        if (rank[ru] == rank[rv])
            rank[rv] = rank[rv] + 1;
    }
}

int minCostConnectPoints(vector<vector<int>> &points) {
    vector<int> tata(points.size(), -1), rank(points.size(), 0);
    for(int i =0;i<points.size();i++)
        tata[i] = i;
    vector<vector<int>> listaAd;
    for (int i = 0; i < points.size(); i++)
        for (int j = i + 1; j < points.size(); j++)
            listaAd.push_back({distance(points[i][0], points[i][1], points[j][0], points[j][1]), i, j});
    /*calculam distantele intre oricare doua puncte
     * si apoi le sortam crescator */
    sort(listaAd.begin(), listaAd.end());

    int k = 0;
    //facem kruskal
    for (auto it: listaAd) {
        int d = it[0];
        int x = it[1];
        int y = it[2];
        if (Reprez(x, tata) != Reprez(y, tata)) {
            Reuneste(x, y, tata, rank);
            k+= d;
        }
    }
    cout<<k;


}

int main() {
    vector<vector<int>> points(5);
    points[0].push_back(0);
    points[0].push_back(0);
    points[1].push_back(2);
    points[1].push_back(2);
    points[2].push_back(3);
    points[2].push_back(10);
    points[3].push_back(5);
    points[3].push_back(2);
    points[4].push_back(7);
    points[4].push_back(0);

    minCostConnectPoints(points);


}
