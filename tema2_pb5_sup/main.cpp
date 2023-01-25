#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream f("ciclu.in");
ofstream g("ciclu.out");

long long n, m;


bool bellmanFord(long long medie, vector<vector<pair<long long, long long>>> &listaAd) {
    // vector de distante si de modificari pentru a verifica ciclu
    vector<long long> d(n + 1, 1e9), modificari(n + 1, 0);
    //vector pt a verifica daca un nod e in coada si daca a fost vizitat
    vector<bool> inCoada(n + 1, false), vizitat(n + 1, false);

    //coada pt nodurile care au fost modificate pt eficientizare
    //nodurile care nu sunt in coada au muchiile relaxate
    queue<long long> modificat;

    //aplicam pentru fiecare nod algoritmul pentru ca
    // exista posibilitatea de a avea mai multe comp conexe
    for (int i = 1; i <= n; i++) {
        // daca a fost deja verificat inseamna ca nu se afla intr o comp conexa noua
        if (vizitat[i]) continue;

        d[i] = 0; // nodul de start
        ++modificari[i];
        inCoada[i] = true;
        vizitat[i] = true;
        modificat.push(i);

        while (!modificat.empty()) {
            long long nod = modificat.front();
            modificat.pop();

            inCoada[nod] = false;
            vizitat[nod] = true;

            // aplicam alogritmul clasic doar ca scadem valoarea medie a ciclului
            for (auto vec: listaAd[nod]) {
                if (d[nod] + vec.second - medie < d[vec.first]) {
                    d[vec.first] = d[nod] + vec.second - medie;

                    if(!inCoada[vec.first]){
                        ++modificari[vec.first];

                        if(modificari[vec.first]==n) return true; // daca a fost vizitat de n ori inseamna ca avem ciclu

                        modificat.push(vec.first); // altfel adaugam in coada pentru actualizare
                        inCoada[vec.first] = true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    f >> n >> m;

    vector<vector<pair<long long, long long>>> listaAdiacenta(n + 1);
    for (int i = 0; i < m; i++) {
        long long x, y, z;
        f >> x >> y >> z;
        listaAdiacenta[x].push_back(make_pair(y, z * 100));
    }

    long long st = 0, dr = 10000000;

    //facem cautare binara a valorii mediei unui ciclu
    // daca nu avem un ciclu cautam o valoare mai mare
    // daca avem, cautam sa vedem daca se poate cu o valoare mai mica
    while(st<=dr){
        long long mij = (st+dr)/2;
        if(!bellmanFord(mij, listaAdiacenta)) st = ++mij;
        else dr = --mij;
    }

    g<<dr / 100<<"."<<dr%100;
}
