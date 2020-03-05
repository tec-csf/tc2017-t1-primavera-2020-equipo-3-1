#include <stdlib.h>
#include <string>
#include <fstream>
#include<iostream>
using namespace std;

int main()
{
    string line;
    ifstream myfile;
    string aux;
    string cadena = "python polinomiosimp.py";
    system("python --version");
    system("python3 polinomiosimp.py 2*n*2+1+2*n2+n*2");
    myfile.open ("file.txt");
    if (myfile.is_open())
    {
        while ( getline(myfile,line) )
        {
            aux=line;
        }
        myfile.close();
    }
    myfile.close();
    cout<<"hola"<<endl;
}
