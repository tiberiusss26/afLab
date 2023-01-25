#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <algorithm>

using namespace std;

int n, k=0;
vector<vector<int>> solutie;


ifstream f("ctc.in");
ofstream g("ctc.out");

// am abordat problema folosing algoritmul lui tarjan
// folosesc un struct pt fiecare nod in care sa pastrez indexul lui,
//lowlink ul care se refera la indexul cel mai mic al nodului la care se poate intoarce
// si daca acesta este deja in stiva sau nu
struct vertex {
    int index = -1;
    int lowlink = -1;
    bool peStiva = false;
};

void tareConex(int nod, int &ind, stack<int> &stiv, vertex v[], vector<vector<int>> &listaAdiacenta) {
    v[nod].index = ind; // indexul reprezinta ordinea in care a fost vizitat nodul
    v[nod].lowlink = ind; // lowlink ul initializat cu indexul propriu
    ind++; // crestem indexul pentru urmatorul nod
    stiv.push(nod); // punem pe stiva nodul
    v[nod].peStiva = true;

    for (auto vec: listaAdiacenta[nod]) {
        if (v[vec].index == -1) { // daca vecinii nodului curent nu au fost vizitati ii vizitam
            tareConex(vec, ind, stiv, v, listaAdiacenta);
            v[nod].lowlink = min(v[nod].lowlink, v[vec].lowlink);
        } else if (v[vec].peStiva)
            // daca vecinul este deja pe stiva inseamna ca nodul apartine unei CTC
            v[nod].lowlink = min(v[nod].lowlink, v[vec].index);
    }

    if (v[nod].lowlink == v[nod].index) {
        // daca lowlink ul nodului este chiar indexul atunci am gasit o componenta conexa
        // si alcatuim componenta conexa cu elementele din stiva
        k++;
        vector<int> sol;
        int w;
        do {
            w = stiv.top();
            stiv.pop();
            v[w].peStiva = false;
            sol.push_back(w);
        }while(w!=nod);
        solutie.push_back(sol);
    }
}

void tarjan() {
    int index = 0, m, x, y;
    stack<int> stiva;
    f >> n >> m;
    vector<vector<int>> listaAd(n + 1);
    for (int i = 0; i < m; i++) {
        f >> x >> y;
        listaAd[x].push_back(y);
    }
    f.close();
    vertex v[n + 1];
    for (int i = 1; i <= n; i++) {
        if (v[i].index == -1)
            tareConex(i, index, stiva, v, listaAd);
    }
}

int main() {
    tarjan();
    g<<k<<"\n";
    for(auto &it: solutie)
        std::sort(it.begin(), it.end());
    for(auto it: solutie)
    {
        for(auto nod: it)
            g<<nod<<" ";
        g<<"\n";
    }
}
