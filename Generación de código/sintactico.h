#ifndef SINTACTICO_H_INCLUDED
#define SINTACTICO_H_INCLUDED
#include "lexico.h"
#include "semantico.h"
#include "conio.h"
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>

#define ES_IF 6
#define ENT_IF 5
#define ES_ELSE 4
#define ENT_ELSE 3
#define ES_ELSE_IF 8
#define ENT_ELSE_IF 7
#define ES_WHILE 6
#define ENT_WHILE 5

using namespace std;

//IF-ELSE IF-ELSE
enum {IF_3=0,PARENTESIS_A_3,CONDICION_3,PARENTESIS_B_3,LLAVE_3} e_if;
enum {LLAVE1_4=0,ELSE_4,LLAVE2_4} e_else;
enum {LLAVE2_5=0,ELSE_5,IF_5,PARENTESIS_A_5,CONDICION_5,PARENTESIS_B_5,LLAVE1_5} e_else_if;
enum {WHILE_8=0,PARENTESIS_A_8,CONDICION_8,PARENTESIS_B_8,LLAVE_8} e_while;
enum {Q0=0,Q1,Q2,Q3,Q4,Q5,Q6,Q7,Q8,Q9,Q10,Q11} estados;

int declaracionIf[ES_IF][ENT_IF];
int declaracionElse[ES_ELSE][ENT_ELSE];
int declaracionElseIf[ES_ELSE_IF][ENT_ELSE_IF];
int declaracionWhile[ES_WHILE][ENT_WHILE];

int posFinalIf = 0;

void llenarAutomatas();
void llenarDeclaracionIf();
void llenarDeclaracionElse();
void llenarDeclaracionElseIf();
void llenarDeclaracionWhile();
bool analiza_funcion(string cadena);
bool analizarDeclaracionIf(string cadena);
bool analizarDeclaracionElseIf(string cadena);
bool analizarDeclaracionElse(string cadena);
bool analizarDeclaracionWhile(string cadena);
void analizar_cadena_sintactico(string cadena);

void llenarAutomatas() {
    llenarDeclaracionIf();
    llenarDeclaracionElse();
    llenarDeclaracionElseIf();
    llenarDeclaracionWhile();
}

struct Comparacion {
    string comparadorIzquierda;
    string comparadorDerecha;
    string operador;
    int num;
};

struct Condicion {
    string cadena;
    vector<Comparacion> comparaciones;
    string operador;
    int num;
    bool esVariableOFuncion = false;
};

struct Linea {
    int num;
    string contenido;
    int longitud;
    int tipo;
    int posFinal;
    bool esIf = false;
    bool ifActivado = false;
    Condicion condicion;
};

vector<Linea> lineas;
string codigo;
string archivo;
int numLinea;
string search_funtion;
bool find_funtion = false;
bool coincide_funcion = false;
bool error_semantico = false;
bool error_sintactico = false;
bool bloqueo = false;

bool validarPilaLlaves(string codigo) {
    int count = 0;
    for(int i = 0; i < (int)codigo.length(); i++) {
        if(codigo[i] == '{' ) {
            count++;
        } else if(codigo[i] == '}') {
            if(count == 0) {
                return false;
            } else {
                count--;
            }
        }
    }
    return count == 0;
}

string leerArchivo(string nombreArchivo) {
    string cadena;
    ifstream leer;
    char temp;
    cadena = "";
    leer.open(nombreArchivo);
    if(leer.good()) {
        while(!leer.eof()) {
            leer.read((char *)&temp, 1);
            if(leer.eof()) break;
            cadena += temp;
        }
        leer.close();
    }
    return cadena;
}

void leerLineas(string codigo) {
    int tamanoCodigo = codigo.length();
    string linea;
    Linea l;
    for(int i=0; i<tamanoCodigo; i++) {
        if((int)codigo[i] != 10) {
            linea+=codigo[i];
        } else {
            l.contenido = linea;
            l.longitud = linea.length();
            l.num = lineas.size()+1;
            lineas.push_back(l);
            linea = "";
        }
    }
    l.contenido = codigo[tamanoCodigo-1];
    l.longitud = l.contenido.length();
    l.num = lineas.size()+1;
    lineas.push_back(l);
}

void analizarLinea(int pos) {
    Linea linea = lineas[pos];
    string contenido = linea.contenido;
    bool funct=false;
    //cout<<contenido; getch();
    if(bloqueo==true){
        funct=analiza_funcion(contenido);
        if(funct){
            bloqueo=false;
        }
    }
    if(find_funtion==false && error_sintactico==false && error_semantico==false && bloqueo==false){
        analizar_cadena_sintactico(contenido);
    }
}

bool analiza_funcion(string cadena){
    int i;
    char reserved[1000];
    char copia_cadena[1000];
    bool find=false;
    string first_word;
    strcpy(copia_cadena,cadena.c_str());
    for(i=0; i<cadena.size(); i++) {
        if(cadena[i]==' ') {
            find=true;
            break;
        }
        reserved[i]=copia_cadena[i];
    }
    if(find==false) {
        return false;
    }
    reserved[i]='\0';
    first_word=reserved;
    string tipo;
    if(analizar_cadena_lexico(first_word)) {
        tipo=retorna_tipo(first_word);
        if(tipo=="Tipo de Dato") { // declaraciones de variables o funciones
            if(first_word!="void") {
                return false;
            } else {
                for(i=0; i<cadena.size(); i++) {
                    if(cadena[i]==';') {
                        return false;
                    }
                }
                return true;
            }
        }
        else{
            return false;
        }
    }
}

void analizarLineas(int lineaInicial, int lineaFinal) {
    for(numLinea=lineaInicial; numLinea<lineaFinal; numLinea++) {
        analizarLinea(numLinea);
    }
}

bool analizarArchivo(string nombreAchivo, string prototype) {
    find_funtion=false;
    error_semantico=false;
    error_sintactico=false;
    bloqueo=false;
    coincide_funcion=false;
    search_funtion = prototype;
    ifstream test;
    test.open(nombreAchivo);
    lineas.clear();
    if(test.good()) {
        codigo = leerArchivo(nombreAchivo);
        if(validarPilaLlaves(codigo)) {
            archivo = nombreAchivo;
            leerLineas(codigo);
            numLinea = 0;
            analizarLineas(numLinea,lineas.size());
        } else {
            cout << endl << "\tNo hay coincidencia de llaves {}" << endl;
            return false;
        }
        if(find_funtion==false){
            return false;
        }
        else{
            if(error_sintactico==false && error_semantico==false){
                return true;
            }
            else{
                return false;
            }
        }
    } else {
        cout << "Algo salió mal, no se ha podido abrir el archivo." << endl;
        return false;
    }
}

void sintactico_function(string cadena, int i) {
    i++;
    int indice=cadena.size()-1;
    if(cadena[indice]==';'){
        char copia_cadena[1000];
        strcpy(copia_cadena,cadena.c_str());
        char reserve[1000];
        int x=0;
        while(cadena[i]!=';') {
            reserve[x]=copia_cadena[i];
            x++;
            i++;
        }
        reserve[x]='\0';
        if(es_identificador(reserve)) {
            if(!existe_variable(reserve)){
                cout<<"\t<ERROR:NO SE HA DECLARADO LA VARIABLE "<<reserve<<".>"<<endl;
                error_semantico=true;
            }
            cout<<"\t<FUNCION MATEMATICA>"<<endl;
        } else {
            cout<<"ERROR DE SINTAXIS"<<endl;
            error_sintactico=true;
        }
    }
    else{
        cout<<"ERROR DE SINTAXIS"<<endl;
        error_sintactico=true;
    }
    return;
}


void sintactico_cout(string cadena,int i) {
    int indice;
    i++;
    if(cadena[i]=='<') {
        i++;
        if(cadena[i]=='<') {
            i++;
            indice=cadena.size()-1;
            if(cadena[indice]==';') {
                if(cadena[i]=='"') {
                    if(cadena.size()<10) {
                        cout<<"ERROR DE SINTAXIS"<<endl;
                        error_sintactico=true;
                        return;
                    }
                    indice--;
                    if(cadena[indice]=='"') {
                        cout<<"\t<MOSTRAR DATOS PANTALLA>"<<endl;
                    } else {
                        cout<<"ERROR DE SINTAXIS"<<endl;
                        error_sintactico=true;
                    }
                }
                else {
                    char copia_cadena[1000];
                    strcpy(copia_cadena,cadena.c_str());
                    char reserve[1000];
                    int x=0;
                    while(cadena[i]!=';') {
                        reserve[x]=copia_cadena[i];
                        x++;
                        i++;
                    }
                    reserve[x]='\0';
                    if(es_identificador(reserve)) {
                        cout<<"\t<MOSTRAR DATOS EN PANTALLA>"<<endl;
                    } else {
                        cout<<"ERROR DE SINTAXIS"<<endl;
                        error_sintactico=true;
                    }
                }
            }
            else {
                cout<<"ERROR DE SINTAXIS"<<endl;
                error_sintactico=true;
            }
        } else {
            cout<<"ERROR DE SINTAXIS"<<endl;
            error_sintactico=true;
        }
    } else {
        cout<<"ERROR DE SINTAXIS"<<endl;
        error_sintactico=true;
    }
    return;
}

void sintactico_cin(string cadena, int i) {
    if(cadena.size()<8) {
        cout<<"ERROR DE SINTAXIS"<<endl;
        error_sintactico=true;
        return;
    }

    i++;
    if(cadena[i]=='>') {
        i++;
        if(cadena[i]=='>') {
            int x=cadena.size()-1;
            if(cadena[x]==';') {
                i++;
                char copia_cadena[1000];
                strcpy(copia_cadena,cadena.c_str());
                char reserve[1000];
                x=0;
                while(cadena[i]!=';') {
                    reserve[x]=copia_cadena[i];
                    x++;
                    i++;
                }
                reserve[x]='\0';
                if(es_identificador(reserve)) {
                    cout<<"<DATOS DE ENTRADA>"<<endl;
                } else {
                    cout<<"ERROR DE SINTAXIS"<<endl;
                    error_sintactico=true;
                }
            } else {
                cout<<"ERROR DE SINTAXIS"<<endl;
                error_sintactico=true;
            }
        } else {
            cout<<"ERROR DE SINTAXIS"<<endl;
            error_sintactico=true;
        }
    } else {
        cout<<"ERROR DE SINTAXIS"<<endl;
        error_sintactico=true;
    }
    return;
}

bool parametros(string cadena) {
    int i;
    char reserved[1000];
    char copia_cadena[1000];
    bool find=false;
    string first_word;
    strcpy(copia_cadena,cadena.c_str());
    for(i=0; i<cadena.size(); i++) {
        if(cadena[i]==' ') {
            find=true;
            break;
        }
        reserved[i]=copia_cadena[i];
    }
    if(find==false) {
        return false;
    }
    reserved[i]='\0';
    first_word=reserved;
    string tipo;
    if(analizar_cadena_lexico(first_word)) {
        tipo=retorna_tipo(first_word);
        if(tipo=="Tipo de Dato") {
            if(first_word=="void") {
                return false;
            } else {
                reserved[0]='\0';
                int b=0;
                i++;
                for(; i<cadena.size(); i++,b++) {
                    reserved[b]=copia_cadena[i];
                }
                reserved[b]='\0';
                tipo=reserved;
                if(es_identificador(tipo)) {
                    return true;
                } else {
                    return false;
                }
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void sintactico_prototipo(string cadena) {
    char copia_cadena[1000];
    char identificador[100];
    int i=0;
    if(cadena[i]=='v'){
        i=5;
        int indice=0;
        while(cadena[i]!='(') {
            identificador[indice]=cadena[i];
            i++;
            indice++;
        }
        identificador[indice]='\0';
        if(es_identificador(identificador)){
            i=0;
        }
        else{
             cout<<"ERROR DE SINTAXIS"<<endl;
             error_sintactico=true;
        }
    }
    while(cadena[i]!='(') {
        i++;
    }
    i++;
    int i2=0;
    while(cadena[i]!=')') {
        copia_cadena[i2]=cadena[i];
        i++;
        i2++;
    }
    copia_cadena[i2]='\0';
    if(strlen(copia_cadena)>0) {
        int tam=strlen(copia_cadena)-1;
        if(copia_cadena[tam]==',') {
            cout<<"ERROR DE SINTAXIS"<<endl;
            error_sintactico=true;
            return;
        }
    } else {
        if(identificador==search_funtion){
            find_funtion=true;
            cout << "\t" << cadena;
            cout<<"\n\t<DECLARACION DE PROTOTIPO DE FUNCION>\n";
        }
        return;
    }
    int x=0;
    char sub_cadena[100];
    for(i=0; i<strlen(copia_cadena)+1; i++) {
        if(copia_cadena[i]!=',' && copia_cadena[i]!='\0') {
            sub_cadena[x]=copia_cadena[i];
            x++;
        } else {
            sub_cadena[x]='\0';
            if(parametros(sub_cadena)) {
                x=0;
                sub_cadena[x]='\0';
            } else {
                cout<<"ERROR DE SINTAXIS"<<endl;
                error_sintactico=true;
                return;
            }
        }
    }
    if(identificador==search_funtion){
        find_funtion=true;
        cout  << "\t" << cadena;
        cout<<"\n\t<DECLARACION DE PROTOTIPO DE FUNCION>\n";
    }
    return;
}

void sintactico_funciones(string cadena) {
    char copia_cadena[1000];
    char identificador[100];
    int i=0;
    if(cadena[i]=='v'){
        i=5;
        int indice=0;
        while(cadena[i]!='(') {
            identificador[indice]=cadena[i];
            i++;
            indice++;
        }
        identificador[indice]='\0';
        if(es_identificador(identificador)){
            i=0;
        }
        else{
             cout<<"ERROR DE SINTAXIS"<<endl;
             error_sintactico=true;
        }
    }
     if(identificador==search_funtion){
        coincide_funcion=true;
        cout << "\t" << cadena;
        cout<<"\n\t<FUNCION>\n";
    }
    else{
        bloqueo=true;
    }
    return;
}

void sintactico_asignaciones(string first_word,string cadena, int i) {
    i++;
    if(cadena[i]=='=') {
        i++;
        if(cadena[i]==' ') {
            i++;
            int a=cadena.size()-1;
            if(cadena[a]==';') {
                a=i;
                char copia_cadena[100];
                char reserve[100];
                strcpy(reserve,cadena.c_str());
                int j;
                for(j=0; a<cadena.size(); a++,j++) {
                    copia_cadena[j]=reserve[a];
                }
                copia_cadena[j-1]='\0';
                string compara=copia_cadena;
                if(copia_cadena[0]=='"'){
                    if(strlen(copia_cadena)<2){
                        cout<<"ERROR DE SINTAXIS"<<endl;
                        error_sintactico=true;
                    }
                    else{
                        j=strlen(copia_cadena)-1;
                        if(copia_cadena[j]!='"'){
                            cout<<"ERROR DE SINTAXIS"<<endl;
                            error_sintactico=true;
                        }
                        else{
                            if(coincide_tipo(first_word,"string")){
                                cambiar_estado(first_word);
                                cout<<"\t<STRING ASIGNADO>"<<endl;
                            }
                            else{
                                cout<<"\t<ERROR DE CONVERSION DE VARIABLE>"<<endl;
                                error_semantico=true;
                            }
                        }
                    }
                }
                else if(copia_cadena[0]==char(39)){
                    if(strlen(copia_cadena)<2){
                        cout<<"ERROR DE SINTAXIS"<<endl;
                        error_sintactico=true;
                    }
                    else{
                        j=strlen(copia_cadena)-1;
                        if(copia_cadena[j]!=char(39)){
                            cout<<"ERROR DE SINTAXIS"<<endl;
                            error_sintactico=true;
                        }
                        else{
                            if(coincide_tipo(first_word,"char")){
                                cambiar_estado(first_word);
                                cout<<"\t<CHAR ASIGNADO>"<<endl;
                            }
                            else{
                                cout<<"\t<ERROR DE CONVERSION DE VARIABLE>"<<endl;
                                error_semantico=true;
                            }
                        }
                    }
                }
                else if(compara=="true" || compara=="false"){
                    if(coincide_tipo(first_word,"bool")){
                        cambiar_estado(first_word);
                        cout<<"\t<BOOLEANO ASIGNADO>"<<endl;
                    }
                    else{
                        cout<<"\t<ERROR DE CONVERSION DE VARIABLE>"<<endl;
                        error_semantico=true;
                    }
                }
                else{
                    int cuenta_operadores=0;
                    for(int x=0; x<strlen(copia_cadena); x++) {
                        if(copia_cadena[x]=='+' || copia_cadena[x]=='-' || copia_cadena[x]=='*' || copia_cadena[x]=='=' || copia_cadena[x]=='/' || copia_cadena[x]=='%' || copia_cadena[x]=='^') {
                            cuenta_operadores++;
                        }
                    }
                    if(cuenta_operadores==0) {
                        string identificador = copia_cadena;
                        if(es_identificador(identificador)) {
                            if(!existe_variable(identificador)){
                                cout<<"\t<ERROR: NO SE HA DECLARADO LA VARIABLE "<<identificador<<".>"<<endl;
                                error_semantico=true;
                            }
                            else{
                                if(mismo_tipo(first_word,identificador)){
                                    cambiar_estado(first_word);
                                    cambiar_estado(identificador);
                                    cout<<"\t<ASIGNACIONES>"<<endl;
                                }
                                else{
                                    cout<<"\t<ERROR: LAS VARIABLES NO SON COMPATIBLES>"<<endl;
                                    error_semantico=true;
                                }
                            }
                        } else if(es_numero(identificador)) {
                            if(coincide_tipo(first_word,"int")){
                                cambiar_estado(first_word);
                                cout<<"\t<ASIGNACIONES>"<<endl;
                            }
                            else{
                                if(coincide_tipo(first_word,"float")){
                                    cambiar_estado(first_word);
                                    cout<<"\t<ASIGNACIONES>"<<endl;
                                }
                                else{
                                    cout<<"\t<ERROR EN CONVERSION DE VARIABLE>"<<endl;
                                    error_semantico=true;
                                }
                            }
                        } else if(es_funcion(identificador)) {
                            cambiar_estado(first_word);
                            cout<<"\t<ASIGNACIONES>"<<endl;
                        } else {
                            cout<<"ERROR DE SINTAXIS"<<endl;
                            error_sintactico=true;
                        }
                    } else {
                        cambiar_estado(first_word);
                        int x=0;
                        char sub_cadena[100];
                        for(i=0; i<strlen(copia_cadena)+1; i++) {
                            if( (copia_cadena[i]!='+' && copia_cadena[i]!='-' && copia_cadena[i]!='*' && copia_cadena[i]!='=' && copia_cadena[i]!='/' && copia_cadena[i]!='%' && copia_cadena[i]!='^') && (copia_cadena[i]!='\0') ) {
                                sub_cadena[x]=copia_cadena[i];
                                x++;
                            } else {
                                sub_cadena[x]='\0';
                                if(es_identificador(sub_cadena)) {
                                    if(!existe_variable(sub_cadena)){
                                        cout<<"\t<ERROR: NO SE HA DECLARADO LA VARIABLE "<<sub_cadena<<".>"<<endl;
                                        error_semantico=true;
                                        return;
                                    }
                                    else{
                                        if(mismo_tipo(first_word,sub_cadena)){
                                            cambiar_estado(sub_cadena);
                                            x=0;
                                            sub_cadena[x]='\0';
                                        }
                                        else{
                                            cout<<"\t<ERROR: LAS VARIABLES NO SON COMPATIBLES>"<<endl;
                                            error_semantico=true;
                                            return;
                                        }
                                    }
                                }
                                else if(es_numero(sub_cadena)) {
                                    cambiar_estado(sub_cadena);
                                    x=0;
                                    sub_cadena[x]='\0';
                                } else if(es_funcion(sub_cadena)) {
                                    cambiar_estado(sub_cadena);
                                    x=0;
                                    sub_cadena[x]='\0';
                                } else {
                                    cout<<"ERROR DE SINTAXIS"<<endl;
                                    error_sintactico=true;
                                    return;
                                }
                            }
                        }
                        cout<<"\t<ASIGNACIONES>"<<endl;
                    }
                }
            } else {
                cout<<"ERROR DE SINTAXIS"<<endl;
                error_sintactico=true;
            }
        } else {
            cout<<"ERROR DE SINTAXIS"<<endl;
            error_sintactico=true;
        }
    } else {
        cout<<"ERROR DE SINTAXIS"<<endl;
        error_sintactico=true;
    }
}

void sintactico_declaraciones(string cadena,string first_word,int i) { // Terminado
    bool find;
    char copia_cadena[1000];
    int b;
    bool find_key=false;
    for(b=0; b<cadena.size(); b++) { //buscar llave que abre '{'
        if(cadena[b]=='{') {
            find_key=true;
            break;
        }
    }
    if(find_key) { // si esta
        find_key=false;
        b--;
        for(; b<cadena.size(); b++) { //buscar llave que cierra
            if(cadena[b]=='}') {
                find_key=true;
            } else {
                find_key=false;
            }
        }
        if(find_key) { //si esta
            sintactico_funciones(cadena);
        } else {
            cout<< "\tError de Sintaxis"<<endl;
            error_sintactico=true;
            return;
        }
    } else {
        find=false;
        int space=i,parentesis=i;
        char identificador[1000];
        // validar que no haya solo ';' despues de espacio
        if(cadena[i+1]==';') {
            cout<<"\tError de Sintaxis"<<endl;
            error_sintactico=true;
            return;
        }
        // validar que termine en ; si hay caracteres despues de espacio
        for(; i<cadena.size(); i++) {
            if(cadena[i]==';' && cadena[i+1]=='\0') {
                find=true;
            }
        }
        if(find==false) {
            cout<<"\tError de Sintaxis"<<endl;
            error_sintactico=true;
            return;
        }
        //validar que la palabra que hay entre el espacio y el ';' sea un identificador valido
        int x;
        space++;
        for(x=0; space<cadena.size(); space++,x++) {
            if(cadena[space]==';') {
                break;
            }
            identificador[x]=cadena[space];
        }
        identificador[x]='\0';
        string ide=identificador;
        if(es_identificador(ide)) { // (tipo de dato) (identificador) ;
            variable x;
            x.nombre=ide;
            x.tipo_dato=first_word;
            if(!existe_variable(ide)){
                declaraciones.push_back(x);
                cout <<"\t<Variable declarada>"<<endl;
            }
            else{
                cout <<"\t<ERROR: YA SE HA DECLARADO LA VARIABLE ANTES>"<<endl;
                error_semantico=true;
            }
        } else { // puede tener parentesis
            bool flag=false;
            int a;
            for(a=0; a<ide.size(); a++) { //buscar parentesis que abre '('
                if(ide[a]=='(') {
                    flag=true;
                    break;
                } else if(ide[a]==')') {
                    flag=false;
                    break;
                }
            }
            if(flag) { // si esta
                a++;
                flag=false;
                int uno=0;
                for(; a<ide.size(); a++) { //buscar parentesis que cierra
                    if(ide[a]==')') {
                        flag=true;
                        uno++;
                    } else if(ide[a]=='(') {
                        flag=false;
                        break;
                    }
                }
                if(uno>1) {
                    flag=false;
                }
                if(flag) { //si esta
                    strcpy(copia_cadena,ide.c_str());
                    char ide_2[1000];
                    for(a=0; a<ide.size(); a++) {
                        if(copia_cadena[a]=='(') {
                            break;
                        }
                        ide_2[a]=copia_cadena[a];
                    }
                    ide_2[a]='\0';
                    ide=ide_2;
                    if(es_identificador(ide)) {
                        if(!existe_variable(ide)){
                            variable x;
                            x.nombre=ide;
                            x.tipo_dato="function";
                            x.used=true;
                            declaraciones.push_back(x);
                            sintactico_prototipo(cadena);
                        }
                        else{
                            cout<<"\t<ERROR: YA SE HA DECLARADO EL IDENTIFICADOR ANTES>";
                            error_semantico=true;
                        }
                        return;
                    } else {
                        cout<< "\tError de Sintaxis"<<endl;
                        error_sintactico=true;
                        return;
                    }
                } else {
                    cout<< "\tError de Sintaxis"<<endl;
                    error_sintactico=true;
                    return;
                }
            } else {
                cout<< "\tError de Sintaxis"<<endl;
                error_sintactico=true;
                return;
            }
        }
    }
}

bool haySoloLlaves(string linea) {
    int tamano = linea.length();
    for(int i=0; i<tamano; i++) {
        if((linea[i] != '}') && (linea[i] != ' ')) {
            if((int)linea[i] != 10) {
                if((int)linea[i] != 9) {
                    return false;
                }
            }
        }
    }
    return true;
}

void printCondition(Linea linea, bool tieneCondicion) {
    string condicion = linea.condicion.cadena;
    condicion[condicion.length()-1] = '\0';
    cout << endl << "\t\tPOSICION DE INICIO: " << linea.num-1;
    cout << endl << "\t\tPOSICIÓN FINAL: " << linea.posFinal-1;
    if(tieneCondicion) {
        cout << endl << "\t\tCONDICIÓN: " << condicion;
    }
    cout << endl << "\t>";
}

void analizar_cadena_sintactico(string cadena) {
    Linea linea;
    if(coincide_funcion==true){
        cout << endl << "\t" << cadena;
    }
    if(cadena.length() == 0) {
        cout << "\t<LINEA VACIA>";
        return;
    }
    if(haySoloLlaves(cadena)) {
        cout << "\t<FINAL DE BLOQUE>";
        if(coincide_funcion==true)
            find_funtion=true;
        return;
    }
    if(analizarDeclaracionIf(cadena)) {
        lineas[numLinea].posFinal = posFinalIf;
        lineas[numLinea].esIf = true;
        linea = lineas[numLinea];
        posFinalIf = 0;
        cout << "\t<DECLARACION DE IF";
        printCondition(linea,true);
        return;
    }
    if(analizarDeclaracionElse(cadena)) {
        lineas[numLinea].posFinal = posFinalIf;
        lineas[numLinea].esIf = false;
        linea = lineas[numLinea];
        posFinalIf = 0;
        cout << "\t<DECLARACION DE ELSE";
        printCondition(linea,false);
        return;
    }
    if(analizarDeclaracionElseIf(cadena)) {
        lineas[numLinea].posFinal = posFinalIf;
        lineas[numLinea].esIf = true;
        linea = lineas[numLinea];
        posFinalIf = 0;
        cout << "\t<DECLARACION DE ELSE IF";
        printCondition(linea,true);
        return;
    }
    if(analizarDeclaracionWhile(cadena)) {
        lineas[numLinea].posFinal = posFinalIf;
        lineas[numLinea].esIf = false;
        linea = lineas[numLinea];
        posFinalIf = 0;
        cout << "\t<DECLARACIÓN DE WHILE";
        printCondition(linea,true);
        return;
    }
    if(es_funcion(cadena)) {
        cout <<"\t<LLAMADA DE FUNCION>";
        return;
    }
    int i;
    char reserved[1000];
    char copia_cadena[1000];
    bool find=false;
    string first_word;
    strcpy(copia_cadena,cadena.c_str());
    for(i=0; i<cadena.size(); i++) {
        if(cadena[i]==' ') {
            find=true;
            break;
        }
        reserved[i]=copia_cadena[i];
    }
    if(find==false) {
        cout<< "\tError de Sintaxis"<<endl;
        error_sintactico=true;
        return;
    }
    reserved[i]='\0';
    first_word=reserved;
    string tipo;
    if(analizar_cadena_lexico(first_word)) {
        tipo=retorna_tipo(first_word);
        if(tipo=="Tipo de Dato") { // declaraciones de variables o funciones
            if(first_word!="void") {
                sintactico_declaraciones(cadena,first_word,i);
            } else {
                for(i=0; i<cadena.size(); i++) {
                    if(cadena[i]==';') {
                        sintactico_prototipo(cadena);
                        return;
                    }
                }
                sintactico_funciones(cadena);
            }
        }

        else if(tipo=="Palabra reserved") { // ciclos o condicionales o structs

            if(first_word=="cout") {
                sintactico_cout(cadena,i);
            } else if(first_word=="cin") {
                sintactico_cin(cadena,i);
            } else {
                cout<<"ERROR DE SINTAXIS"<<endl;
                error_sintactico=true;
            }
        } else if(tipo=="identificador") { // asignaciones o llamadas a funciones
            if(!existe_variable(first_word)){
                cout<<"\t<ERROR: NO SE HA DECLARADO LA VARIABLE "<<first_word<<".>";
                error_semantico=true;
            }
            else{
                sintactico_asignaciones(first_word,cadena,i);
            }
        } else if(tipo=="Ensamblador") {
            sintactico_function(cadena,i);
        }
        else {                    // numeros
            cout<< "\tError de Sintaxis"<<endl;
            error_sintactico=true;
        }
    } else {
        cout<< "\tError de Sintaxis"<<endl;
        error_sintactico=true;
    }
    return;
}

void llenarDeclaracionWhile() {
    //Forma : while(condicion) {
    declaracionWhile[Q0][WHILE_8]=Q1;
    declaracionWhile[Q0][PARENTESIS_A_8]=Q6;
    declaracionWhile[Q0][CONDICION_8]=Q6;
    declaracionWhile[Q0][PARENTESIS_B_8]=Q6;
    declaracionWhile[Q0][LLAVE_8]=Q6;

    declaracionWhile[Q1][WHILE_8]=Q6;
    declaracionWhile[Q1][PARENTESIS_A_8]=Q2;
    declaracionWhile[Q1][CONDICION_8]=Q6;
    declaracionWhile[Q1][PARENTESIS_B_8]=Q6;
    declaracionWhile[Q1][LLAVE_8]=Q6;

    declaracionWhile[Q2][WHILE_8]=Q6;
    declaracionWhile[Q2][PARENTESIS_A_8]=Q6;
    declaracionWhile[Q2][CONDICION_8]=Q3;
    declaracionWhile[Q2][PARENTESIS_B_8]=Q6;
    declaracionWhile[Q2][LLAVE_8]=Q6;

    declaracionWhile[Q3][WHILE_8]=Q6;
    declaracionWhile[Q3][PARENTESIS_A_8]=Q6;
    declaracionWhile[Q3][CONDICION_8]=Q6;
    declaracionWhile[Q3][PARENTESIS_B_8]=Q4;
    declaracionWhile[Q3][LLAVE_8]=Q6;

    declaracionWhile[Q4][WHILE_8]=Q6;
    declaracionWhile[Q4][PARENTESIS_A_8]=Q6;
    declaracionWhile[Q4][CONDICION_8]=Q6;
    declaracionWhile[Q4][PARENTESIS_B_8]=Q6;
    declaracionWhile[Q4][LLAVE_8]=Q5;

    declaracionWhile[Q5][WHILE_8]=Q6;
    declaracionWhile[Q5][PARENTESIS_A_8]=Q6;
    declaracionWhile[Q5][CONDICION_8]=Q6;
    declaracionWhile[Q5][PARENTESIS_B_8]=Q6;
    declaracionWhile[Q5][LLAVE_8]=Q6;
}

void llenarDeclaracionIf() {
    //Forma : if(condicion) {
    declaracionIf[Q0][IF_3]=Q1;
    declaracionIf[Q0][PARENTESIS_A_3]=Q6;
    declaracionIf[Q0][CONDICION_3]=Q6;
    declaracionIf[Q0][PARENTESIS_B_3]=Q6;
    declaracionIf[Q0][LLAVE_3]=Q6;

    declaracionIf[Q1][IF_3]=Q6;
    declaracionIf[Q1][PARENTESIS_A_3]=Q2;
    declaracionIf[Q1][CONDICION_3]=Q6;
    declaracionIf[Q1][PARENTESIS_B_3]=Q6;
    declaracionIf[Q1][LLAVE_3]=Q6;

    declaracionIf[Q2][IF_3]=Q6;
    declaracionIf[Q2][PARENTESIS_A_3]=Q6;
    declaracionIf[Q2][CONDICION_3]=Q3;
    declaracionIf[Q2][PARENTESIS_B_3]=Q6;
    declaracionIf[Q2][LLAVE_3]=Q6;

    declaracionIf[Q3][IF_3]=Q6;
    declaracionIf[Q3][PARENTESIS_A_3]=Q6;
    declaracionIf[Q3][CONDICION_3]=Q6;
    declaracionIf[Q3][PARENTESIS_B_3]=Q4;
    declaracionIf[Q3][LLAVE_3]=Q6;

    declaracionIf[Q4][IF_3]=Q6;
    declaracionIf[Q4][PARENTESIS_A_3]=Q6;
    declaracionIf[Q4][CONDICION_3]=Q6;
    declaracionIf[Q4][PARENTESIS_B_3]=Q6;
    declaracionIf[Q4][LLAVE_3]=Q5;

    declaracionIf[Q5][IF_3]=Q6;
    declaracionIf[Q5][PARENTESIS_A_3]=Q6;
    declaracionIf[Q5][CONDICION_3]=Q6;
    declaracionIf[Q5][PARENTESIS_B_3]=Q6;
    declaracionIf[Q5][LLAVE_3]=Q6;
}

void llenarDeclaracionElse() {
    //Foma : } else {
    declaracionElse[Q0][LLAVE2_4]=Q1;
    declaracionElse[Q0][ELSE_4]=Q4;
    declaracionElse[Q0][LLAVE1_4]=Q4;

    declaracionElse[Q1][LLAVE2_4]=Q4;
    declaracionElse[Q1][ELSE_4]=Q2;
    declaracionElse[Q1][LLAVE1_4]=Q4;

    declaracionElse[Q2][LLAVE2_4]=Q4;
    declaracionElse[Q2][ELSE_4]=Q4;
    declaracionElse[Q2][LLAVE1_4]=Q3;

    declaracionElse[Q3][LLAVE2_4]=Q4;
    declaracionElse[Q3][ELSE_4]=Q4;
    declaracionElse[Q3][LLAVE1_4]=Q4;
}
void llenarDeclaracionElseIf() {
    //Forma : } else if(condicion) {
    declaracionElseIf[Q0][LLAVE2_5]=Q1;
    declaracionElseIf[Q0][ELSE_5]=Q8;
    declaracionElseIf[Q0][IF_5]=Q8;
    declaracionElseIf[Q0][PARENTESIS_A_5]=Q8;
    declaracionElseIf[Q0][CONDICION_5]=Q8;
    declaracionElseIf[Q0][PARENTESIS_B_5]=Q8;
    declaracionElseIf[Q0][LLAVE1_5]=Q8;

    declaracionElseIf[Q1][LLAVE2_5]=Q8;
    declaracionElseIf[Q1][ELSE_5]=Q2;
    declaracionElseIf[Q1][IF_5]=Q8;
    declaracionElseIf[Q1][PARENTESIS_A_5]=Q8;
    declaracionElseIf[Q1][CONDICION_5]=Q8;
    declaracionElseIf[Q1][PARENTESIS_B_5]=Q8;
    declaracionElseIf[Q1][LLAVE1_5]=Q8;

    declaracionElseIf[Q2][LLAVE2_5]=Q8;
    declaracionElseIf[Q2][ELSE_5]=Q8;
    declaracionElseIf[Q2][IF_5]=Q3;
    declaracionElseIf[Q2][PARENTESIS_A_5]=Q8;
    declaracionElseIf[Q2][CONDICION_5]=Q8;
    declaracionElseIf[Q2][PARENTESIS_B_5]=Q8;
    declaracionElseIf[Q2][LLAVE1_5]=Q8;

    declaracionElseIf[Q3][LLAVE2_5]=Q8;
    declaracionElseIf[Q3][ELSE_5]=Q8;
    declaracionElseIf[Q3][IF_5]=Q8;
    declaracionElseIf[Q3][PARENTESIS_A_5]=Q4;
    declaracionElseIf[Q3][CONDICION_5]=Q8;
    declaracionElseIf[Q3][PARENTESIS_B_5]=Q8;
    declaracionElseIf[Q3][LLAVE1_5]=Q8;

    declaracionElseIf[Q4][LLAVE2_5]=Q8;
    declaracionElseIf[Q4][ELSE_5]=Q8;
    declaracionElseIf[Q4][IF_5]=Q8;
    declaracionElseIf[Q4][PARENTESIS_A_5]=Q8;
    declaracionElseIf[Q4][CONDICION_5]=Q5;
    declaracionElseIf[Q4][PARENTESIS_B_5]=Q8;
    declaracionElseIf[Q4][LLAVE1_5]=Q8;

    declaracionElseIf[Q5][LLAVE2_5]=Q8;
    declaracionElseIf[Q5][ELSE_5]=Q8;
    declaracionElseIf[Q5][IF_5]=Q8;
    declaracionElseIf[Q5][PARENTESIS_A_5]=Q8;
    declaracionElseIf[Q5][CONDICION_5]=Q8;
    declaracionElseIf[Q5][PARENTESIS_B_5]=Q6;
    declaracionElseIf[Q5][LLAVE1_5]=Q8;

    declaracionElseIf[Q6][LLAVE2_5]=Q7;
    declaracionElseIf[Q6][ELSE_5]=Q7;
    declaracionElseIf[Q6][IF_5]=Q7;
    declaracionElseIf[Q6][PARENTESIS_A_5]=Q7;
    declaracionElseIf[Q6][CONDICION_5]=Q7;
    declaracionElseIf[Q6][PARENTESIS_B_5]=Q7;
    declaracionElseIf[Q6][LLAVE1_5]=Q7;

    declaracionElseIf[Q7][LLAVE2_5]=Q8;
    declaracionElseIf[Q7][ELSE_5]=Q8;
    declaracionElseIf[Q7][IF_5]=Q8;
    declaracionElseIf[Q7][PARENTESIS_A_5]=Q8;
    declaracionElseIf[Q7][CONDICION_5]=Q8;
    declaracionElseIf[Q7][PARENTESIS_B_5]=Q8;
    declaracionElseIf[Q7][LLAVE1_5]=Q8;
}

int estadoDeclaracionIf(int estadoActual, int simbolo) {
    return declaracionIf[estadoActual][simbolo];
}
int estadoDeclaracionElse(int estadoActual, int simbolo) {
    return declaracionElse[estadoActual][simbolo];
}
int estadoDeclaracionElseIf(int estadoActual, int simbolo) {
    return declaracionElseIf[estadoActual][simbolo];
}

int estadoDeclaracionWhile(int estadoActual, int simbolo) {
    return declaracionWhile[estadoActual][simbolo];
}

bool existeCadena(string linea, int pos, string cadena, int& indiceFinal) {
    int tamanoLinea = linea.length();
    stringstream cadenaEncontrada;
    for(int i=pos; i<tamanoLinea; i++) {
        if((linea[i] != ' ') && ((int)linea[i] != 10) && ((int)linea[i] != 9)) {
            cadenaEncontrada << linea[i];
            if(cadenaEncontrada.str() == cadena) {
                indiceFinal = i+1;
                return true;
            }
        }
    }
    indiceFinal = -1;
    return false;
}

string obtenerSubCadena(string cadena, int pos1, int pos2) {
    stringstream cadenaCorta;
    int caracteresALaDererecha = pos2 - pos1;
    switch(caracteresALaDererecha) {
    case 0:
        cadenaCorta << cadena[pos1];
        return cadenaCorta.str();
    case 1:
        cadenaCorta << cadena[pos1];
        return cadenaCorta.str();
    default:
        return cadena.substr(pos1,caracteresALaDererecha);
    }
}

int obtenerIndiceSubcadena(string linea, int indice, char caracter) {
    int tamanoLinea = linea.length();
    if(tamanoLinea) {
        for(int i=indice; i<tamanoLinea; i++) {
            if(linea[i] == caracter) {
                return i;
            }
        }
        return 0;
    } else {
        return -1;
    }
}

int encontrarLlaves(string linea, int contLlaves) {
    int tamanoLinea = linea.length();
    int cont = contLlaves;
    for(int i=0; i<tamanoLinea; i++) {
        if(linea[i] == '{') {
            cont++;
            if(cont == 0) {
                break;
            }
        } else if (linea[i] == '}') {
            cont--;
            if(cont == 0) {
                break;
            }
        }
    }
    return cont;
}

int obtenerIndiceBloqueInstrucciones(int linea, bool esIf, bool esElseIf) {
    int contLineas = lineas.size();
    int contLlaves = 0;
    if(esElseIf) {
        esIf = true;
        contLlaves = 1;
        linea++;
    }
    for(int i=linea; i<contLineas; i++) {
        contLlaves = encontrarLlaves(lineas[i].contenido,contLlaves);
        cout << endl << "\t\tSub: " << lineas[i].contenido <<  " Llaves: " << contLlaves << endl;
        if(contLlaves == 0) {
            if(esIf) {
                posFinalIf = i+1;
            }
            return 0;
        } else if(contLlaves < 1) {
            return -1;
        }
    }
    return 0;
}

string dameOperadoresLinea(string linea, char caracter_1, char caracter_2) {
    int tamanoLinea = linea.length();
    char simbolo;
    string cadena = "";
    for(int i=0; i<tamanoLinea; i++) {
        simbolo=linea[i];
        if((simbolo == caracter_1) || (simbolo == caracter_2)) {
            cadena+=simbolo;
        }
    }
    if(cadena.length() > 0) {
        return cadena;
    }
    return "";
}

bool estaBalanceadaLaPila(string cadena, char caracterApertura) {
    stack<char> pila;
    int tamanoLinea = cadena.length();
    char simbolo;
    bool balanceada = true;
    for(int i=0; i<tamanoLinea; i++) {
        simbolo = cadena[i];
        if(simbolo == caracterApertura) {
            pila.push(simbolo);
        } else {
            if(pila.empty()) {
                balanceada = false;
                break;
            } else {
                pila.pop();
            }
        }
    }
    if((balanceada) && (pila.empty())) {
        return true;
    }
    return false;
}

bool tieneIf(int posElse) {
    int cantLineas = lineas.size();
    for(int i=0; i<cantLineas; i++) {
        if(lineas[i].esIf) {
            if(!lineas[i].ifActivado) {
                if(lineas[i].posFinal == posElse) {
                    lineas[i].ifActivado = true;
                    return true;
                }
            }
        }
    }
    return false;
}

bool analizarDeclaracionIf(string linea) {
    int tamanoLinea = linea.length();
    int entrada, i, indice, estado;
    string subCadena, condicion;
    int lineaFinalBloque;

    i=indice=estado=0;
    if(existeCadena(linea,i,"if",indice)) {
        subCadena = obtenerSubCadena(linea,indice-2,indice);
        i = indice-2;
    } else {
        return false;
    }
    while(i < tamanoLinea) {
        /*cout << endl << "*" << subCadena << "*" << endl;
        system("pause");*/
        if(subCadena == "if") {
            entrada = IF_3;
            i+=2;
            if(!existeCadena(linea,i,"(",indice)) {
                return false;
            }
            subCadena = obtenerSubCadena(linea,indice-1,indice);
        } else if (subCadena == "(") {
            entrada = PARENTESIS_A_3;
            i+=subCadena.length()-1;
            indice = obtenerIndiceSubcadena(linea,i,'{');
            subCadena = obtenerSubCadena(linea,i,indice);
            if(!estaBalanceadaLaPila(dameOperadoresLinea(subCadena,'(',')'),'(')) {
                cout << endl << "\tERROR: NO HAY EQUIVALENCIA DE PARENTESIS";
                error_sintactico=true;
                return false;
            }
            condicion = subCadena.substr(1,subCadena.length()-3);
            estado = estadoDeclaracionIf(estado,entrada);
            entrada = CONDICION_3;
            i+=condicion.length()+1;
            subCadena = linea[i];
            i+=subCadena.length();
        } else if (subCadena == ")") {
            entrada = PARENTESIS_B_3;
            indice = obtenerIndiceSubcadena(linea,i,'{');
            subCadena = linea[indice];
            i+=subCadena.length();
        } else if (subCadena == "{") {
            entrada = LLAVE_3;
            i++;
        } else {
            break;
        }
        estado = estadoDeclaracionIf(estado,entrada);
    }
    if(estado == Q5) {
        string c2 = "(";
        condicion.push_back(')');
        c2 += condicion;
        if(!es_condicional_valido(c2)) {
            cout << endl << "\tERROR EN LA CONDICION IF";
            error_sintactico=true;
        }
        lineaFinalBloque = obtenerIndiceBloqueInstrucciones(numLinea,true,false);
        if(lineaFinalBloque == -1) {
            return false;
        }
        for(; numLinea<lineaFinalBloque; numLinea++) {
            analizarLinea(numLinea);
        }
        return true;
    } else {
        return false;
    }
}

bool analizarDeclaracionElse(string linea) {
    int tamanoLinea = linea.length();
    int entrada, i, indice, estado;
    string subCadena;
    int lineaFinalBloque;

    i=indice=estado=0;
    i=obtenerIndiceSubcadena(linea,i,'}');
    subCadena=linea[i];
    while(i < tamanoLinea) {
        //cout << "." << subCadena << "." << endl;
        if(subCadena == "}") {
            i+=2;
            entrada = LLAVE2_4;
            indice=obtenerIndiceSubcadena(linea,i,'{');
            indice--;
            subCadena = obtenerSubCadena(linea,i,indice);
        } else if (subCadena == "else") {
            entrada = ELSE_4;
            i+=subCadena.length()+1;
            indice = obtenerIndiceSubcadena(linea,i,'{');
            subCadena = obtenerSubCadena(linea,i,indice);
        } else if (subCadena == "{") {
            entrada = LLAVE1_4;
            i++;
        } else {
            break;
        }
        estado = estadoDeclaracionElse(estado,entrada);
    }
    if(estado == Q3) {
        if(!tieneIf(numLinea+1)) {
            cout << endl << endl << "\tERROR: FALTA IF" << endl;
            error_sintactico=true;
            return false;
        }
        lineaFinalBloque = obtenerIndiceBloqueInstrucciones(numLinea,false,true);
        if(lineaFinalBloque == -1) {
            return false;
        }
        for(; numLinea<lineaFinalBloque; numLinea++) {
            analizarLinea(numLinea);
        }
        return true;
    }
    return false;
}
bool analizarDeclaracionElseIf(string linea) {
    int tamanoLinea = linea.length();
    int entrada, i, indice, estado;
    string subCadena, condicion;
    int lineaFinalBloque;

    i=indice=estado=0;
    i=obtenerIndiceSubcadena(linea,i,'}');
    subCadena=linea[i];
    while(i < tamanoLinea) {
        //cout << endl << "*" << subCadena << "*" << endl;
        if(subCadena == "}") {
            entrada = LLAVE2_5;
            i+=2;
            if(!existeCadena(linea,i,"else",indice)) {
                return false;
            }
            subCadena = obtenerSubCadena(linea,indice-4,indice);
        } else if(subCadena == "else") {
            entrada = ELSE_5;
            i+=subCadena.length()+1;
            if(!existeCadena(linea,i,"if",indice)) {
                return false;
            }
            subCadena = obtenerSubCadena(linea,indice-2,indice);
        } else if(subCadena == "if") {
            entrada = IF_5;
            i+=subCadena.length();
            if(!existeCadena(linea,i,"(",indice)) {
                return false;
            }
            subCadena = linea[indice-1];
        } else if(subCadena == "(") {
            entrada = PARENTESIS_A_5;
            i+=subCadena.length()-1;
            indice = obtenerIndiceSubcadena(linea,i,'{');
            subCadena = obtenerSubCadena(linea,i,indice);
            if(!estaBalanceadaLaPila(dameOperadoresLinea(subCadena,'(',')'),'(')) {
                return false;
            }
            condicion = subCadena.substr(1,subCadena.length()-3);
            estado = estadoDeclaracionIf(estado,entrada);
            entrada = CONDICION_5;
            i+=condicion.length()+1;
            subCadena = linea[i];
            i+=subCadena.length();
        } else if (subCadena == ")") {
            entrada = PARENTESIS_B_5;
            indice = obtenerIndiceSubcadena(linea,i,'{');
            subCadena = linea[indice];
            i+=subCadena.length();
        } else if (subCadena == "{") {
            entrada = LLAVE1_5;
            i++;
        } else {
            break;
        }
        estado = estadoDeclaracionElseIf(estado,entrada);
    }
    if(estado == Q7) {
        if(!tieneIf(numLinea+1)) {
            cout << endl << endl << "\tERROR: FALTA IF" << endl;
            error_sintactico=true;
        }
        string c2 = "(";
        condicion.push_back(')');
        c2 += condicion;
        if(!es_condicional_valido(c2)) {
            cout << endl << "\tERROR EN ELSE IF";
            error_sintactico=true;
            return false;
        }
        lineaFinalBloque = obtenerIndiceBloqueInstrucciones(numLinea,false,true);
        if(lineaFinalBloque == -1) {
            return false;
        }
        for(; numLinea<lineaFinalBloque; numLinea++) {
            analizarLinea(numLinea);
        }
        return true;
    }
    return false;
}

int buscarPrimerCaracter(string linea, int posInicial, char caracter) {
    int tamanoLinea = linea.length();
    for(int i=posInicial; i<tamanoLinea; i++) {
        if(linea[i] == caracter) {
            return i;
        }
    }
    return tamanoLinea;
}

bool analizarDeclaracionWhile(string linea) {
    int tamanoLinea = linea.length();
    int entrada, i, j, indice_1, indice_2, estado, lineaFinalBloque;
    string subCadena, condicion;

    i=j=indice_1=indice_2=estado=0;
    indice_1 = buscarPrimerCaracter(linea,j,'w');
    i+=indice_1;
    indice_2 = buscarPrimerCaracter(linea,indice_1,'(');
    subCadena = obtenerSubCadena(linea,indice_1,indice_2);
    i += subCadena.length();
    while(i < tamanoLinea) {
        //cout << endl << "*" << subCadena << "*" << endl;
        if(subCadena == "while") {
            entrada = WHILE_8;
            j = i;
            indice_1 = buscarPrimerCaracter(linea,j,'(');
            subCadena = obtenerSubCadena(linea,indice_1,indice_1);
            i++;
        } else if(subCadena == "(") {
            entrada = PARENTESIS_A_8;
            j = i;
            indice_1 = buscarPrimerCaracter(linea,j,'{');
            indice_1-=2; //Para encontrar )
            subCadena = obtenerSubCadena(linea,j,indice_1);
            condicion = subCadena;
            estado = estadoDeclaracionWhile(estado,entrada);
            entrada = CONDICION_8;
            i = j+subCadena.length();
            subCadena = obtenerSubCadena(linea,indice_1,indice_1);
            i++;
        } else if(subCadena == ")") {
            entrada = PARENTESIS_B_8;
            j = i;
            indice_1 = buscarPrimerCaracter(linea,j,'{');
            subCadena = obtenerSubCadena(linea,indice_1,indice_1);
            i = j+subCadena.length();
        } else if(subCadena == "{") {
            entrada = LLAVE_8;
            i++;
        } else {
            break;
        }
        estado = estadoDeclaracionWhile(estado,entrada);
    }
    if(estado == Q5) {
        string c2 = "(";
        condicion.push_back(')');
        c2 += condicion;
        if(!es_condicional_valido(c2)) {
            cout << endl << "\tError en Condición del WHILE";
            error_sintactico=true;
        }
        lineaFinalBloque = obtenerIndiceBloqueInstrucciones(numLinea,true,false);
        if(lineaFinalBloque == -1) {
            return false;
        }
        for(; numLinea<lineaFinalBloque; numLinea++) {
            analizarLinea(numLinea);
        }
        return true;
    }
    return false;
}

#endif // SINTACTICO_H_INCLUDED

