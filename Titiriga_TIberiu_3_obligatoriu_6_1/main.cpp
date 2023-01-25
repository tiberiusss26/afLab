#include <iostream>
#include <string>

using namespace std;


int main() {
    string c1 = "abcde", c2 = "ace";
    int k = 0;
    int sol[c1.length()][c2.length()];
    for (int i = 0; i < c1.length(); i++)
        for (int j = 0; j < c2.length(); j++)
            sol[i][j] = 0;

    for (int i = 0; i < c1.length(); i++) {
        if (c1[i] == c2[0]) sol[i][0] = 1;
        else sol[i][0] = sol[i-1][0];
    }
    for (int i = 0; i < c2.length(); i++)
        if (c1[0] == c2[i]) sol[0][i] = 1;
    else sol[0][i] = sol[0][i-1];


    for (int i = 1; i < c1.length(); i++) {
        for (int j = 1; j < c2.length(); j++)
            if (c1[i] == c2[j]) sol[i][j] = sol[i - 1][j - 1] + 1; else sol[i][j] = max(sol[i - 1][j], sol[i][j - 1]);
    }

    for (int i = 0; i < c1.length(); i++) {
        for (int j = 0; j < c2.length(); j++)
            cout << sol[i][j] << " ";
        cout << endl;
    }

}
