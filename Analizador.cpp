#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <thread>
#include <regex>
#include <ctime>
#include <numeric>
#include <cmath>

using namespace std;

/*void printLineByLine()
{
    string line;
    string correctedLine;
    int lineNumber = 1;
    int correctBeginning;
    int correctEnding;
    ifstream file("Analizador.cpp");
    
    if(file.is_open())
    {
        while(getline(file,line))
        {
            correctBeginning = line.find_first_not_of(' ');
            correctEnding = line.find_last_not_of(' ');
            correctedLine = line.substr(correctBeginning, correctEnding);
            cout<<"Line "<< lineNumber << ": " << correctedLine << '\n';
            lineNumber++;
        }
        file.close(); 
    }
    else
    {
        cout<<"file is not open"<<'\n';
    }
}*/

void RegrexPlus2(string str, regex regexarr[])
{
    smatch matches;
    int operationCounter = 0;
    for(int i=0; i<7; i++)
    {
        if(i==3)
        {
            while(regex_search(str, matches, regexarr[i]))
            {
                str = matches.suffix().str();
                operationCounter+=2;
                cout<<operationCounter<<endl;
            }
        }
        else
        {
            while(regex_search(str, matches, regexarr[i]))
            {
                str = matches.suffix().str();
                operationCounter+=1;
                cout<<operationCounter<<endl;
            }
        }
    }
}

int main()
{
    regex reg ("[^<>!=+-]+[=+-\/\*<>!%](?![+-=])");
    regex reg2 ("[=<>!]=");
    regex reg3 ("[+\|\&-]{2}");
    regex reg4 ("[+-\/\*]=");
    regex reg5 ("(print)"); //falta el return
    regex reg6 ("(?:[\[]|([\]])|(\=))(?![=])"); //(number of repetitions%2)-1 = 0 para que sea TRUE HACER EXCEPTION PARA OPERACIONES = 1
    regex reg7 ("(return)");
    regex reg8 ("(cout)");

    regex regexWhile ("(while\\(([^ ]+)\\))");

    regex arrayRegs[8] = {reg, reg2, reg3, reg4, reg5, reg6, reg7, reg8};

    string completes = "for(int = 0; a>b; i++) ";
    
    RegrexPlus2(completes, arrayRegs);

    return 0;
}
