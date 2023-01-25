#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

vector<unordered_map<int, int>> vizite;

void euler(unordered_map<int, stack<int>>& lista, vector<vector<int>>&sol, int nod ){
    auto &stack = lista[nod];

    while(!stack.empty()){
        int vecin = stack.top();
        stack.pop();
        euler(lista,sol,vecin);
        sol.push_back({nod,vecin});
    }
}

vector<vector<int>> validArrangement(vector<vector<int>> &pairs) {
    int l = pairs.size();
    unordered_map<int, stack<int>> listaAd(l);
    unordered_map<int, int> in(l), out(l);
    vector<vector<int>>sol;

    for (auto it: pairs) {
        listaAd[it[0]].push(it[1]);
        out[it[0]]++;
        in[it[1]]++;
    }

    int start = -1;
    for (auto &it: listaAd) {
        if (out[it.first] - in[it.first] == 1) start = it.first;
    }
    if(start == -1)
        start = listaAd.begin()->first;

    euler(listaAd,sol,start);
    reverse(sol.begin(),sol.end());

    return sol;
}

int main() {
    vector<int> a = {1, 2, 3};
    vector<vector<int>> listaAd(10);
    listaAd = {{5,  1},
               {4,  5},
               {11, 9},
               {9,  4}};


    vector<vector<int>> rez = validArrangement(listaAd);
    for(auto it: rez){
        cout<<it[0]<<" "<<it[1]<<"\n";
    }
}
