#include <iostream>
#include <fstream>

#include <vector>

using namespace std;

ifstream f("dfs.in");
ofstream g("dfs.out");

class graf {
    vector<vector<int>> listaAd;
    int n, m;
public:
    graf(const vector<vector<int>> &listaAdiacenta, int n, int m) : n(n), m(m) {
        listaAd.resize(n + 1);
        for (auto v: listaAdiacenta) {
            listaAd[v[0]].push_back(v[1]);
            listaAd[v[1]].push_back(v[0]);
        }
    }

    void aranjeazaListaAd(vector<int> ordine) { // aranjam nodurile adiacente altui nod
        for (int i = 1; i <= n; i += 1) {      // in ordine in care apar in permutare
            sort(listaAd[i].begin(), listaAd[i].end(), [&](int a, int b) {
                return ordine[a] < ordine[b];
            });
        }
    };

    void dfs(int nod, vector<int> &viz, vector<int> &ordineDfs) {
        viz[nod] = 1;
        ordineDfs.push_back(nod);  // pastram ordinea in care parcurgem graful
        for (auto vec: listaAd[nod])
            if (viz[vec] == 0)
                dfs(vec, viz, ordineDfs);
    }

    int verificaDfs(vector<int> permutari){
        vector<int> ordineDfs, viz(n+1,0);
        dfs(1,viz, ordineDfs);
        return (permutari == ordineDfs);
        // daca ordinea in care sunt parcurse nodurile coincide cu permutarea
        // atunci functia returneaza 1

    }


    void arataLista() {
        int i = 0;
        for (auto itt: listaAd) {
            cout << i << ": ";
            for (auto it: itt)
                cout << it << " ";
            cout << endl;
            i++;
        }
    }

    virtual ~graf() {}
};

int main() {
    int n, m,x;
    f >> n >> m;
    vector<int> p, ordine(n + 1);
    for (int i = 0; i < n; i++) {
        f >> x;
        p.push_back(x);
        ordine[x] = i;
    }
    vector<vector<int>> lista_ad;

    for (int i = 0; i < m; i++) {
        int x, y;
        f >> x >> y;
        vector<int> v;
        v.push_back(x);
        v.push_back(y);
        lista_ad.push_back(v);
    }

    graf gg = graf(lista_ad, n, m);
    gg.aranjeazaListaAd(ordine);
    cout<<gg.verificaDfs(p);
}
