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
![error_lexico](https://user-images.githubusercontent.com/111925532/205796293-9cc7f0ab-415c-423c-a175-dd3dab8a7f75.png)


![lexico_funcionando](https://user-images.githubusercontent.com/111925532/205796392-5027156a-7cb8-4f5b-8a95-491932e4a8ad.png)

-------------
#### Analizador Sintactico:  
El analizador sintactico esla segunda fase del compilador, recibe como entrada los tokens de salida que mandó el analizador léxico, en estas parte se manejan dichos tokens realiza un analisis de la gramatica y de ese analisis se genera un árbol sintactico. Aquí se que comprueba, procesa y reenvía las instrucciones del código fuente. Después de que un analizador léxico crea tokens estos son procesados por el analizador sintáctico para construir la estructura de datos.
Como parte del código este se contiene en la parte de sintactico.h y esta desarrollado con un automata capaz de crear un árbol sintactico capaz de procesar y organizar los tokens obtenidos del analizador léxico, además de que es capaz de reconocer bloques, sentencias de lectura y escritura; asignaciones, variables, funciones, llamadas de funciones, estructuras condicionales y de errores.  
Para empezar este programa utiliza un arreglo, que ayuda a guardar la información de las palabras aceptadas que proporciona el analizador léxico. además de usar dos autómatas los cuales representan los números reales y los identificadores válidos, en la parte principal del codigo se declaran las estructuras de los estados del autómata, también la organización de signos y palabras reservadas. También se encuentran funciones enteras que serán las declaraciones de las estructuras condicionales.  
Además de tener las funciones que analizarán y realizarán el llenado de los autómatas, que tienen estructuras que contienen vectores, y cadenas que son leídas.
Como se puede observar en las capturas el programa nos da aviso cuando ha habido algún error de sintaxis y cuando no:
![error_sintactico](https://user-images.githubusercontent.com/111925532/205796558-8b9876f6-24e4-4b08-9b62-7d2c5ac0b1da.png)

![error_sintactico2](https://user-images.githubusercontent.com/111925532/205796588-33495336-6b95-487f-9464-4a2a3bee3c40.png)

![error_sintactico3](https://user-images.githubusercontent.com/111925532/205796637-8ee3b3b1-3e45-4074-87bc-0fe1bd881840.png)

![sintactico_bien](https://user-images.githubusercontent.com/111925532/205796516-a4e2d2e6-ffc4-4334-9045-e6d2a1a833ff.png)
-------------
#### Analizador Semántico:  
El analizador Semántico es la tercera fase del desarrollo de un compilador, en esta parte se analiza el contexto en la que las instrucciones se encuentran, para que despues se haga su implementación en lenguaje de bajo nivel, en esta fase se analiza una estructura de instrucciones en un árbol semántico y luego comparan los
diferentes componentes individuales en búsqueda de errores en la programación. En esta fase se utiliza la salida obtenida por el analizador sintactico, aquí se implementa un conjunto de reglas formales que especifican la estructura de los programas pertenecientes a dicho lenguaje. aquí se confirma la validez de la intrucción dada y el orden de dichas intrucciones.  
Por parte del código, este lo podemos encontrar en la parte de semantico.h esta parte del código debe de ser capaz de Mostrará errores si existen re-declaraciones de variables en el código, solo puede declararse un nombre a la vez, Mostrará alertas el compilador si alguna variable no ha sido usada, Si una variable está queriendo tomar un valor que no corresponde a su tipo de dato, este mostrará un error, Las variables no pueden tener el mismo nombre que determinadas funciones declaradas, No se pueden usar variables que no hayan sido declaradas previamente, se debe tener un uso correcto a las condicionales usadas en el If y While, entre otros. Un autómata deberá ser capaz de realizar eso. Por otra parte, Se usaron dos autómatas los cuales representan los números reales y los identificadores
válidos. El análisis semántico se realiza a la vez que el análisis sintáctico. En la primera parte se declaran estructuras enumeradas de los estados del autómata,
así como de la organización de signos y palabras reservadas. También se encuentran funciones enteras que serán las declaraciones de las estructuras condicionales.
además de tener funciones que analizarán, realizarán el llenado de los autómatas y estructuras contienen vectores, y cadenas que son leídas.  
Como se puede observar en las siguientes capturas, cómo es que se muestran los errores cuando el código está escrito de manera incorrecta y otra de cómo se ve un código escrito correctamente:
![error_semantico](https://user-images.githubusercontent.com/111925532/205796692-d6c67f09-c99f-40b1-88ba-445cb724de17.png)

![semantico-error](https://user-images.githubusercontent.com/111925532/205796720-f5d148dd-3163-4385-b787-ac037a209835.png)

![error_semantico2](https://user-images.githubusercontent.com/111925532/205796751-f22a2d1d-a30e-4d21-9651-55d1d20f9196.png)

![semantico_funcionando](https://user-images.githubusercontent.com/111925532/205796784-d3b6b745-a2b1-43b2-96c4-53ad9a8fa582.png)

-----------
#### Generación de Código:
La generación de código consiste en relacionar todo lo que se ha hecho hasta ahora en el compilador que cuenta ya con tres fases de desarrollo. Se trata así pues de la última fase del compilador que se han desarrollado, el cual tiene como función vincular las funciones del lenguaje desarrollado con las de ensamblador. El lenguaje ensamblador que se utiliza para traducir programas al código de máquina. Cada microprocesador o microcontrolador tiene su propio lenguaje ensamblador con su particular
conjunto de instrucciones y sus varios modos de direccionamiento que dependen de la arquitectura del hardware, cada nuevo procesador de INTEL que sale al mercado, el
fabricante agrega algunas instrucciones a su conjunto de instrucciones, pero siempre conservan las instrucciones y registros de los modelos anteriores por razones de
compatibilidad. Existe una relación muy estrecha entre la programación en C y la programación en ensamblador.
creado para evitarle a los programadores del sistema operativo UNIX seguir escribiéndolo en ensamblador. Las ventajas de programar en C lo mismo que antes se programaba en ensamblador son obvias: portabilidad y legibilidad a través de un código bien estructurado. Sin embargo, las partes del sistema en las que es necesario trabajar con características específicas del hardware no pueden ser escritas en C.  
* El generador de código deberá reconocer lo siguiente:  
  * Operaciones aritméticas (suma y resta)
  * Operaciones aritméticas (multiplicación y división)
  * Operaciones aritméticas (potencia y raíz)
  * Funciones trigonométricas
  * Uso de la función volatile
  * Uso del analizador léxico, sintáctico y semántico, para poder utilizar el lenguaje desarrollado.  

Este parte del código esta contenida en la parte de asmcpp.h que utiliza el lenguaje ensamblador en c++, y como ya se mencionó antes, este realiza operaciones matematicas, es una calculadora, y en el codigo está contenidas las operaciones que serán llamadas cuando el codigo sea leido y revisado, ya que esté archivo está conectado con las demás fases del compilador y el funcionamiento de las funciones se ve afectado por un archivo txt, donde si es modificado, no se podrán realizar las operaciones que aparezcan en la ventana, por lo que el txt funciona como el nuevos lenguaje que se desarrolló.  
Acontinuación se mostraran capturas con el funcionamiento de la calculadora:  
![resta](https://user-images.githubusercontent.com/111925532/205796859-fe1c444f-3b94-4817-a285-9e462e73f604.png)

![multiplicacion](https://user-images.githubusercontent.com/111925532/205796875-78aa2840-acf6-4821-b094-813261bd3cdb.png)

![raiz](https://user-images.githubusercontent.com/111925532/205796902-b43d2d25-8377-4dff-a421-473084b60534.png)

![potencia](https://user-images.githubusercontent.com/111925532/205796933-379be469-e6da-4864-8d62-2136e58a835c.png)

![coseno](https://user-images.githubusercontent.com/111925532/205796952-681ea5d9-868b-40cc-bb79-7c1470cbcf3e.png)

![tangente](https://user-images.githubusercontent.com/111925532/205796973-d2655c14-adcb-4665-a7b9-1ce4daad7df9.png)
