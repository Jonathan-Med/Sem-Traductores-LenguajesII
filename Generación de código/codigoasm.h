#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vector>

#define _USE_MATH_DEFINES
#define M_PI   3.14159265358979323846
#define M_E    2.71828182818281828182

using namespace std;

#include "lexico.h"
#include "sintactico.h"
#include "semantico.h"
#include "stdio.h"

float suma( int $a, int $b){
int $result;
__asm__ __volatile__(
		"movl %1, %%eax;"
		"movl %2, %%ebx;"
		"addl %%ebx, %%eax;"
	    "movl %%eax, %0;" : "=g" ( $result ) : "g" ( $a ), "g" ( $b )
);
return $result ;
}

int resta( int $a, int $b){
int $result;
__asm__ __volatile__(
		"movl %1, %%eax;"
		"movl %2, %%ebx;"
		"subl %%ebx, %%eax;"
	    "movl %%eax, %0;" : "=g" ( $result ) : "g" ( $a ), "g" ( $b )
);
return $result ;
}

float multiplicacion( float x, float y ) {
    float resultado;
    __asm__ __volatile__ (
        "fld %1;"
        "fld %2;"
        "fmulp;"
        "fst %0;" : "=m" (resultado) : "g" (x), "g" (y)
    ) ;
    return resultado;
}

float division( float x, float y ) {
    float resultado;
    __asm__ __volatile__ (
        "fld %2;"
        "fld %1;"
        "fdivp;"
        "fst %0;" : "=m" (resultado) : "g" (x), "g" (y)
    ) ;
    return resultado;
}


int potencia( int $a, int $b ) {
    int $result;
    __asm__ __volatile__(		

        "movl %1, %%eax;"	
        "movl %1, %%ebx;"	
        "movl %2, %%ecx;"	
        "cmpl $1, %%ecx;"	
        "je UNO;"			
        "jl CERO;"			
        "decl %%ecx;"		
        "POTENCIA: imull %%ebx;"	
            "loopl POTENCIA;"		
        "jmp FIN;"				
        "UNO: jmp FIN;"			
        "CERO: movl $1,%%eax;"	
            "jmp FIN;"			
        "FIN: movl %%eax, %0;" : "=g" ( $result ) : "g" ( $a ), "g" ( $b )
    );
    return $result;
}

float raiz( float x) {
    float resultado;
    __asm__ __volatile__ (
        "fld %1;"
        "fsqrt;"
        "fst %0;" : "=m" (resultado) : "g" (x)
    ) ;
    return resultado;
}

long double seno(long double grados)
{
    grados=(grados*M_PI)/180;
    register long double resultado;

    __asm__ __volatile__(
        "fsin" : "=t" (resultado) : "0" (grados)
    );
    return resultado;
}

long double coseno(long double grados)
{
    grados=(grados*M_PI)/180;
    register long double resultado;

    __asm__ __volatile__(
        "fcos" : "=t" (resultado) : "0" (grados)
    );
    return resultado;
}

float potencia_euler( float x, int y ) {
    float resultado = 1;
    __asm__ __volatile__ (
        "movl %2,%%eax;"
        "cmp $0,%%eax;"
        "je SALIR;"
        "cmp $1,%%eax;"
        "je POT_UNO;"
        "decl %%eax;"
        "fld %1;"
        "fld %1;"
        "REPITE:"
        "fmulp;"
        "decl %%eax;"
        "cmp $0, %%eax;"
        "je FINAL;"
        "fst %0;"
        "fld %0;"
        "fld %1;"
        "jmp REPITE;"
        "FINAL:"
        "fst %0;"
        "jmp SALIR;"
        "POT_UNO:"
        "movl %1,%%eax;"
        "movl %%eax,%0;"
        "SALIR:"

        : "=m" (resultado) : "g" (x), "g" (y)
    ) ;
    return resultado;
}

float seno_hiperbolico( float x, float y ) {
    float resultado,div=2;
    __asm__ __volatile__ (
        "fld %3;"
        "fld %2;"
        "fld %1;"
        "fsubp;"
        "fdivp;"
        "fst %0;" : "=m" (resultado) : "g" (x), "g" (y), "g" (div)
    ) ;
    return resultado;
}

float coseno_hiperbolico( float x, float y ) {
    float resultado,div=2;
    __asm__ __volatile__ (
        "fld %3;"
        "fld %2;"
        "fld %1;"
        "faddp;"
        "fdivp;"
        "fst %0;" : "=m" (resultado) : "g" (x), "g" (y), "g" (div)
    ) ;
    return resultado;
}

