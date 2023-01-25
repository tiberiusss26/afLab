#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

unordered_map<string,vector<pair<string,char>>> listaAd;
unordered_map<string,int> in,out;
string lant;

void dfs(string &c){
    while (!listaAd[c].empty()){
        string nod = listaAd[c].back().first;
        char lit = listaAd[c].back().second;
        listaAd[c].pop_back();
        dfs(nod);
        lant.push_back(lit);
    }
}
int main() {
    int n,k,grad=0;
    string cuv;
    char lit;
    cin>>n>>k;
    for (int i = 0; i < n; ++i) {
        cin >> cuv;
        string pref = cuv.substr(0, k - 1);
        string suf = cuv.substr(1);
        lit = k == 1 ? cuv[0] : suf.back();
        listaAd[pref].push_back(make_pair(suf, lit));
        out[pref]++;
        in[suf]++;
    }
    cuv=listaAd.begin()->first;
    for(auto &i:out){
        if(i.second != in[i.first]){
            grad++;
            if(grad>2){
                cout<<-1;
                return 0;
            }
            if(i.second==in[i.first]+1){
                cuv=i.first;
            }
        }
    }
    dfs(cuv);
    for (int i = cuv.size()-1; i >=0 ; --i) {
        lant.push_back(cuv[i]);
    }
    if(lant.size()!=n+k-1){
        cout<<-1;
        return 0;
    }
    reverse(lant.begin(),lant.end());
    cout<<lant;
    return 0;
}
