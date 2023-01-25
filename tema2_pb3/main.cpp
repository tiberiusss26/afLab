//Clustering.Fişierul cuvinte.inconţine cuvinte pe mai multe linii, cuvintelede pe o linie fiind separate prin spaţiu.
// Se citeşte de la tastatură un număr natural k.Se consideră distanţa Levenshtein
// între două cuvintehttps://en.wikipedia.org/wiki/Levenshtein_distance.
// Să se împartă cuvintele dinfişier în k clase(categorii)nevideastfel încât gradul de separare al claselor să fie maxim
// (= distanţa minimă între două cuvinte din clase diferite) -v. curs; se vor afişape câte o linie cuvintele din fiecare clasă
// și pe o altă linie gradul de separare al claselor.
#include <fstream>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

ifstream f("cuvinte.in");

class cluster {
    int *rang, *tata;
    string *cuv;
    int n, k;
public:
    explicit cluster(int k) : k(k) {
        rang = new int[n];
        tata = new int[n];
        cuv = new string[n];
        n = actualizeaza();
    }

    int actualizeaza() {
        int i = 0;
        while (f >> cuv[i]) {
            tata[i] = i;
            rang[i] = 0;
            i++;
        }
        return i;
    }

    int gaseste(int nod) {
        while (tata[nod] != nod)
            nod = tata[nod];
        return tata[nod];
    }

    void reuneste(int a, int b) {
        int x = gaseste(a);
        int y = gaseste(b);

        if (x == y)
            return;

        if (rang[x] < rang[y])
            tata[x] = y;
        else if (rang[x] > rang[y])
            tata[y] = x;
        else {
            tata[y] = x;
            rang[x]++;
        }
    }

    void clustering() {
        bool viz[n][n];
        for (int i = 0; i <= n; i++)
            for (int j = 0; j < n; j++)
                viz[i][j] = false;

        for (int x = 1; x <= n - k ; x++) { // facem reuniune de n-k ori pentru a avea fix k multimi
            int c1, c2, dmin = 1e9;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (!viz[i][j] && cluster::distLeven(cuv[i], cuv[j]) < dmin && tata[i] != tata[j]) {
                        c1 = i;
                        c2 = j;
                        dmin = cluster::distLeven(cuv[i], cuv[j]);
                    }
                }
            }
            viz[c1][c2] = true;
            viz[c2][c1] = true;
            reuneste(c1, c2);
        }

        vector<vector<int>> sol(k);
        set<int> parinti;
        for (int i = 0; i < n; i++) {
            parinti.insert(tata[i]);
        }
        for (int i = 0; i < k; i++)
            for (auto it: parinti) {
                sol[i].push_back(it);
                parinti.erase(it);
                break;
            }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                if (tata[i] == tata[sol[j][0]] && tata[i] != i) {
                    sol[j].push_back(i);
                    break;
                }
            }
        }

        for(int i =0;i<k;i++){
            for(auto it: sol[i])
                cout<<cuv[it]<<" ";
            cout<<"\n";
        }

        // gradul de separare
        int gradSep = 999999;
        for(int i =0;i<k;i++)
            for(int j =i+1;j<k;j++)
                for(auto it: sol[i])
                    for(auto itt: sol[j])
                        if(cluster::distLeven(cuv[it],cuv[itt])< gradSep)
                            gradSep = cluster::distLeven(cuv[it],cuv[itt]);

        cout<<gradSep;

        // sau asa , parcurgand inca un pas din kruskal
//        int c1, c2, dmin = 1e9;
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < n; j++) {
//                if (!viz[i][j] && cluster::distLeven(cuv[i], cuv[j]) < dmin && tata[i] != tata[j]) {
//                    c1 = i;
//                    c2 = j;
//                    dmin = cluster::distLeven(cuv[i], cuv[j]);
//                }
//            }
//        }
//        cout<<cluster::distLeven(cuv[c1],cuv[c2]);


    };

    static int distLeven(const string &cuv1, const string &cuv2) {
        auto m = cuv1.length();
        auto n = cuv2.length();
        int L[cuv1.length() + 1][cuv2.length() + 1];
        for (int i = 0; i <= cuv1.length(); i++)
            for (int j = 0; j <= cuv2.length(); j++) {
                L[i][j] = 0;
                if (j == 0 && i >= 1)
                    L[i][j] = i;
                if (i == 0 && j >= 1)
                    L[i][j] = j;
            }
        int subCost ;
        for (int j = 1; j <= n; j++)
            for (int i = 1; i <= m; i++) {
                if (cuv1[i - 1] == cuv2[j - 1])
                    subCost = 0;
                else
                    subCost = 1;
                L[i][j] = min(L[i - 1][j] + 1, min(L[i][j - 1] + 1, L[i - 1][j - 1] + subCost));
            }
        return L[m][n];
    }


    ~cluster() = default;
};


int main() {
    int k;
    cout<<"k: ";
    cin >> k;
    cluster a(k);
    a.clustering();
}
