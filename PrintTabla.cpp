#include <iostream>
#include <tuple>
#include <iomanip>
using namespace std;
//tabla que impriira tupla con los 4 elementos que necesitamos para la tabla
int main(){
    tuple<string, string, string, string> i;
    get<0>(i)="1";
    get<1>(i)="for(nvvinw{evnwnt)";
    get<2>(i)="3";
    get<3>(i)="(n+1)";
    cout<< setw(2)<< "No. de linea " << setw(45)<< "Código" << setw(40) << "OE" << setw(40)<< "Polinomio" << endl;
    cout<< setw(7)<< get<0>(i) << setw(50) <<get<1>(i) << setw(40) <<get<2>(i) << setw(40) <<get<3>(i) <<endl;

}