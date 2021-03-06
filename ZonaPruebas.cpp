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
 * of the AlgorithmÂ´s complexity topic. 
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

/**
 * Storage for all the information regarding each line of code analyzed by the program
 * 
 * @param N Number of line will be kept here.
 * @param C Line of code in turn will be kept here.
 * @param O Number of Elemental Operations are kept here.
 * @param P Polynomial fot the line analyzed is kept here.
 */
template <typename N, typename C, typename O, typename P> 

/**
 * Implementation of the "Pruebas" class to analyze and print the information regarding
 * a code introduce by the user.
 * 
 * Different methods controlling the counter of Elemental Operations, the type of structure
 * present in the line in turn (for instance, a for) and the printing of the aforementioned
 * info are present in the class Pruebas. Several libraries used for the mathematical and string
 * analysis are implemented by the Pruebas class.
 * 
 */ 
class Pruebas
{
    public:
        smatch matches;
        vector <tuple<N,C,O,P>> info;
        vector <string> lines;
        vector <string> variableAssignations;
        string regexOE[9] = {"[\=\+\-\/\*\<\>\!\%]", "[=<>!]=", "[\|\&]{2}", "[+-]{2}", "(print)", "([\[])", "(return)", "(cout)", "(:)"};
        string forgElements[3];  //Used for the OE count in FOR structures
        string forgElements2[3]; //Used for the complexity polynomial in FOR structures 
        string polynomLineAanalyzed;
        string tempMultiplicator = "";
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
            system("sudo apt-get install python3-pip");
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
            ifstream myfile; //File that enters the Python program containing the time polynomial without math manipulation
            ofstream outFile; // File that exits the Python program with the time polynomial already simplified
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
        }

        /**
         * Method that plays the role of the central controller of all the program. In it, diverse
         * methods and fucntions are called depending on the type of line being analyzed (loops for instance);
         * countability for the Elemental Operations, printing of the information regarding the complexity and 
         * invocation of methods to manage the polynomial of the complete code are managed here
         * 
         * @param argv is an array of c-string pointers, from which the file (name or path) is extracted
         *     to be found.
         * 
         * @note Due to the way in which the information of each line is saved (vector of tuples with 4 elements),
         *      the format of our table diverges with the one suggested in the Canvas Task. However, all the requiered
         *      information for the analysis of the code is presented. 
         */
        void ReadFileLineLine(char argv[])
        {
            int flag = 0;
            string lineAnalyzed;
            string lineTableFor; //Used for the printing section in this method
            string variableToSearch;
            ifstream file(argv);
            int numberLine = 1;
            regex regFor("((.*)?\\})");
            regex regFor2("((.*)?\\{)");
            regex regWhile("(while[ ]?\\((.*)\\))");
            int correctBegginig = 0; //Variable used for format elements regarding spaces and tabs (\t)
            while(getline(file, lineAnalyzed))
            {
                if(regex_search(lineAnalyzed, matches, regWhile))
                {
                    lineAnalyzed = lineAnalyzed.substr((lineAnalyzed.find_first_not_of(' ')||lineAnalyzed.find_first_not_of('\t')), lineAnalyzed.length()-1);
                    if(lineAnalyzed.at(6)=='(')
                    {
                        string parenthesisContent = lineAnalyzed.substr(7, lineAnalyzed.length()-2-7);
                        if(parenthesisContent.substr(((parenthesisContent.find("<=")||parenthesisContent.find(">=")||parenthesisContent.find("!=")||parenthesisContent.find("=="))+2)) != "")
                        {
                            variableToSearch = parenthesisContent.substr(((parenthesisContent.find("<=")||parenthesisContent.find(">=")||parenthesisContent.find("!=")||parenthesisContent.find("=="))+2));
                        }
                        else
                        {
                            variableToSearch = parenthesisContent.substr(((parenthesisContent.find("<")||parenthesisContent.find(">"))+1));
                        }
                    }
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
                }
                info.push_back(make_tuple(numberLine,lineAnalyzed.substr(lineAnalyzed.find_first_not_of('\t'), lineAnalyzed.size()),RegOE(lineAnalyzed),lineTableFor));
                numberLine++;
            }
            cout<<"--------------------------------------------------------------------------------------------------------------------------------"<<endl;
            for(const auto & i : info) 
            {
                int numberLine = get<0>(i);
                string codeLine = get<1>(i);
                codeLine = codeLine.substr(correctBegginig, codeLine.length());
                int OEcount = get<2>(i);
                string tempPoly = get<3>(i);
                tempPoly= SendToPython(tempPoly);

                string tablePart1 = "Numero de linea siendo analizada: "+to_string(numberLine)+ "         |        " + "Codigo contenido en dicha linea: "+ codeLine;
                string tablePart2 = "Numero de Operaciones Elementales : "+ to_string(OEcount)+ "               " + " Polinomio: "+ tempPoly;
                cout<<tablePart1<<endl;
                cout<<tablePart2<<endl;
                cout<<"\n"<<endl;
            }
            string fP = SendToPython(finalPolunomial);
            cout<<fP<<endl;
            CotaAsin(fP);
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
            int correctBeginning; //Used for formatting purposes
            int correctEnding; //Used for formatting purposes
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

        /**
         * Depending on the strinf (not simplified polynomial) received by the method,
         * it will return a simplified polynomial for the complexity of the entire code and
         * also the Big O Notation.
         * 
         * @param value is a strig that represents the complexity polynomial for the entire
         *      code without any mathemathical manipulation yet.
         * 
         * @return "Polinomio del codigo analizado: T(n) = " + FinalPol indicates the Polynomial
         *      complexity of the code analyzed.
         * 
         * @note CotaAsin also prints the Big O Notation for the code analyzed as meentioned 
         *      before in this comment section.
         * 
         */
        void CotaAsin(string value)
        {
            int cont=0;
            smatch matches;
            char aux='0',logarit='0';
            string cot="";
            int band=0;
            regex regw("(w)");
            regex regPot(("([\\]*\\)")); 
            string Polipot = regex_replace(value,regPot,"^");
            cout<<Polipot<<endl;
            for(int i=0;i<Polipot.length();i++)
            {
                if(Polipot.at(i)=='n')
                {
                    if(Polipot.at(i+1)=='^')
                    {
                    if(Polipot.at(i+2)>=aux)
                    {
                        aux=Polipot.at(i+2);
                    }
                    i=i+2;
                    }
                    else if(Polipot.at(i+1)!='^')
                    {
                        if('1'>=aux)
                        {
                        aux='1';
                        }
                    }
                }
                else if(Polipot.at(i)=='w')
                {
                    band=1;
                    logarit=aux;
                }
            }
            if(band==1&&aux=='0')
            {
                cot="log n";
            }
            else if(aux>=logarit)
            {
                string s(1, aux);
                cot="n^"+ s;
            }
            else if(aux<=logarit)
            {
                string s(1, logarit);
                cot="n^"+ s+ " log n";
            }
            else if(aux=='0')
            {
                cot="1";
            }
            string FinalPol= regex_replace(Polipot,regw,"log n ");
            cout<<"Cota Asintotica: O("<<cot<<")"<<endl;
            //return "Polinomio del codigo analizado: T(n) = " + FinalPol;   
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
 * 
 */
int main(int argc, char** argv)
{
    Pruebas<int,string,int,string>P;
    P.InstallPython();
    P.SaveLinesIntoVector(argv[2]);
    P.ReadFileLineLine(argv[2]);
    return 0;
}