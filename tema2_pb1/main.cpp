#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

//facem un struct pentru a pastra coordonatele punctelor de interes
struct locatie {
    double x,y;
};

ifstream fin("retea2.in");
ofstream fout("retea2.out");

double distEucl(locatie a, locatie b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
    double n, m;
    fin >> n >> m;

    locatie centrala[2005], bloc[2005];

    // memoram daca se afla in arborele APM
    bool inAPM[2005];
    vector<double> distC(2005), d(2005);

    for (int i = 1; i <= n; i++)
        fin >> centrala[i].x >> centrala[i].y;
    for (int i = 1; i <= m; i++)
        fin >> bloc[i].x >> bloc[i].y;

    //initializam costul pana la fiecare nod cu distanta minima pana la cea mai apropiata centrala
    for (int i = 1; i <= m; i++) {
        double minC = 1e9;
        for(int j=1;j<=n;j++)
            minC = min(minC, distEucl(bloc[i],centrala[j]));
        d[i] = minC;
    }

    //Prim

    double k = 0;

    for(int i =1;i<=m;i++){
        // din multimea de noduri neselectate cautam nodul cu eticheta minima
        double etMin = 1e9;
        int nod = -1;
        for(int j =1;j<=m;j++)
            if(!inAPM[j] && d[j]<etMin)
            {
                etMin = d[j];
                nod = j;
            }
        // adaugam etichema minima la suma cautata
        k+= d[nod];
        //scoatem din lista de noduri neaccesate
        inAPM[nod] = true;

        // pt fiecare nod neaccesat verificam daca e mai aproape de noul nod altfel pastram distanta initaiala
        for(int j = 1;j<=m;j++)
            d[j] = min(d[j], distEucl(bloc[j],bloc[nod]));
    }

    fout<<fixed<<setprecision(6)<<k;

}
