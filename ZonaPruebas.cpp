// -*- lsst-c++ -*-

/*
 * This file is part of tc2017-t1-primavera-2020-equipo-3-1
 *
 * Developed for Algorithms Design and Analysis Class.
 * See the README file at the repository's root for details of code ownership.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, 
 *
 * This program is distributed in the hope that it will help
 * this team to develop its coding habilities and understanding
 * of the Algorithm´s complexity topic. 
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>
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
        stack<string> multiplicators;
        stack<string> temporalPolys;
        smatch matches;
        vector <tuple<N,C,O,P>> info;
        string regexOE[9] = {"[\=\+\-\/\*\<\>\!\%]", "[=<>!]=", "[\|\&]{2}", "[+-]{2}", "(print)", "([\[])", "(return)", "(cout)", "(:)"};
        string forgElements[3];
        string forgElements2[3];
        string polynomLineAanalyzed;
        string multiplicator = "";
        string tempMultiplicator = "";
        string concatPolynomial;
        void ReadFileLineLine(char argv[])
        {
            string lineAnalyzed;
            ifstream file(argv);
            int numberLine = 1;
            bool Open= false;
            bool Close = false;
            while(getline(file, lineAnalyzed))
            {
                if(lineAnalyzed.find("for") != std::string::npos)
                {
                    RegFor(lineAnalyzed);
                }
                else
                {
                    polynomLineAanalyzed = to_string(RegOE(lineAnalyzed));
                }
                if(Open == true && Close == false  && lineAnalyzed.find("}") == std::string::npos )
                {
                    concatPolynomial = polynomLineAanalyzed + " +" + concatPolynomial;
                    cout<<concatPolynomial<<endl;
                }
                if(lineAnalyzed.find("{") != std::string::npos)
                {
                    multiplicator = tempMultiplicator;
                    //cout<<concatPolynomial<<endl;
                    if(multiplicators.empty())
                    {
                        Open = true;
                        multiplicators.push(multiplicator);
                    }
                    else
                    {
                        multiplicators.push(multiplicator);
                        temporalPolys.push(concatPolynomial);
                        concatPolynomial = ""; 
                    }
                }
                if(lineAnalyzed.find("}") != std::string::npos)
                {
                    cout<<multiplicators.top()<<endl;
                    Close = true;
                    concatPolynomial = "("+multiplicator+")"+"*"+"("+concatPolynomial+"0"")";
                    //cout<<concatPolynomial<<endl;
                    //string w = multiplicators.top();
                    //cout << w <<endl;
                    multiplicators.pop();
                    if(!multiplicators.empty())  
                    {
                        multiplicator = multiplicators.top();
                        concatPolynomial = temporalPolys.top() + multiplicator +"*(" + concatPolynomial;
                    }
                    else
                    {
                        //concatPolynomial = temporalPolys.top() + multiplicator +"*(" + concatPolynomial;
                    }
                }
                //Open = false;
                info.push_back(make_tuple(numberLine,lineAnalyzed,RegOE(lineAnalyzed),polynomLineAanalyzed));
                numberLine++;
            }
            for(const auto & i : info) 
            {
                cout <<get<0>(i)<<" "<<get<1>(i)<<endl;
                cout <<get<2>(i)<<" "<<get<3>(i)<<endl;
            }
        }

        /**
         * Takes RegOEAux and cycles it through all the regular expressions declared
         * at the begginnig of the class Pruebas in order to get the number of EO
         * 
         * @param str represents the line of code to be analyzed by this method in
         *      order to obtain its number of Elemental Operations.
         * 
         * @return operationCounter, which is the number of EO in the particular
         *      line being analyzed.
         * 
         * @note Two replace() methods were used as commas and periods were being 
         *      taken into considerations by the regular expressions as indicators
         *      of EO (we could not found any obvious reason to this phonomena)
         * @note The regular expressions declared at the beggining of the class Pruebas
         *      are the ones used to count the number of EO in the line
         */
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

        /**
         * Identifies and quantifies the number of Elemental Operations located
         * at every line of the file being analyzed.
         * 
         * @param index represents the index of the array containing all the regex that
         *      is being analyzed. 
         * @param str represents the line of code to be analyzed by this method in
         *      order to obtain its number of Elemental Operations.
         * @param matches keeps all the matches found by the regex in the line of code
         *      being analyzed. 
         * @param reg Regular expression to which the line of code is compareds with.
         * 
         * @return operationCounter, which is the number of EO in the particular
         *      line being analyzed.
         * 
         * @note If index is 1 or 3, the operation counter is reduced by one so that OE
         *      such as ++, --, ==, among others, are not counted as separate OEs.
         * @note If index is 8, the operation counter is increased by two as it matches
         *      with the : found in an iterator.
         * @note Any other OE will increased the operation counter by one.
         * 
         */ 
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
                        poly = "w";
                        tempMultiplicator = poly;
                    }
                    else if(forgElements2[2]!="1")
                    {
                        forgElements2[2] = forgElements2[2].substr(0,forgElements2[2].size()-1); 
                        poly = poly + to_string(RegOE(forgElements[i]))+ "*" + (forgElements2[2]) +"*"+"("+forgElements2[1]+"-"+"("+forgElements2[0]+")"+")";
                        tempMultiplicator = "("+forgElements2[2]+"* n";
                    }
                    else
                    {
                        poly = poly + to_string(RegOE(forgElements[i]))+ "*" + (forgElements2[2]) +"*"+"("+forgElements2[1]+"-"+"("+forgElements2[0]+")"+")";
                        tempMultiplicator = "("+forgElements2[1]+"-"+"("+forgElements2[0]+")"+")";
                    }  
                }
                //cout<<poly<<endl;
                polynomLineAanalyzed = poly;
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
                        j=j+1;
                    }
                    else if((vect[i].at(j)=='/'&& vect[i].at(j+1)=='=')||(vect[i].at(j)=='*'&& vect[i].at(j+1)=='='))
                    {
                        aux="log";
                        j=j+1;
                    }
                    else if((vect[i].at(j)=='<'&& vect[i].at(j+1)=='=')||(vect[i].at(j)=='>'&& vect[i].at(j+1)=='='))
                    {
                        aux=vect[i].substr(j+2,vect[i].length()-j);
                        j=j+1;
                    }
                    else if(vect[i].at(j)=='='||vect[i].at(j)=='<'||vect[i].at(j)=='>')
                    {
                        aux=vect[i].substr(j+1,vect[i].length()-j);
                    }
                    else if((vect[i].at(j)=='+'&& vect[i].at(j+1)=='+')||(vect[i].at(j)=='-'&& vect[i].at(j+1)=='-'))
                    {
                        aux="1";
                        j++;
                    }
                    forgElements2[i]=aux;
                }
            }
        }
};

/**
 * Identifies the file to be opened and analyzed by the Complexity Analzer.
 * When the analysis is finalized, it prints a formated table with information
 * (line number, code line, number of Elemental Operations and line Polynomial)
 * for each line of the file analyzed. 
 * 
 * @param argc specifies the number of elements within argv
 * @param argv is an array of c-string pointers, from which the file (name or path) is extracted
 *      to be found.
 * 
 * @return 0 (int) as we are working with the main() method of a cpp file.
 * 
 * @note This method also prints the Polynomial Time Complexity of the file previously
 * analyzed as well as the worst case Big O notation.
 */
int main(int argc, char** argv)
{
    Pruebas<int,string,int,string>P;
    P.ReadFileLineLine(argv[2]);
    return 0;
}