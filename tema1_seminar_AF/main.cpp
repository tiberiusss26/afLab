#include <iostream>
#include <vector>

using namespace std;
//modificam dfs ul astfel incat acesta sa creeze o bipartitie a oamenilor
// daca intalnim doi oameni care nu se agreeaza dar sunt in aceeasi partitie
//inseamna ca nu exista o impartire a acestora
bool dfs(int nod, vector<int> &sol, vector<vector<int>> &lista_ad) {
    if (sol[nod] == 0)
        sol[nod] = 1; // daca omul respectiv nu face parte dintr un grup anume, ii dam grupul 1 ca valoare implicita
    for (auto vec: lista_ad[nod]) {
        if (sol[vec] == sol[nod]) return false;  // daca doua persoane care nu se agreeaza se afla in aceeasi partitie, dfs ul returneaza fals
        if (sol[vec] == 0) {
            sol[vec] = sol[nod] * (-1); // daca persoanele pe care nu le place un om nu fac parte dintr un grup, le partitionam in grupul opus
            dfs(vec, sol, lista_ad);
        }
    }
    return true;
}

vector<vector<int>> possibleBipartition(int n, vector<vector<int>> &dislikes) {
    vector<vector<int>> listaAd(n + 1);
    vector<vector<int>> grupe(2);
    for (auto it: dislikes) { // creeam lista de adiacenta pt fiecare persoana cu persoanele pe care nu le place
        listaAd[it[0]].push_back(it[1]);
        listaAd[it[1]].push_back(it[0]);
    }

    vector<int> sol(n + 1, 0);

    for (int i = 1; i <= n; i++)  // facem parcurgerea pentru fiecare persoana care nu se afla intr o partitie
        if (sol[i] == 0)
            if (!dfs(i, sol, listaAd)) {
                return grupe; // daca dfs ul returneaza fals atunci functia noastra va returna o lista vida
            }

    vector<int> g1, g2;
    for (int i = 1; i <= n; i++) { // daca ramanem in functie inseamna ca este posibila bipartitia si o returnam
        if (sol[i] == 1)
            g1.push_back(i);
        else
            g2.push_back(i);
    }
    grupe.push_back(g1);
    grupe.push_back(g2);
    return grupe;
    }


int main() {
    int n = 10;
    vector<vector<int>> dislikes(6);

    dislikes[0].push_back(1);
    dislikes[0].push_back(2);
    dislikes[1].push_back(3);
    dislikes[1].push_back(4);
    dislikes[2].push_back(5);
    dislikes[2].push_back(6);
    dislikes[3].push_back(6);
    dislikes[3].push_back(7);
    dislikes[4].push_back(8);
    dislikes[4].push_back(9);
    dislikes[5].push_back(7);
    dislikes[5].push_back(8);

    vector<vector<int>> listaAd(n + 1);
    for (auto it: dislikes) {
        listaAd[it[0]].push_back(it[1]);
        listaAd[it[1]].push_back(it[0]);
    }
    vector<int> sol(n + 1, 0);

    for (int i = 1; i <= n; i++)
        if (sol[i] == 0)
            dfs(i, sol, listaAd);

    vector<vector<int>>bipartit = possibleBipartition(n, dislikes);

    for (auto it: bipartit) {
        for (auto itt: it)
            cout << itt << " ";
        cout << endl;
    }
}