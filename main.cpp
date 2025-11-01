#include <iostream>
#include <fstream>
#include <string>
using namespace std;



float sumar(float saldo, float consignacion);
float restar(float saldo, float retiro);
string textoABinario(string texto);
string charABinario(char c);
string binarioATexto(string binario);
char binarioAChar(string binario8bits);
string archivoABinario(string& nombreArchivo);
string encriptarMetodo2(string binario, int n);

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
                string nombreArchivo;
                string contenido;
                string result;
                string textresul;
                cout<<"Ingrese el nombre del archivo"<<endl;
                cin>>nombreArchivo;
                contenido=archivoABinario(nombreArchivo);
               result= textoABinario(contenido);
                cout<<"Binario"<<result<<endl;
               textresul=binarioATexto(contenido);
                cout<<"Texto comvertido de nuevo"<<textresul<<endl;
               encriptarMetodo2(contenido,4);
                /*
                char* buffer = leerArchivo_Original("ejemplo.txt");
                if (buffer == nullptr) {
                    cout << "No se pudo leer el archivo.\n";
                    break;
                }

                // Calcular tamaño (como 'long')
                long tam = 0;
                while (buffer[tam] != '\0') {
                    tam++;
                }

                char* binario = texto_Binario(buffer, tam);
                cout << "Binario:\n" << binario << "\n";

                delete[] buffer;
                delete[] binario;
                break;
            }
*/

            }

            case 2:{

                cout<<"Desencriptar"<<endl;


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

string textoABinario(string texto) {
    string binarioCompleto = "";

    for (int i = 0; i < texto.length(); i++) {
        binarioCompleto += charABinario(texto[i]);
    }

    return binarioCompleto;
}
string charABinario(char c) {
    string binario = "";

    for (int i = 7; i >= 0; i--) {

        if ((c >> i) & 1) {
            binario += '1';
        } else {
            binario += '0';
        }
    }
    return binario;
}

string binarioATexto(string binario) {
    string texto = "";


    for (int i = 0; i < binario.length(); i += 8) {

        string bloque8 = binario.substr(i, 8);


        texto += binarioAChar(bloque8);
    }

    return texto;
}

char binarioAChar(string binario8bits) {
    int valor = 0;


    for (int i = 0; i < 8; i++) {
        valor = valor * 2;

        if (binario8bits[i] == '1') {
            valor += 1;
        }
    }

    return (char)valor;
}
string archivoABinario(string& nombreArchivo) {

    string temArchivo=nombreArchivo;
    ifstream archivo(nombreArchivo);


    if (!archivo.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo '" << nombreArchivo << "'" << endl;
        return "";
    }

    // Lee todo el contenido
    string contenido = "";
    string linea;

    while (getline(archivo, linea)) {
        contenido += linea;

        if (!archivo.eof()) {
            contenido += '\n';
        }
    }

    archivo.close();

    cout << "Archivo leido: " << contenido.length() << " caracteres" << endl;
    cout<<"contenido"<<contenido<<endl;
    // Convierte... el contenido a binario

    return textoABinario(contenido);
}

//Funciones para encriptar y desencriptar
string encriptarBloque(string bloque) {
    int n = bloque.length();

    if (n <= 1) {
        return bloque;
    }

    string encriptado = "";


    encriptado += bloque[n - 1];


    for (int i = 0; i < n - 1; i++) {
        encriptado += bloque[i];
    }

    return encriptado;
}


string desencriptarBloque(string bloque) {
    int n = bloque.length();

    if (n <= 1) {
        return bloque;
    }

    string desencriptado = "";


    for (int i = 1; i < n; i++) {
        desencriptado += bloque[i];
    }


    desencriptado += bloque[0];

    return desencriptado;
}


string encriptarMetodo2(string binario, int n) {


    if (n <= 0) {
        cout << "ERROR: n debe ser mayor que 0" << endl;
        return binario;
    }

    string resultado = "";
    int longitud = binario.length();


    for (int i = 0; i < longitud; i += n) {

        string bloque = "";

        for (int j = i; j < i + n && j < longitud; j++) {
            bloque += binario[j];
        }


        string bloqueEncriptado = encriptarBloque(bloque);


        resultado += bloqueEncriptado;
    }

    return resultado;
}


string desencriptarMetodo2(string binarioEncriptado, int n) {

    if (n <= 0) {
        cout << "ERROR: n debe ser mayor que 0" << endl;
        return binarioEncriptado;
    }

    string resultado = "";
    int longitud = binarioEncriptado.length();

    for (int i = 0; i < longitud; i += n) {

        string bloque = "";

        for (int j = i; j < i + n && j < longitud; j++) {
            bloque += binarioEncriptado[j];
        }


        string bloqueDesencriptado = desencriptarBloque(bloque);


        resultado += bloqueDesencriptado;
    }

    return resultado;
}
