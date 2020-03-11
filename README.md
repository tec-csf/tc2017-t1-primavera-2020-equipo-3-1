# Tarea 1. Complejidad Computacional

---

##### Integrantes:
1. Esteban Manrique de Lara Sirvent - A01027077 - Campus Santa Fe
2. Miguel Ángel Hernández Maldonado - A01022398 - Campus Santa Fe
3. Luis Emilio Alcántara Guzmán - A01027304 - Campus Santa Fe

---
## 1. Aspectos generales

Las orientaciones de la tarea se encuentran disponibles en la plataforma **Canvas**.

Este documento es una guía sobre qué información debe entregar como parte de la tarea, qué requerimientos técnicos debe cumplir y la estructura que debe seguir para organizar su entrega.


### 1.1 Requerimientos técnicos

A continuación se mencionan los requerimientos técnicos mínimos de la tarea, favor de tenerlos presente para que cumpla con todos.

* El código debe desarrollarse en C++, cumpliendo con el último estándar [C++17](https://isocpp.org/std/the-standard).
* Toda la programación debe realizarse utilizando Programación Genérica.
* Deben utilizarse las [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md).
* Todo el código debe estar correctamente documentado, siguiendo los lineamientos que aparecen en [Documenting C++ Code](https://developer.lsst.io/cpp/api-docs.html).
* Todo el código de la tarea debe alojarse en este repositorio de GitHub.
* Debe configurar su repositorio para que utilice el sistema de Integración Continua [Travis CI](https://travis-ci.org/).

### 1.2 Estructura del repositorio

El proyecto debe seguir la siguiente estructura de carpetas:
```
- / 			        # Raíz del repositorio
    - README.md			# Archivo con la información general de la actividad (este archivo)
    - sources  			# Códigos fuente con la solución
    - examples			# Archivos de ejemplo que pueden utilizarse para verificar que la solución funciona.
```

## 2. Solución
El programa necesita mostrar 4 valores específicos por cada línea y 2 valores finales que son “polinomio final” y “complejidad del polinomio”, los cuales son; “número de línea”, “código de la línea”, “número de operaciones elementales” y “polinomio por línea”. Los 4 valores específicos son guardados en una “tupla”.
Al principio el programa tiene que leer línea por línea el documento “.txt” y lo hace mediante el método de “ReadFileLineLine”, para después entrar a una serie de operaciones de “regex” (expresiones regulares) las cuales identifican los componentes de la línea, ya sean “for”, “while”, “if”, “if else”, etc, para sacar la cantidad de operaciones elementales y el “polinomio por línea” según corresponda. Para la parte de “número de línea”, se mete a un ciclo “for” con un incremento de +1 cada que lee una línea de código; el Código de Línea se imprime el arreglo de caracteres de la línea que se está leyendo.
Para resolver la parte de polemonios se utilizó un “puente” a pyhton con la librería de “sympy” la cual nos ayuda a resolver el polinomio y a reducirlo para que nos dé el “polinomio por línea”, “el polinomio final” ya reducido y finalmente la “Cota asintótica” que nos ayuda a identificar cual es la complejidad del polinomio.


### 2.1 Pasos a seguir para utilizar la aplicación

1.	Clonar el repositorio de GitHub
   
    a.	Pegar la liga en el navegador
   
        i.	https://github.com/tec-csf/tc2017-t1-primavera-2020-equipo-3-1.git
   
    b.	Dar Click en el botón verde “Clone or Download”
        
        i.	Seleccionar “Open in Desktop”
        ii.	Se descagara un archivo .ZIP
        iii.	“tc2017-t1-primavera-2020-equipo-3-1-master.zip”
   
    c.	Descomprimir el archivo .zip
        
        i.	Se creara la carpeta “tc2017-t1-primavera-2020-equipo-3-1-master”
        
2.	Abrir el compilador Visual Studio Code en su Servidor

    a.	Abrir la carpeta clonada “tc2017-t1-primavera-2020-equipo-3-1-master"
    
    b.	Abrir el archivo “ZonaPruebas.cpp”
    
    c.	Abrir la terminal del Visual Studio Code
        
        i.	“Ctrl+ñ”
    
    d.	Identificar el archivo de la carpeta “Examples” que se quiere leer 
        
        i.	“Prueba.txt ” o “Prueba2.txt”
    
    e.	Compilar el archivo “ZonaPruebas.cpp”
        
        i.	“bash”
        ii.	“g++ ZonaPruebas.cpp –o z”
    
    f.	Compilar con el archivo .txt de su preferencia (paso 2.d)
        
        i.	“./z –i Prueba.txt” o “./z –i Prueba2.txt”
    
    g.	Analizar resultados


## 3. Referencias


Jan Goyvaerts. (2003). C++ Regular Expressions with std::regex. 2020, de Regular-Expressions.info Sitio web: https://www.regular-expressions.info/stdregex.html

geeksforgeeks. (2016). Tuples in C++. 2020, de GeeksforGeeks.org Sitio web: https://www.geeksforgeeks.org/tuples-in-c/

wordpress. (2014). Run a C/C++ program on terminal using gcc compiler. 2020, de Wordpress.com Sitio web: https://rupinderjeetkaur.wordpress.com/2014/06/20/run-a-cc-program-on-terminal-using-gcc-compiler/

http://www.yamllint.com/


