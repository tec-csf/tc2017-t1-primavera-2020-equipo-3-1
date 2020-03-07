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
        string forgElements[3];
        string forgElements2[3];
        void ReadFileLineLine(char argv[])
        {
            string lineAnalyzed;
            ifstream file(argv);
            int numberLine = 1;
            while(getline(file, lineAnalyzed))
            {
                if(lineAnalyzed.at(0)=='f')
                {
                    RegFor(lineAnalyzed);
                }
                info.push_back(make_tuple(numberLine,lineAnalyzed,RegOE(lineAnalyzed),"n+2"));
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
        void RegFor(string str)
        {
            regex regFor("(for[ ]?\\((.*)\\))");
            string poly;
            replace(str.begin(), str.end(), (','), ' ');
            replace(str.begin(), str.end(), ('.'), ' ');
            if(regex_search(str, matches, regFor))
            {
                RegForAux(str);  
            }
            checkTimes(forgElements);
            for(int i = 0; i<3; i++)
            {
                char temp[10];
                if(i==0)
                {
                    poly = poly + to_string(RegOE(forgElements[i])) +strcat(temp,"+");
                }
                else if (i==1)
                {
                    poly = poly + to_string(RegOE(forgElements[i]))+"*"+"(" + forgElements2[1]+ "+ 1" + " -" +"("+forgElements2[0]+")" +")"+ "+";
                }
                else
                {
                    if(forgElements2[2]=="log")
                    {
                        poly = "w*";
                    }
                    else
                    {
                        poly = poly + to_string(RegOE(forgElements[i]))+ "*" + (forgElements2[2]) +"*"+"("+forgElements2[1]+"-"+"("+forgElements2[0]+")"+")";
                    }  
                }
                cout<<poly<<endl;
            }
        }
        void RegForAux(string str)
        {
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
                    correctBeginning = aux.find_first_not_of(' ') || aux.find_first_not_of('(');
                    aux = aux.substr(correctBeginning, number);
                    forgElements[arrayCounter] = aux;

                    //cout<<forgElements[arrayCounter]<<endl;

                    arrayCounter++;
                    cont=i+1;
                }
            }
            number=str.length()-2-cont;
            aux = str.substr(cont,number);  
            correctBeginning = aux.find_first_not_of(' ');
            aux = aux.substr(correctBeginning, number);
            forgElements[2] = aux;
            //cout<<forgElements[2]<<endl;
        }
        void checkTimes(string vect[3])
        {
            string aux="";
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<vect[i].length();j++)
                {
                    if((vect[i].at(j)=='+'&& vect[i].at(j+1)=='=')||(vect[i].at(j)=='-'&& vect[i].at(j+1)=='='))
                    {
                        aux=vect[i].substr(j+2,vect[i].length()-j);
                        aux="1/"+aux;
                        //cout<<aux<<endl;
                        j=j+1;
                    }
                    else if((vect[i].at(j)=='/'&& vect[i].at(j+1)=='=')||(vect[i].at(j)=='*'&& vect[i].at(j+1)=='='))
                    {
                        aux="log";
                        //cout<<aux<<endl;
                        j=j+1;
                    }
                    else if((vect[i].at(j)=='<'&& vect[i].at(j+1)=='=')||(vect[i].at(j)=='>'&& vect[i].at(j+1)=='='))
                    {
                        aux=vect[i].substr(j+2,vect[i].length()-j);
                        //cout<<aux<<endl;
                        j=j+1;
                    }
                    else if(vect[i].at(j)=='='||vect[i].at(j)=='<'||vect[i].at(j)=='>')
                    {
                        aux=vect[i].substr(j+1,vect[i].length()-j);
                        //cout<<aux<<endl;
                    }
                    else if((vect[i].at(j)=='+'&& vect[i].at(j+1)=='+')||(vect[i].at(j)=='-'&& vect[i].at(j+1)=='-'))
                    {
                        aux="1";
                        //cout<<aux<<endl;
                        j++;
                    }
                    forgElements2[i]=aux;
                }
            }
        }
};

int main(int argc, char** argv)
{
    Pruebas<int,string,int,string>P;
    P.ReadFileLineLine(argv[2]);
    return 0;
}