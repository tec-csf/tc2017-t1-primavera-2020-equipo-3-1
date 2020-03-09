#include <iostream>
#include <tuple>
#include <iomanip>
#include <cmath>
#include <thread>

using namespace std;
//tabla que impriira tupla con los 4 elementos que necesitamos para la tabla
int main(){
    tuple<string, string, string, string> i;
    tuple<string, string, string, string> a;
    tuple<string, string, string, string> b;
    tuple<string, string, string, string> c;
    get<0>(i)="1";
    get<1>(i)="int=1";
    get<2>(i)="3";
    get<3>(i)="(n+1)";
    get<0>(a)="2";
    get<1>(a)="for(isisjsijsijsijsisisjis)";
    get<2>(a)="2";
    get<3>(a)="2(n+1)";
    get<0>(b)="3";
    get<1>(b)="(cout<<teblat,bla,eb,aabamsmgon nfh metmpsmet bmsb";
    //replace(get<1>(b).begin(),get<1>(b).end(),"|", "/");
    get<2>(b)="3";
    get<3>(b)="(n)";
    get<0>(c)="4";
    get<1>(c)="i++";
    get<2>(c)="1";
    get<3>(c)="(n+1)-1";
    cout<< setw(2)<< "|No. de linea| " << setw(64)<< "|Código|" << setw(45) << "|OE|" << setw(15)<< "|Polinomio|" << endl;
    cout<<"|"<< get<0>(i) << setw(110) << get<1>(i) << setw(10) << get<2>(i) << setw(15)<< get<3>(i)<<"|" <<endl;
    cout<<"|"<< get<0>(a) << setw(110) << get<1>(a) << setw(10) << get<2>(a) << setw(15)<< get<3>(a)<<"|" <<endl;
    cout<<"|"<< get<0>(b) << setw(110) << get<1>(b) << setw(10) << get<2>(b) << setw(15)<< get<3>(b)<<"|" <<endl;
    cout<<"|"<< get<0>(c) << setw(110) << get<1>(c) << setw(10) << get<2>(c) << setw(15)<< get<3>(c)<<"|" <<endl;

}
