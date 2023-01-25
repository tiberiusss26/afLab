#include <iostream>
#include <fstream>

using namespace std;

ifstream f("disjoint.in");
ofstream g("disjoint.out");


class multDisjuncta {
    int *rang, *tata, n;
public:
    multDisjuncta(int n) {
        this->n = n;
        rang = new int[n + 1];
        tata = new int[n + 1];
        creeazaMultimea();
    }

    //initial avem cate o multime pentru fiecare numar
    void creeazaMultimea() {
        for (int i = 1; i <= n; i++)
            tata[i] = i;
    }

    //daca x coincide cu tatal sau am ajuns la radacina
    //altfel parcurgem in sus pana ajungem la tata
    int gaseste(int x) {
        if (tata[x] != x)
            tata[x] = gaseste(tata[x]);

        return tata[x];
    }

    //facem merge ul intre multimile lui x si y
    // cautam radacinile fiecarui numar
    void merge(int x, int y) {
        int xMult = gaseste(x);
        int yMult = gaseste(y);

        // daca cele doua numeral fac parte din aceeasi multime nu facem nimic
        if (xMult == yMult)
            return;

        //daca apartin unor multimi diferite
        // alipim multimea cu rang mai mic la cea cu rang mai mare
        if (rang[xMult] < rang[yMult])
            tata[xMult] = yMult;

        else if (rang[xMult] > rang[yMult])
            tata[yMult] = xMult;
        // daca ambele multimi au ranguri egale
        // o alipim by default pe a doua la prima si ii crestem rangul primei
        else {
            tata[yMult] = xMult;
            rang[xMult]++;
        }
    }

    void executa(int m){
        for(int i =0;i<m;i++){
            int a,b,c;
            f>>a>>b>>c;
            if(a==1){
                merge(b,c);
            }
            if(a==2){
                if(gaseste(b)!= gaseste(c))
                    g<<"NU\n";
                else g<<"DA\n";
            }
        }
    }

    ~multDisjuncta() {}
};

int main() {
    int n,m;
    f>>n>>m;
    multDisjuncta a(n);
    a.executa(m);
}
