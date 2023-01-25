#include <iostream>
#include <vector>
#include <queue>

using namespace std;
//solutia problemei se bazeaza pe sortarea topologica a cursurilor

vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    queue<int> coada; // in coada pastram cursurile care se pot desfasura fara sa fie precedate de altele
    vector<vector<int>> listaAd(numCourses + 1);
    vector<int> d(numCourses), sol;
    if (prerequisites.empty()) // daca nu exista o ordine in care sa fie urmate cursurile
        return sol; //inseamna ca nu exista un ciclu si returnam un vector vid


    for (auto it: prerequisites) {
        listaAd[it[1]].push_back(
                it[0]); // pastram o lista pt fiecare curs cu acele cursuri care trebuie sa aiba loc inainte
        d[it[0]]++; //  vector care pastreaza gradul intern al fiecarui nod
    }

    for (int i = 0; i < numCourses; i++)
        if (d[i] == 0)
            coada.push(i); // punem in coada cursurile care sunt independente

    while (!coada.empty()) {
        int x = coada.front(); // x e cursul actual si il scoatem din coada si il punem in solutie
        sol.push_back(x);
        coada.pop();
        for (auto vec: listaAd[x]) {
            d[vec]--;
            if (d[vec] == 0)
                coada.push(vec);
        }
    }

    if (sol.size() == numCourses) {
        sol.clear();
        return sol; // daca solutia contine toate cursurile atunci nu avem niciun ciclu si returnam vector vid
    } else { // daca solutia nu contine toate cursurile inseamna ca s a format un ciclu
            // astfel pastram in sol fiecare curs care are gradul intern diferit de 0
        sol.clear();
        for (int i = 0; i < numCourses; i++)
            if (d[i] != 0)
                sol.push_back(i);
        return sol;
    }
}

int main() {

}
