#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
//#include <bits/stdc++.h>

using namespace std;

ifstream fin("online.in");
ofstream fout("online.out");

/*
 * Rezolvarea problemei o abordam construind un APM cu algoritmul lui Kruskal
 * De fiecare data cand avem o muchie noua aplicam algoritmul pe muchiile din arbore
 * Pastram de fiecare data muchiile din APM
 *
 * */
vector<int> tata, rang;

int gaseste(int nod) {
    while (tata[nod] != nod)
        nod = tata[nod];
    return nod;
}

void uneste(int nod1, int nod2) {
    int x = gaseste(nod1);
    int y = gaseste(nod2);

    if(rang[x]> rang[y]){
        tata[y] = x;
    }
    else{
        tata[x] = y;
        if(rang[x]==rang[y])
            rang[y] ++;
    };
}


int main() {
    int n, m, k;
    fin >> n >> m;
    vector<vector<int>> listaAd;

    tata.resize(n,-1);
    rang.resize(n,0);
    for (int i = 0; i < n; i++)
        tata[i] = i;

    for (int i = 0; i < m; i++) {
        int x, y, z;
        fin >> x >> y >> z;
        listaAd.push_back({x, y, z});
    }

    // folosim kruskal utilizand min-heap
    sort(listaAd.begin(), listaAd.end(), [](vector<int> &a, vector<int> &b) {
        if (a[2] < b[2]) return true;
        return false;
    });

    int min = 0;
    int index = 0;
    for (auto it: listaAd) {
        if (gaseste(it[0]) != gaseste((it[1]))) {
            uneste(it[0], it[1]);\
            // pastram pe primele n-1 pozitii muchiile din APM
            listaAd[index][0] = it[0];
            listaAd[index][1] = it[1];
            listaAd[index++][2] = it[2];
            min += it[2];
        }
    }
    listaAd.resize(n-1);
    fout << min << "\n";

    fin >> k;
    for (int i = 0; i < k; i++) {
        int x, y, z;
        fin >> x >> y >> z;
        listaAd.push_back({x, y, z});
        //pentru fiecare segment nou de drum il adaugam la muchiile existente deja
        //sortam crescator din nou muchiile in functie de cost
        sort(listaAd.begin(), listaAd.end(), [](vector<int> &a, vector<int> &b) {
            if (a[2] < b[2]) return true;
            return false;
        });


        //facem kruskal pe noile muchii
        tata.clear();
        rang.clear();
        tata.resize(n,-1);
        rang.resize(n,0);
        for (int j = 0; j < n; j++)
            tata[j] = j;

        int miin = 0;
        int indexx = 0;
        for (auto it: listaAd) {
            if (gaseste(it[0]) != gaseste((it[1]))) {
                uneste(it[0], it[1]);
                listaAd[indexx][0] = it[0];
                listaAd[indexx][1] = it[1];
                listaAd[indexx++][2] = it[2];
                miin += it[2];
            }
        }
        listaAd.resize(n-1 );

        fout << miin << "\n";
    }
}