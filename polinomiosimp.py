from sympy import *
import sys
lista = sys.argv
def polinomio (poli):
    n = symbols('n')
    return(expand(poli))
value= str(polinomio (sys.argv[1]))
f=open('file.txt','w')
f.write(value)
f.close()

