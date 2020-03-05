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
    system("sudo apt-get update");
    system("sudo apt-get install python3-pip3");
    system("pip install --user sympy");
    system("python polinomiosimp.py 2*n**2 +2*n**2");
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
    cout<<line<<endl;
}
