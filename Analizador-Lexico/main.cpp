#include <cstdlib>
#include <iostream>
#include <string>

#include "lexico.h"

using namespace std;

int main(int argc, char *argv[]){


    Lexico lexico;
    cout<<"Entrada a evaluar: ";
    cout<<"Hola Mund0 234 2.43 {} +*/ else while if "<< endl;
    system("pause");
    lexico.entrada("Hola Mund0 234 2.43 {} +*/ else while if ");

    cout << "Resultado del Analisis Lexico" << endl << endl;
    cout << "Simbolo\t\t      Tipo" << endl;

    while ( lexico.simbolo.compare("$") != 0 ){
          lexico.sigSimbolo();

          cout <<  lexico.simbolo << "\t\t    " << lexico.tipoAcad(lexico.tipo) << endl;
    }

    system("pause");

    return 0;
}
