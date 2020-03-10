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
#include <iomanip>

using namespace std;

template <class N, class C, class O, class P> 
class Pruebas
{
    public:
        smatch matches;
        vector <tuple<N,C,O,P>> info;
        vector <string> lines;
        vector <string> variableAssignations;
        string regexOE[9] = {"[\=\+\-\/\*\<\>\!\%]", "[=<>!]=", "[\|\&]{2}", "[+-]{2}", "(print)", "([\[])", "(return)", "(cout)", "(:)"};
        string forgElements[3];
        string forgElements2[3];
        string polynomLineAanalyzed;
        string tempMultiplicator = "";
        string concatPolynomial = "";
        string finalPolunomial = "";

        /**
         * This method was created so the necessary installations regarding python and pip can be performed
         * in order to be able to simplify the polynomials presented by this Complexity Analyzer.
         * 
         * @note No parameters and no return values are expetec by this method.
         * @note Contain the lines of text that the command line (either in Travis or in a physical machine)
         *      will have to execute to set up Python for a correct performance of this program.
         * 
         */
        void InstallPython()
        {
            system("sudo apt-get update");
            system("sudo apt-get install python3-pip3");
            system("pip3 install --user sympy");
        }

        /**
         * This method sends each polynomial created or developed by this program to be analyzed, solved and
         * reduced by the Python file "polinomiosimp.py"
         * 
         * @param poly is the line (defined as a string datatype) that will be sent to the Python file
         *      aforementioned to be analyzed,
         * 
         * @return returns the polynomial (may be with constant, lineal or any other complexity) in a simplified 
         *      and clear way so the final user can understand it.  
         * 
         * @note In order to achieve this analysis, each line has to be saved in a .txt file that will be loaded
         *      in its propper time by the Python file to be analyzed and simplified.
         * 
         */
        string SendToPython(string poly)
        {
            string line;
            string aux;
            ifstream myfile;
            ofstream outFile;
            outFile.open("file.txt");
            outFile<<poly<<endl;
            outFile.close();
            system("python3 polinomiosimp.py");
            myfile.open ("file.txt");
            if (myfile.is_open())
            {
                while (getline(myfile,line) )
                {
                    aux=line;
                }
            }
            myfile.close();
            return aux;
        }

        /**
         * This method reads the file specified by the user to be analyzed and saves each line as an
         * element of a vector made up strings
         * 
         * @param argv is an array of c-string pointers, from which the file (name or path) is extracted
         *     to be found.
         * 
         * @note This method is perfored before the actual analysis of the code and its operations. It is
         *      done so further analysis focused on the if, else and while structures can be done easily.
         * @note The vector in which the line are saved is declared with a global scope inside the class.
         * 
         */
        void SaveLinesIntoVector(char argv[])
        {
            ifstream reader(argv);
            string lineToBeSaved;
            int counter = 0;
            while(getline(reader, lineToBeSaved))
            {
                if(lineToBeSaved.find("=") != std::string::npos || lineToBeSaved.find("++") != std::string::npos || lineToBeSaved.find("--") != std::string::npos)
                {
                    variableAssignations.push_back(lineToBeSaved);
                }
                lines.push_back(lineToBeSaved);   
                counter++;
            }
            for(const auto & i : variableAssignations) 
            {
                //cout<<i<<endl;
            }
        }

        void ReadFileLineLine(char argv[])
        {
            int flag = 0;
            string lineAnalyzed;
            string lineTableFor;
            string variableToSearch;
            ifstream file(argv);
            int numberLine = 1;
            regex regFor("((.*)?\\})");
            regex regFor2("((.*)?\\{)");
            regex regWhile("(while[ ]?\\((.*)\\))");
            int correctBegginig = 0;
            while(getline(file, lineAnalyzed))
            {
                if(lineAnalyzed.find("else if") != std::string::npos)
                {
                    checkBrackets(numberLine, variableToSearch);
                }
                else if(lineAnalyzed.find("if") != std::string::npos)
                {
                    checkBrackets(numberLine, variableToSearch);
                }  
                else if(lineAnalyzed.find("else") != std::string::npos)
                {
                    checkBrackets(numberLine, variableToSearch);
                }
                else if(regex_search(lineAnalyzed, matches, regWhile))
                {
                    lineAnalyzed = lineAnalyzed.substr((lineAnalyzed.find_first_not_of(' ')||lineAnalyzed.find_first_not_of('\t')), lineAnalyzed.length()-1);
                    if(lineAnalyzed.at(6)=='(')
                    {
                        //cout<<"MIKE LO TIENE ROTO"<<endl;
                        string parenthesisContent = lineAnalyzed.substr(7, lineAnalyzed.length()-2-7);
                        //cout<<parenthesisContent<<endl;
                        if(parenthesisContent.substr(((parenthesisContent.find("<=")||parenthesisContent.find(">=")||parenthesisContent.find("!=")||parenthesisContent.find("=="))+2)) != "")
                        {
                            variableToSearch = parenthesisContent.substr(((parenthesisContent.find("<=")||parenthesisContent.find(">=")||parenthesisContent.find("!=")||parenthesisContent.find("=="))+2));
                        }
                        else
                        {
                            variableToSearch = parenthesisContent.substr(((parenthesisContent.find("<")||parenthesisContent.find(">"))+1));
                        }
                        //cout<<parenthesisContent.substr(((parenthesisContent.find("<=")||parenthesisContent.find(">=")||parenthesisContent.find("!=")||parenthesisContent.find("=="))+2))<<endl;
                        //cout<<parenthesisContent.substr(((parenthesisContent.find("<")||parenthesisContent.find(">"))+1))<<endl;
                        //cout<<variableToSearch<<endl;
                    }
                    //cout<<"WHILE"<<endl;
                    checkBrackets(numberLine, variableToSearch);
                }  
                if(lineAnalyzed.find("for") != std::string::npos)
                {
                    RegFor(lineAnalyzed);
                    polynomLineAanalyzed= polynomLineAanalyzed + "*" + forgElements2[2] + "*";
                    lineTableFor = forgElements2[0]+ "+" + forgElements2[1]+ "+" +forgElements2[2];
                }
                else
                {
                    polynomLineAanalyzed = to_string(RegOE(lineAnalyzed));
                    lineTableFor = polynomLineAanalyzed;
                }
                if(regex_search(lineAnalyzed, matches, regFor2) && flag==0)
                {
                    flag++;
                    finalPolunomial = finalPolunomial + "+1*(";
                }
                else if(regex_search(lineAnalyzed, matches, regFor2) && flag!=0)
                {
                    finalPolunomial = finalPolunomial + "+1*(";
                }
                
                if(regex_search(lineAnalyzed, matches, regFor))
                {
                    finalPolunomial = finalPolunomial + ")";
                }
                else
                {
                    finalPolunomial = finalPolunomial + "+" + polynomLineAanalyzed;
                    //cout<<finalPolunomial<<endl;
                }
                info.push_back(make_tuple(numberLine,lineAnalyzed,RegOE(lineAnalyzed),lineTableFor));
                numberLine++;
            }
            //finalPolunomial = finalPolunomial;
            //cout<< setw(2)<< "|No. de linea| " << setw(40)<< "|Código|" << setw(45) << "|OE|" << setw(50)<< "|Polinomio|" << endl;
            cout<<"--------------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout<< setw(2)<< "|No. de linea| " << setw(49)<< "Código" << setw(40) << "|OE|" << setw(16)<<"Polinomio"<<setw(9)<<"|" << endl; 
            cout<<"--------------------------------------------------------------------------------------------------------------------------------"<<endl;
            for(const auto & i : info) 
            {
                string temp = get<3>(i);
                temp= SendToPython(temp);
                cout<<"|"<< get<0>(i) << setw(90) << get<1>(i)<< setw(8) <<"|"<< get<2>(i) <<" |"<< setw(24)<< temp<<"|" <<endl;
                //cout<<"|"<<setw(1)<<get<1>(i)<<setw(50)<<get<2>(i)<<setw(60) << get<3>(i)<< setw(8)<< get<0>(i)<<"|" <<endl;
                //cout<<"|"<< get<0>(i) << setw(110) << get<1>(i) << setw(10)<<endl << get<2>(i) << setw(15)<< get<3>(i)<<"|" <<endl;
                
                //cout <<get<0>(i)<<" "<<get<1>(i)<<endl;
                //cout <<get<2>(i)<<" "<<temp<<endl;
            }
            //cout<<finalPolunomial<<endl;
            //cout<<SendToPython(finalPolunomial)<<endl;
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

        /**
         * With the help of RegForAux, it concatenates the number of operations found in each
         * component of any FOR structure (setup; test expression; increment).
         * 
         * @param str represents the line of code (FOR) to be analyzed by this method in
         *      order to obtain its number of Elemental Operations.
         * 
         * @note 
         * @note polynomLineAanalyzed (with a greater scope than any variable inside of this method)
         *      receives the value of the polynomial created by the three groups of operations in the FOR
         *      structure
         * @note RegFor serves more like a concatenator; RegForAux is the method that actually counts
         *      the number of EO in the code line with this structure.
         * 
         */
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
                polynomLineAanalyzed = poly;
            }
        }

        /**
         * RegForAux is in charge of identifying and adding the number of Elemental Operations
         * found in any FOR structure in the piece of code introduced by the user.
         * 
         * @param str represents the line of code (FOR) to be analyzed by this method in
         *      order to obtain its number of Elemental Operations.
         * 
         * @note This function divides any FOR structure into three parts (setuo, test exp. and increment)
         *      as each of these components requiere a different "treatament" in order to get the number
         *      of OE in each element of the structure
         * @note RegForAux works alligned with the RegFor method for the correct analysis of FORs.
         * 
         */
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

                    arrayCounter++;
                    cont=i+1;
                }
            }
            number=str.length()-2-cont;
            aux = str.substr(cont,number);  
            correctBeginning = aux.find_first_not_of(' ');
            aux = aux.substr(correctBeginning, number);
            forgElements[2] = aux;
        }

        /**
         * Methos used to identify the number of time a certain loop structure will be performed;
         * Lineal, (n/something) or Logharitmic options are possible.
         * 
         * @param vect[3] The increment segment of a FOR structure is kept in this parameter to later 
         *      be concatenated in the finaly polynomial to be printed by this program.
         * 
         * @note If a += or -= is found by this method, the FOR structure will be assigned a 1/aux number
         *      of time to be repated; *= or /= results in a log number of times and ++ or -- in a lineal (n)
         *      number of times.
         * 
         */ 
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
        void checkBrackets(int lineNumber, string searchStr)
        {
            //string vect[6]={value1,value2,value3,value4,value5,value6};
            int contLI=0;
            int contLC=0;
            int cont=0;
            for(int i=lineNumber;i<lines.size();i++)
            {
                //cout<<searchStr<<endl;
                //cout<<lines.at(i)<<endl;
                if(lines.at(i).find(searchStr) != std::string::npos && lines.at(i).find(("++")||("--")) != std::string::npos)
                {
                    cout<<searchStr + "+1"<<endl;
                }
                else if(lines.at(i).find(searchStr) != std::string::npos && lines.at(i).find(("*=")||("/=")) != std::string::npos)
                {
                    cout<<"log"<<endl;
                }
                else if(lines.at(i).find(searchStr) != std::string::npos && lines.at(i).find(("+=")||("-=")) != std::string::npos)
                {
                    cout<<"1/n"<<endl;
                }
                if(lines.at(i).find("{") != std::string::npos)
                {
                    contLI++;
                }
                else if(lines.at(i).find("}") != std::string::npos)
                {
                    contLC++;
                }
                cont++;
                if(contLC==contLI&&(contLC!=0&&contLI!=0))
                {
                    break;
                }
            }
            //cout<<cont<<endl;
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
    P.InstallPython();
    P.SaveLinesIntoVector(argv[2]);
    P.ReadFileLineLine(argv[2]);
    return 0;
}
