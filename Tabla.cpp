#include <iostream>
#include <iomanip>

using namespace std;
string noLinea;
string noLinea2;
string noLinea3;
string noLinea4;
string oe;
string oe2;
string oe3;
string oe4;
string codigo;
string codigo2;
string codigo3;
string codigo4;
string polinomio;
string polinomio2;
string polinomio3;
string polinomio4;
string polired;
string complejidad;
string je = "printf(“El elemento ;";

int main(){
  noLinea= "1";
  noLinea2="2";
  noLinea3="3";
  noLinea4="4";
  oe="1";
  oe2="1";
  oe3="1";
  oe4="1";
  codigo= "int i = 0;";
  codigo2= "while (i < n)";
  codigo3= je;
  codigo4= "++i";
  polinomio = "1";
  polinomio2 = "(n+1)";
  polinomio3 = "n";
  polinomio4 = "n";
  polired = "3n+2";
  complejidad = "O(n)";
  cout<< "No. de linea " << "\t\t\t\t"<< "Código" << "\t\t\t\t" << "OE" << "\t\t\t\t" "Polinomio" << "\t\t\t\t\n"<<endl;
  cout<< noLinea << "\t\t\t\t" << codigo << "\t\t\t\t" << oe << "\t\t\t\t" << polinomio << "\t\t\t\t" <<endl;
  cout<< noLinea2 << "\t\t\t\t" << codigo2 << "\t\t\t\t" << oe2 << "\t\t\t\t"<< polinomio2 << "\t\t\t\t" <<endl;
  cout<< noLinea3 << "\t\t\t\t" << codigo3 << "\t\t\t\t" << oe3 << "\t\t\t\t"<< polinomio3 << "\t\t\t\t" <<endl;
  cout<< noLinea4 << "\t\t\t\t" << codigo4 << "\t\t\t\t" << oe4 << "\t\t\t\t"<< polinomio4 << "\t\t\t\t" <<endl;


  /*cout<< setw(5)<< "No. de linea " << setw(15)<< "Código" << setw(20) << "OE" << setw(20)<< "Polinomio" << endl;
  cout<< setw(7) << noLinea << setw(25) << codigo << setw(15) << oe << setw(20)<< polinomio <<endl;
  cout<< setw(7) << noLinea2 << setw(25) << codigo2 << setw(15) << oe2 << setw(20)<< polinomio2 <<endl;
  cout<< setw(7) << noLinea3 << setw(25) << codigo3 << setw(15) << oe3 << setw(20)<< polinomio3 <<endl;
  cout<< setw(7) << noLinea4 << setw(25) << codigo4 << setw(15) << oe4 << setw(20)<< polinomio4 <<endl;*/


  cout<< "Polinomio: T(n) =" <<polired <<endl;
  cout<< "Complejidad:"<< complejidad<<endl;
  
  //meter en matrices los resultados
  //son 4 datos
  //no de linea y código van juntas
  //oe y polinomio van juntas
  //reduccion pasar directo de Pyhton
  //complejidad = el indice mayor del polinomio reducido
}