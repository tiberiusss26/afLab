#include <iostream>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

int main() {
    string str1 = "abac", str2 = "cab";
    auto l1 = str1.length(), l2 = str2.length();
    int sol[l1 + 1][l2 + 1];
    for (int i = 0; i <= l1; i++)
        for (int j = 0; j <= l2; j++) {
            if (i == 0 || j == 0)
                sol[i][j] = 0;
            else {
                if (str1[i - 1] == str2[j - 1])
                    sol[i][j] = sol[i - 1][j - 1] + 1;
                else sol[i][j] = max(sol[i - 1][j], sol[i][j - 1]);
            }
        }

    string cuv;
    auto i = l1, j = l2;
    while (i > 0 || j > 0) {
        if (i == 0 && j != 0) {
            while (j != 0)
                cuv += str2[--j];
            break;

        }
        if (i != 0 && j == 0) {
            while (i != 0)
                cuv += str1[--i];
            break;
        }
        if (str1[i - 1] == str2[j - 1]) {
            cuv += str1[i - 1];
            i--;
            j--;
        } else if (sol[i - 1][j] > sol[i][j - 1]) {
            cuv += str1[i - 1];
            i--;
        } else {
            cuv += str2[j - 1];
            j--;
        }
    }
    reverse(cuv.begin(), cuv.end());
    cout << cuv;
}
