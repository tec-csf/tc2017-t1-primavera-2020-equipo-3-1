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

template <class N, class C, class O, class P> 
class Pruebas
{
    public:
        smatch matches;
        vector <tuple<N,C,O,P>> info;
        string regexOE[9] = {"[\=\+\-\/\*\<\>\!\%]", "[=<>!]=", "[\|\&]{2}", "[+-]{2}", "(print)", "([\[])", "(return)", "(cout)", "(:)"};
        void ReadFileLineLine(char argv[])
        {
            string lineAnalyzed;
            ifstream file(argv);
            int numberLine = 1;
            while(getline(file, lineAnalyzed))
            {
                info.push_back(make_tuple(numberLine,lineAnalyzed,RegOE(lineAnalyzed),"n+2"));
                //RegFor(lineAnalyzed);
                numberLine++;
            }
            for(const auto & i : info) 
            {
                cout <<get<0>(i)<<" "<<get<2>(i)<<endl;
                //cout <<get<2>(i)<<" "<<get<3>(i)<<endl;
            }
        }
        int RegOE(string str)
        {
            int operationCounter = 0;
            replace(str.begin(), str.end(), (','), ' ');
            replace(str.begin(), str.end(), ('.'), ' ');
            int temp=0;
            for(int i = 0; i<9; i++)
            {
                operationCounter += RegOEAux(i, str, matches, regex(regexOE[i]));
            }
            return operationCounter;
        }
        int RegOEAux(int index, string str, smatch matches, regex reg)
        {
            int operationCounter = 0;
            while(regex_search(str, matches, reg))
            {
                if((index == 1) || (index == 3))
                {
                    str = matches.suffix().str();
                    operationCounter--;
                }
                else if(index == 8)
                {
                    str = matches.suffix().str();  
                    operationCounter+=2;  
                }
                else
                {
                    str = matches.suffix().str();
                    operationCounter++;
                }
            }
            return operationCounter;
        }
        bool RegFor(string str)
        {
            string poly;
            string *tempForElements;
            regex regFor("(for\\((.*)\\))");
            replace(str.begin(), str.end(), (','), ' ');
            replace(str.begin(), str.end(), ('.'), ' ');
            while(regex_search(str, matches, regFor))
            {
                tempForElements = RegForAux(matches.str(0));
                str = matches.suffix().str();
            }
            for(int i = 0; i<3; i++)
            {
                char temp[10];
                sprintf(temp, "%d", RegOE(*(tempForElements+i)));
                poly = poly + strcat(temp,"+");
                cout<<poly<<endl;
            }
        }
        string * RegForAux(string str)
        {
            static string forElements[3];
            string aux="";
            int arrayCounter = 0;
            
            int cont=4;
            int number;
            int correctBeginning;
            int correctEnding;
            for(int i=4;i<str.length();i++)
            {
                if(str.at(i)==';')
                {
                    number=i-cont;
                    aux=str.substr(cont, number);
                    correctBeginning = aux.find_first_not_of(' ');
                    aux = aux.substr(correctBeginning, number);
                    forElements[arrayCounter] = aux;
                    arrayCounter++;
                    cont=i+1;
                }
            }
            number=str.length()-1-cont;
            aux = str.substr(cont,number);  
            correctBeginning = aux.find_first_not_of(' ');
            aux = aux.substr(correctBeginning, number);
            forElements[2] = aux;

            return forElements;
        }
};

int main(int argc, char** argv)
{
    Pruebas<int,string,int,string>P;
    P.ReadFileLineLine(argv[2]);
    return 0;
}