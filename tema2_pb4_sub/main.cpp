#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, q;
vector<int> tata, rang;
vector<vector<int>> listaMuch(100001);


ifstream fin("apm2.in");
ofstream fout("apm2.out");

int gaseste(int nod) {
    while (tata[nod] != nod)
        nod = tata[nod];
    return nod;
}

void uneste(int nod1, int nod2) {
    int x = gaseste(nod1);
    int y = gaseste(nod2);

    if (rang[x] > rang[y])
        tata[y] = x;
    else {
        tata[x] = y;
        if (rang[x] == rang[y])
            rang[y]++;
    }
}

int main() {
    fin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int x, y, z;
        fin >> x >> y >> z;
        listaMuch[i]={x, y, z};
    }

    listaMuch.resize(m);
    //ordonam muchiile pt Kruskal
    sort(listaMuch.begin(), listaMuch.end(), [&](vector<int> &a, vector<int> &b) {
        if (a[2] < b[2]) return true;
        return false;
    });

    tata.resize(n + 1);
    rang.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) tata[i] = i;

    int min = 0;
    int index = 0;

    for (auto &it: listaMuch) {
        if (index > n - 1) break; // daca am creat deja arborele nu mai avem nevoie sa vf restul muchiilor
        int a = gaseste(it[0]);
        int b = gaseste(it[1]);
        if (a != b) {
            uneste(a, b);
            listaMuch[index][0] = it[0];
            listaMuch[index][1] = it[1];
            listaMuch[index++][2] = it[2];
            min += it[2];
        }
    }
    listaMuch.resize(n - 1);

    //acum avem apm-ul
    for (int i = 0; i < q; i++) {
        int x, y;
        fin >> x >> y;
        rang.clear();
        rang.resize(n + 1, 0);
        for (int j = 1; j <= n; j++) {
            tata[j] = j;
        }
        int min2 = 0;
        //pentru fiecare muchie noua o adaugam in APM cu costul 0 practic
        uneste(x, y);
        int indexx = 0;
        for (auto &it: listaMuch) {
            int a = gaseste(it[0]);
            int b = gaseste(it[1]);
            if (a != b) {
                uneste(a, b);
                min2 += it[2];
                indexx++;
                if (indexx == n - 1)
                    break;
            }

        }
        //dupa ce am aflat minimul noului APM, costul maxim al muchiei adaugate este diferenta dintre minime, -1,
        // pentru a ne asigura ca este sigur in APM
        fout << (min - min2 - 1) << "\n";

    }


}
