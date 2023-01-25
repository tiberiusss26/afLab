#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int minim = 1000000;

ifstream f("padure.in");
ofstream g("padure.out");

int bfs(int linStart, int colStart, int cl, int cc, vector<vector<int>>& vizita, int& minim){
    queue<pair<int,int>> coada;
    vizita[linStart][colStart] = 1;
    coada.push(make_pair(linStart, colStart));

    int i,j;

    while(!coada.empty()){

    }

}

int main() {
    int n, m, pl, pc, cl, cc;
    f >> n >> m >> pl >> pc >> cl >> cc;
    vector<int> gol(m + 1);
    vector<vector<int>> padure(n + 1, gol), vizita(n+1,gol);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            f >> padure[i][j];


}
