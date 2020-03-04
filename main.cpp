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
    system("apt install python3.6");
    system("apt-get install python3-pip");
    system("pip3 install sympy");
    system("python3 polinomiosimp.py 2*n**2+1+2*n**2+n**2");
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
    cout<<aux<<endl;
}