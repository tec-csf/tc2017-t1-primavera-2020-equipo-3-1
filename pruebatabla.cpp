#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <regex>
#include <ctime>
#include <numeric>
#include <cmath>
#include <thread>


using namespace std;

string noLinea;
string noLinea2;
string oe;
string oe2;
string codigo;
string codigo2;
string polinomio;
string polinomio2;
string polired;
string complejidad;

int main(){

  noLinea= "1";
  noLinea2="2";
  oe="1";
  oe2="1";
   codigo= "int i = 0;";
  codigo2= "for(c=0,i=8\n;c<i;c++awnfjwqnnwrfnqernversgfj)";
  replace(codigo2.begin(),codigo2.end(),'\n', 'n');
 polinomio = "1";
  polinomio2 = "(n+1)";
    polired = "3n+2";
  complejidad = "O(n)";

    cout<< setw(2)<< "No. de linea " << setw(45)<< "Código" << setw(40) << "OE" << setw(40)<< "Polinomio" << endl;
  cout<< setw(7) << noLinea << setw(50) << codigo << setw(40) << oe << setw(40)<< polinomio <<endl;
  cout<< setw(7) << noLinea2 << setw(50) << codigo2 << setw(40) << oe2 << setw(40)<< polinomio2 <<endl;
  cout<< "Polinomio: T(n) =" <<polired <<endl;
  cout<< "Complejidad:"<< complejidad<<endl;
}