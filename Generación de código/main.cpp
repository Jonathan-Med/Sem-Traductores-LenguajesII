#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

#include "lexico.h"
#include "sintactico.h"
#include "semantico.h"
#include "codigoasm.h"
#include "stdio.h"


int main()
{
        setlocale(LC_CTYPE,"Spanish");
        int opcion;
        int a,b;
        bool aceptado;
        string prototype;
        float x,y;
        while(true)
        {
            system("cls");
            aceptado=false;
            declaraciones.clear();
            cout<<"\t       Generacion de Codigo";
            cout<<"\n\nSeleccione una operacion: "<<endl<<endl;
            cout<<"\n1-. Suma.";
            cout<<"\n2-. Resta.";
            cout<<"\n3-. Multiplicacion.";
            cout<<"\n4-. Division.";
            cout<<"\n5-. Potencia.";
            cout<<"\n6-. Raíz Cuadrada.";
            cout<<"\n7-. Seno.";
            cout<<"\n8-. Coseno.";
            cout<<"\n9-. Tangente.";
            cout<<"\n0-. Salir.";
            cout<<"\n\nSeleccione una opcion: "; fflush(stdin); 
			cin>>opcion;
            if(opcion==1){
                cout<<"\nSuma.";
                prototype=buscaFuncion(opcion);
                aceptado=analizarArchivo("prototipo.txt",prototype);
                if(aceptado==true){
                    aceptado=false;
                    aceptado=analizarArchivo("Funciones.txt",prototype);
                    if(aceptado==true){
                        cout<<"\nSuma.";
                        cout<<endl<<endl<<"Ingresa el primer número: "; cin>>a;
                        cout<<"Ingresa el segundo número: "; cin>>b;
                        cout<<"\nResultado = "<<suma(a,b)<<endl;
                    }
                    else {
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                    }
                }
                else{
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                }
            }
            else if(opcion==2){
                cout<<"\nResta.";
                prototype=buscaFuncion(opcion);
                aceptado=analizarArchivo("Prototipo.txt",prototype);
                if(aceptado==true){
                    aceptado=false;
                    aceptado=analizarArchivo("Funciones.txt",prototype);
                    if(aceptado==true){
                        cout<<"\nResta.";
                        cout<<endl<<endl<<"Ingresa el primer número: "; cin>>a;
                        cout<<"Ingresa el segundo número: "; cin>>b;
                        cout<<"\nResultado = "<<resta(a,b)<<endl;
                    }
                    else {
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                    }
                }
                else{
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                }
            }
            else if(opcion==3){
                cout<<"\nMultiplicación."<<endl;
                prototype=buscaFuncion(opcion);
                aceptado=analizarArchivo("Prototipo.txt",prototype);
                if(aceptado==true){
                    aceptado=false;
                    aceptado=analizarArchivo("Funciones.txt",prototype);
                    if(aceptado==true){
                        cout<<"\nMultiplicación."<<endl;
                        cout<<endl<<endl<<"Ingresa el primer número: "; cin>>x;
                        cout<<"Ingresa el segundo número: "; cin>>y;
                        cout<<"\nResultado = "<<multiplicacion(x,y)<<endl;
                    }
                    else {
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                    }
                }
                else{
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                }
            }
            else if(opcion==4){
                cout<<"\nDivisión."<<endl;
                prototype=buscaFuncion(opcion);
                aceptado=analizarArchivo("prototipo.txt",prototype);
                if(aceptado==true){
                    aceptado=false;
                    aceptado=analizarArchivo("Funciones.txt",prototype);
                    if(aceptado==true){
                        cout<<"\nDivisión."<<endl;
                        cout<<endl<<endl<<"Ingresa el dividendo: "; cin>>x;
                        cout<<"Ingresa el divisor: "; cin>>y;
                        if(y==0){
                            cout<<"\nERROR: Division por cero";
                        }
                        else{
                            cout<<"\nResultado = "<<division(x,y)<<endl;
                        }
                    }
                    else {
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                    }
                }
                else{
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                }
            }
            else if(opcion==5){
                cout<<"\nPotencia."<<endl;
                prototype=buscaFuncion(opcion);
                aceptado=analizarArchivo("Prototipo.txt",prototype);
                if(aceptado==true){
                    aceptado=false;
                    aceptado=analizarArchivo("Funciones.txt",prototype);
                    if(aceptado==true){
                        cout<<"\nPotencia."<<endl;
                        cout<<endl<<endl<<"Ingresa un primer número: "; cin>>a;
                        cout<<"Ingresa la potencia: "; cin>>b;
                        if(b>=0){
                            cout<<"\nResultado = "<<potencia(a,b)<<endl;
                        }
                        else{
                            b=b*-1;
                            cout<<"\nResultado = "<<division(1,potencia(a,b))<<endl;
                        }
                    }
                    else {
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                    }
                }
                else{
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                }
            }
            else if(opcion==6){
                cout<<"\nRaíz Cuadrada."<<endl;
                prototype=buscaFuncion(opcion);
                aceptado=analizarArchivo("Prototipo.txt",prototype);
                if(aceptado==true){
                    aceptado=false;
                    aceptado=analizarArchivo("Funciones.txt",prototype);
                    if(aceptado==true){
                        cout<<"\nRaíz Cuadrada."<<endl;
                        cout<<endl<<endl<<"Ingresa un número: "; cin>>x;
                        if(x<0){
                            cout<<"\nERROR: Las raíces negativas no forman parte de los reales.";
                        }
                        else{
                            cout<<"\nResultado = "<<raiz(x)<<endl;
                        }
                    }
                    else {
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                    }
                }
                else{
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                }
            }
            else if(opcion==7){
                cout<<"\nSeno."<<endl;
                prototype=buscaFuncion(opcion);
                aceptado=analizarArchivo("Prototipo.txt",prototype);
                if(aceptado==true){
                    aceptado=false;
                    aceptado=analizarArchivo("Funciones.txt",prototype);
                    if(aceptado==true){
                        cout<<"\nSeno."<<endl;
                        cout<<endl<<endl<<"Ingresa un número: "; cin>>x;
                        if (x == 90 ){
                        	cout<<"\nResultado = 1"<<endl;
						}
						else if (x == 270){
							cout<<"\nResultado = -1"<<endl;
						}
						else if (x == 180 || x == 360){
							cout<<"\nResultado = 0"<<endl;
						}
						else{
							cout<<"\nResultado = "<<seno(x)<<endl;
						}
                        
                    }
                    else {
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                    }
                }
                else{
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                }
            }
            else if(opcion==8){
                cout<<"\nCoseno."<<endl;
                prototype=buscaFuncion(opcion);
                aceptado=analizarArchivo("Prototipo.txt",prototype);
                if(aceptado==true){
                    aceptado=false;
                    aceptado=analizarArchivo("Funciones.txt",prototype);
                    if(aceptado==true){
                        cout<<"\nCoseno."<<endl;
                        cout<<endl<<endl<<"Ingresa un número: "; cin>>x;
                        if (x == 90 || x==270){
                        	cout<<"\nResultado = 0"<<endl;
						}
						else if (x == 180){
							cout<<"\nResultado = -1"<<endl;
						}
						else if (x == 360){
							cout<<"\nResultado = 1"<<endl;
						}
						else{
							cout<<"\nResultado = "<<coseno(x)<<endl;
						}
                        
                    }
                    else {
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                    }
                }
                else{
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                }
            }
            else if(opcion==9){
                cout<<"\nTangente."<<endl;
                prototype=buscaFuncion(opcion);
                aceptado=analizarArchivo("Prototipo.txt",prototype);
                if(aceptado==true){
                    aceptado=false;
                    aceptado=analizarArchivo("Funciones.txt",prototype);
                    if(aceptado==true){
                        cout<<"\nTangente."<<endl;
                        cout<<endl<<endl<<"Ingresa un número: "; cin>>x;
                        if (x == 90 || x==270){
                        	cout<<"\nResultado = indefinido"<<endl;
						}
						else if (x == 180 || x == 360){
							cout<<"\nResultado = 0"<<endl;
						}
						else{
							cout<<"\nResultado = "<<seno(x)/coseno(x)<<endl;
						}
                        
                    }
                    else {
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                    }
                }
                else{
                    cout<<"\nERROR: No se encontró la función del lenguaje.";
                }
            }
            else if(opcion==0){
             break;
            }
         getch();
        }
	return 0;
}

