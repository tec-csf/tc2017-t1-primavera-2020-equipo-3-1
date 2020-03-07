#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
void checkTimes(string val1, string val2 , string val3)
{
    string vect[3]={val1,val2,val3};
    string aux="";
    for(int i=0;i<3;i++)
    {
       for(int j=0;i+j<vect[i].length();j++)
       {
           if((vect[i].at(j)=='+'&& vect[i].at(j+1)=='=')||(vect[i].at(j)=='-'&& vect[i].at(j+1)=='='))
           {
              aux=vect[i].substr(j+2,vect[i].length()-j);
              aux="1/"+aux;
              cout<<aux<<endl;
              j=j+1;
           }
           else if((vect[i].at(j)=='/'&& vect[i].at(j+1)=='=')||(vect[i].at(j)=='*'&& vect[i].at(j+1)=='='))
           {
               aux="log";
               cout<<aux<<endl;
               j=j+1;
           }
           else if((vect[i].at(j)=='<'&& vect[i].at(j+1)=='=')||(vect[i].at(j)=='>'&& vect[i].at(j+1)=='=')||(vect[i].at(j)=='+'&& vect[i].at(j+1)=='+')||(vect[i].at(j)=='-'&& vect[i].at(j+1)=='-'))
           {
                 aux=vect[i].substr(j+2,vect[i].length()-j);
                 cout<<aux<<endl;
                j=j+1;
           }
           else if(vect[i].at(j)=='='||vect[i].at(j)=='<'||vect[i].at(j)=='>')
           {
                aux=vect[i].substr(j+1,vect[i].length()-j);
                cout<<aux<<endl;
           }
       }
    }
}
int main()
{
    checkTimes("i=10","i/=10","i-=3");
   
    cout<<j<<endl;
    return 0;
}