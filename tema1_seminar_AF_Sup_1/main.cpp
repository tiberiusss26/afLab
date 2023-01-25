#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int dfs(int i,int j, vector<vector<int>>& sol, vector<vector<int>>& grid){
        if(i<0 || j<0 || i>=grid.size() || j>= grid[0].size()) return 0;
        if(grid[i][j]==1 && sol[i][j]==0){
            sol[i][j]=1;
            return 1 + dfs(i-1,j, sol, grid) + dfs(i+1,j,sol,grid) +dfs(i,j-1,sol,grid) +dfs(i,j+1,sol,grid);
        }
        else return 0;
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int max = 0;
        int n = grid.size();
        int m = grid[0].size();
        vector<int>line(m,0);
        vector<vector<int>>viz(n, line);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(grid[i][j] == 1 && viz[i][j] == 0)
                {
                    int rez = dfs(i,j,viz,grid);
                    if (rez > max)
                        max = rez;

                }
        return max;
    }
};

int main() {
    vector<vector<int>>grid;

}
