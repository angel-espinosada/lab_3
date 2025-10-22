#include <iostream>
#include <fstream>
#include <string>
using namespace std;

float sumar(float saldo, float consignacion);
float restar(float saldo, float retiro);
string leerArchivo(const string& nombre);
void guardarArchivo(const string& nombre, const string& contenido);
string codificar(const string& texto);
string decodificar(const string& texto);
int main() {

    {
        int opcion=1;
        while(opcion!=0)
        {
            cout<<"Menu de incio"<<endl;
            cout<<"1- Codificacion de archivos"<<endl;
            cout<<"2- Decodificacion de archivos"<<endl;
            cout<<"3-Cajero automatico"<<endl;
            cout<<"0- para salir"<<endl;
            cin>>opcion;

            switch (opcion) {

            case 1:{

            }

            case 2:{

                cout<<"Desencriptar"<<endl;

//hola
            }

            break;

            case 3:{
                int identificacion;
                float plata, resul;
                float consignar;
                float retirar;
                string clave;
                string archivoEntrada;

                cout<<"::Cajero::"<<endl;
                plata=100000;
                string pista="ala";

                int identificacion1=12345;

                cout<<"Ingrese su cedula"<<endl;
                cin>>identificacion;
                cout<<"Ingrese la clave"<<endl;
                cin>>clave;
                //if(pista!=clave&&identificacion!=identificacion1)

                if(identificacion!=identificacion1){
                    cout<<"Error en la identificacion"<<endl;
                }
                if(pista!=clave){
                    cout<<"Error en la clave"<<endl;
                }


                else{

                    int opcion=1;
                    while(opcion!=0)
                    {
                        cout<<":::Bienvenido:::"<< identificacion<<endl;
                        cout<<"1- Consultar saldo"<<endl;
                        cout<<"2- Retirar"<<endl;
                        cout<<"3-Consignar"<<endl;
                        cout<<"0- para salir"<<endl;
                        cin>>opcion;

                        switch (opcion) {

                        case 1:{
                            cout<<"Su saldo es:"<<plata<<endl;


                        }

                        break;

                        case 2:
                        {
                            cout<<"Cuanto deseas retirar: "<<endl;

                            cin>>retirar;

                            resul=restar(plata, retirar);
                            cout<<"Se retiro "<<retirar<<" Su saldo es: "<<resul-1000<<endl;


                        }
                        break;

                        case 3:{

                            cout<<"Cuanto desear consignar: "<<endl;
                            cin>>consignar;

                            resul=sumar(plata,consignar);

                            cout<<"Vas a consignar  "<<consignar<<" su saldo es: "<<resul<<endl;
                        }

                        default:{

                            if(opcion!=0)
                                cout<<"opcion no valida"<<endl;
                            break;
                        }

                        }
                    }
                }
            }
            break;



            default:{

                if(opcion!=0)
                    cout<<"opcion no valida"<<endl;
                break;
            }
            }
        }
    }
    cout << "Hello World!" << endl;

    return 0;
}

// Lee texto desde un archivo
string leerArchivo(const string& nombre) {
    ifstream archivo(nombre);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombre << endl;
        return "";
    }
    string contenido((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    archivo.close();
    return contenido;
}

// Guarda texto en un archivo
void guardarArchivo(const string& nombre, const string& contenido) {
    ofstream archivo(nombre);
    if (!archivo.is_open()) {
        cout << "No se pudo guardar el archivo: " << nombre << endl;
        return;
    }
    archivo << contenido;
    archivo.close();
}

// Codifica invirtiendo los bits
string codificar(const string& texto) {
    string resultado = texto;
    for (char& c : resultado)
        c = ~c; // invierte los bits
    return resultado;
}

// Decodifica (misma operación)
string decodificar(const string& texto) {
    return codificar(texto); // invertir 2 veces recupera el original
}

float sumar(float saldo, float consignacion){

    saldo = saldo+consignacion;

    return saldo;
}
float restar(float saldo, float retiro){

    saldo=saldo-retiro;

    return saldo;
}
