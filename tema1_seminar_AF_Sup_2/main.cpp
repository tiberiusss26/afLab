#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void df(int nod, vector<int>& viz, vector<int>& niv, vector<int>& niv_min, vector<vector<int>>& listaAd, vector<vector<int>>& sol){
        viz[nod] = 1;
        niv_min[nod] = niv[nod] ;
        for(auto vec: listaAd[nod]){
            if(viz[vec]==0)
            {
                niv[vec] = niv[nod] + 1;
                df(vec, viz, niv, niv_min, listaAd,sol);
                niv_min[nod] = min(niv_min[nod],niv_min[vec]);
                if(niv_min[vec]>niv[nod])
                {
                    vector<int> v;
                    v.push_back(nod);
                    v.push_back(vec);
                    sol.push_back(v);
                }

            }
            else
            if(niv[vec]<niv[nod]-1)
                niv_min[nod] = min(niv_min[nod],niv[vec]);
        }

    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> listaAd(n+1);
        for(auto it: connections)
        {   listaAd[it[0]].push_back(it[1]);
            listaAd[it[1]].push_back(it[0]);
        }
        vector<int> viz(n), niv(n), niv_min(n);
        vector<vector<int>> sol;
        int index = 1;
        niv[1] = 1;
        df(1,viz,niv,niv_min,listaAd,sol);
        return sol;
    }

};
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
