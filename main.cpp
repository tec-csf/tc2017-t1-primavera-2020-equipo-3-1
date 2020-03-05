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
    system("sudo apt-get install python3.7");
    system("python --version");
    system("sudo apt-get install python3-pip");
    system("pip3 install python-scipy");
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
    cout<<"hola1"<<endl;
}
