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
El analizador sintactico esla segunda fase del compilador, recibe como entrada los tokens de salida que mandó el analizador léxico, en estas parte se manejan dichos tokens realiza un analisis de la gramatica y de ese analisis se genera un árbol sintactico. Aquí se que comprueba, procesa y reenvía las instrucciones del código fuente. Después de que un analizador léxico crea tokens estos son procesados por el analizador sintáctico para construir la estructura de datos.
Como parte del código este se contiene en la parte de sintactico.h y esta desarrollado con un automata capaz de crear un árbol sintactico capaz de procesar y organizar los tokens obtenidos del analizador léxico, además de que es capaz de reconocer bloques, sentencias de lectura y escritura; asignaciones, variables, funciones, llamadas de funciones, estructuras condicionales y de errores.  
Para empezar este programa utiliza un arreglo, que ayuda a guardar la información de las palabras aceptadas que proporciona el analizador léxico. además de usar dos autómatas los cuales representan los números reales y los identificadores válidos, en la parte principal del codigo se declaran las estructuras de los estados del autómata, también la organización de signos y palabras reservadas. También se encuentran funciones enteras que serán las declaraciones de las estructuras condicionales.  
Además de tener las funciones que analizarán y realizarán el llenado de los autómatas, que tienen estructuras que contienen vectores, y cadenas que son leídas.
Como se puede observar en las capturas el programa nos da aviso cuando ha habido algún error de sintaxis y cuando no:

-------------
