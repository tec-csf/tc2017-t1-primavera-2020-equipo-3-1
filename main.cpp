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
    string cadena = "(2*n**2)*(n**2)";
    ofstream outFile;
    outFile.open("file.txt");
    outFile<<cadena<<endl;
    outFile.close();
    system("sudo apt-get update");
    system("sudo apt-get install python3-pip3");
    system("pip install --user sympy");
    system("python polinomiosimp.py");
    myfile.open ("file.txt");
    if (myfile.is_open())
    {
        while (getline(myfile,line) )
        {
            aux=line;
        }
    }
    myfile.close();
    cout<<aux<<endl;
}
