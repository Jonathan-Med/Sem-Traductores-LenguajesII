#ifndef SEMANTICO_H_INCLUDED
#define SEMANTICO_H_INCLUDED
#include "lexico.h"
#include "conio.h"
#include "semantico.h"
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>


struct variable
{
    string nombre;
    string tipo_dato;
    bool used = false;
};

string buscaFuncion(int operation){
    switch(operation)
    {
        case 1:
            return "suma";
            break;
        case 2:
            return "resta";
            break;
        case 3:
            return "mul";
            break;
        case 4:
            return "div";
            break;
        case 5:
            return "pot";
            break;
        case 6:
            return "raiz";
            break;
        case 7:
            return "seno";
            break;
        case 8:
            return "coseno";
            break;
        case 9:
            return "tangente";
            break;
        case 10:
            return "senoh";
            break;
        case 11:
            return "coseh";
            break;
        case 12:
            return "tangh";
            break;
    }
}

vector<variable> declaraciones;

bool existe_variable(string identificador){
    for(int i=0;i<declaraciones.size();i++){
        if(declaraciones[i].nombre==identificador){
            return true;
        }
    }
    return false;
}

bool mismo_tipo(string x1,string x2){
    string tipo1,tipo2;
    for(int i=0;i<declaraciones.size();i++){
        if(declaraciones[i].nombre==x1){
            tipo1=declaraciones[i].tipo_dato;
        }
        if(declaraciones[i].nombre==x2){
            tipo2=declaraciones[i].tipo_dato;
        }
    }
    if(tipo1==tipo2){
        return true;
    }
    else{
        return false;
    }
}

bool coincide_tipo(string identificador,string tipo){
    for(int i=0;i<declaraciones.size();i++){
        if(declaraciones[i].nombre==identificador){
            if(declaraciones[i].tipo_dato==tipo){
                return true;
            }
        }
    }
    return false;
}

void cambiar_estado(string identificador){
    for(int i=0;i<declaraciones.size();i++){
        if(declaraciones[i].nombre==identificador){
            declaraciones[i].used = true;
        }
    }
}

void mostrar_no_usadas(){
    for(int i=0;i<declaraciones.size();i++){
        if(declaraciones[i].used==false){
            cout<<endl<<"\t<WARNING: LA VARIABLE "<<declaraciones[i].nombre<<" HA SIDO DECLARADA PERO NO USADA>"<<endl;
        }
    }
}


#endif // SEMANTICO_H_INCLUDED

