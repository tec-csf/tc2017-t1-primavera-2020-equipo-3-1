from sympy import *
g=open('file.txt','r')
simpli=g.readline()
g.close()
def polinomio (poli):
    n = symbols('n')
    return(expand(poli))
value=str(polinomio(simpli))
f=open('file.txt','w')
f.write(value)
f.close()
