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

template <class T>
class ReadFile
{
    public:
        int arraySize = 0;
        vector <string> fileLines;

        void ReadLineByLine(T argv[])
        {
            regex reg ("[\=\+\-\/\*\<\>\!\%]");
            regex reg2 ("[=<>!]=");
            regex reg3 ("[\|\&]{2}");
            regex reg4 ("[+-]{2}");
            regex reg5 ("(print)"); 
            regex reg6 ("([\[])");
            regex reg7 ("(r)n");
            regex reg8 ("(cout)");

            regex regexWhile ("(while\(([^ ]+)\))");
            regex regFor ("(for\\((.*)\\))");

            string temp;
            ifstream file(argv);
            int operationsNumber = 0;
            while(getline(file, temp))
            {
                fileLines.push_back(temp);
                cout<<temp<<endl;
                
                operationsNumber = RegrexPlus(temp, reg);
                if(operationsNumber>0)
                {
                    operationsNumber += RegrexPlus(temp, reg6);
                }
                operationsNumber += RegrexPlus(temp, reg3);
                operationsNumber += RegrexPlus(temp, reg5);
                operationsNumber += RegrexPlus(temp, reg7);
                operationsNumber += RegrexPlus(temp, reg8);

                operationsNumber += RegrexMinus(temp, reg2);
                operationsNumber += RegrexMinus(temp, reg4);
            }
            cout<<operationsNumber<<endl;
            file.close();
        };

        int RegrexPlus(string str, regex reg)
        {
            smatch matches;
            int operationCounter = 0;
            replace(str.begin(), str.end(), (','), ' ');
            replace(str.begin(), str.end(), ('.'), ' ');
            while(regex_search(str, matches, reg))
            {
                str = matches.suffix().str();
                operationCounter++;
            }
            return operationCounter;
        };
        int RegrexMinus(string str, regex reg)
        {
            smatch matches;
            int operationCounter = 0;
            replace(str.begin(), str.end(), ',', ' ');
            replace(str.begin(), str.end(), ('.'), ' ');
            while(regex_search(str, matches, reg))
            {
                str = matches.suffix().str();
                operationCounter--;
            }
            return operationCounter;
        };
        int RegrexSpecialCases(string str, regex reg)
        {
            smatch matches;
            int operationCounter = 0;
            replace(str.begin(), str.end(), ',', ' ');
            while(regex_search(str, matches, reg))
            {
                str = matches.suffix().str();
                operationCounter--;
            }
            return operationCounter;
        }
};

int main(int argc, char** argv)
{
    ReadFile<char>R;
    R.ReadLineByLine(argv[2]);
    return 0;
}
