#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <math.h>

using namespace std;


int main() {
    vector<vector<int>> graph = {{1, 2, 3},
                                 {0},
                                 {0},
                                 {0}};
    auto n = graph.size();
    auto deVizitat = pow(2,n)-1;
    set<pair<int,int>> stare;
    queue<pair<int,int>>coada;
    for(int i =0;i<n;i++){
        stare.insert(make_pair(i,(1<<i)));
        coada.push(make_pair(i,(1<<i)));}
    int ind = 0;

    while(!coada.empty()){
        auto m = coada.size();
        for(int i = 0;i<m;i++){
            auto curr = coada.front();
            coada.pop();
            if(curr.second == deVizitat) return ind;
            for(auto j: graph[curr.first]){
                auto urm = make_pair(j,curr.second|(1<<j));
                if(stare.find(urm)!=stare.end())continue;
                stare.insert(urm);
                coada.push(urm);
            }
        }
        ind++;
    }
    cout<<ind;
    return 0;

}
