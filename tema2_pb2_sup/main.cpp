#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

vector <int> tata(100005,-1);

int gaseste(int nod){
    while(tata[nod]!=nod)
        nod = tata[nod];
    return nod;
}

void uneste(int nod1, int nod2){
    int x = gaseste(nod1);
    int y = gaseste(nod2);

    if(x!=y)
        tata[y] = x;
}


vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>> &edgeList, vector<vector<int>> &queries) {

    for(int i =0;i<n;i++) tata[i] = i;

    //sortam lista de muchii crescator dupa lungimea intre noduri
    sort(edgeList.begin(),edgeList.end(),[](vector<int>&a, vector<int>&b){
        if(a[2]<b[2]) return true;
        return false;
    });

    //adaugam nr de ordine al fiecarui querry
    for(int i =0;i<queries.size();i++)
        queries[i].push_back(i);

    //sortam querriurile in functie de lungimea care trb verificata
    //pentru ca daca gasim un drum cu costul muchiilor mai mic decat k
    //sigur avem un sub-drum cu costul muchiilor mai mic decat un k mai mare
    sort(queries.begin(),queries.end(),[](vector<int>&a,vector<int>&b){
        if(a[2]<b[2]) return true;
        return false;
    });

    // vector de solutii pt rasp la querry-uri
    vector<bool> sol(queries.size(), false);

    int k = 0;
    for(int i =0;i<queries.size();i++) {

        //pt fiecare muchie verificam sa aiba costul mai mic decat cere querry-ul
        //si daca indeplineste conditia o adaugam in arbore
        while(k<edgeList.size() && edgeList[k][2] < queries[i][2])
        {
            uneste(edgeList[k][0],edgeList[k][1]);
            k++;
        }

        //daca sunt in acelasi APM cele doua noduri inseamnca ca exista un drum cu toate muchiile mai mici decat k
        if(gaseste(tata[queries[i][0]]) == gaseste( tata[queries[i][1]])) sol[queries[i][3]] = true;
    }
    return sol;

}

int main() {
    int n = 3;
    vector<vector<int>> edgeList = {{0, 1, 2},
                                    {1, 2, 4},
                                    {2, 0, 8},
                                    {1, 0, 16}}, queries = {{0, 1, 2},
                                                            {0, 2, 5}};


//    vector<vector<pair<int, int>>> listaAd(n);
//    for (auto it: edgeList) {
//        listaAd[it[0]].push_back(make_pair(it[1], it[2]));
//        listaAd[it[1]].push_back(make_pair(it[0], it[2]));
//    }
//    for(int i = 0;i<n;i++)
//    {
//        cout<<i<<": ";
//        for(auto it: listaAd[i])
//            cout<<it.first<<","<<it.second<<" | ";
//        cout<<endl;
//    }


}