# Proyecto de Seminario de Solución de Problemas de Traductores de Lenguajes II
### Alumno: Medina Herrera Jonathan
### Carrera: Ingenieria en Computación
### Universidad de Guadalajara
----------------
## Compilador
Compilar es el proceso de transformar un programa informático escrito en un lenguaje en un conjunto de instrucciones en otro formato o lenguaje.  
Para poder realizar un compilador es necesario realizar varias fases, cada uno trabajando y realizando una tarea en epecifico, para la realización de este proyecto, tenemos que hacer un analizador léxico, un analizador sintactico, un analizador semántico y la generación de código. 
#### Analizador Léxico:  
Un analizador léxico es la primera fase de un compilador, el analizador léxico es el encargado de revisar cada componente del código introducido y transformarlo en un token y ver la validez del mismo, verificando si existe dentro del lenguaje, como si es una variable o una palabra reservada, asi como operadores logicos o un simple espacio, basicamente un analizador léxico revisa que cada palabra se encuentre registrada o tenga una estructura coherente, todo esto con el proposito de obtener dichos tokens mencionados anteriormente que van a servir como entrada para la siguiente fase del compilador.  
Esta fase del código se encuentra contenida en el archivo lexico.h que en pocas palabras es un automata capaz de reconocer simbolos, palbras reservadas y variables, por parte del código tiene una estructura sencilla de explicar: contiene una clase que define cada tipo de simbolo, además de una clase llamada léxico que tienen diferentes funciones, cada uno con funciones diferentes, por ejemplos hay una función para leer el caracter, otra para ver el estado siguiente, otra para el estado de aceptación, una para verificar si se trata de un espacio, letra o dígito, así como para leer la entrada como cadena.
En las siguientes capturas se podra ver una prueba de qué es lo que ocurre cuando se agrega un simbolo que no se encuentra en el lenguaje y otro cuando todo está en orden:

-------------
#### Analizador Sintactico:  

