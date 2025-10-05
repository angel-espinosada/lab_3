#include <iostream>
#include <fstream>
using namespace std;


char* leerArchivo_Original(const char* nombre);
char* encrip_xor(char *texto, int tamaño ,int clave);

int main()
{

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
            break;
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




char* leerArchivo_Original(const char* nombre) {
    ifstream archivo(nombre, ios::binary); // modo binario para preservar todo
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo '" << nombre << "'\n";
        return nullptr;
    }

    // Ir al final para saber el tamaño
    archivo.seekg(0, ios::end);
    streampos tam = archivo.tellg();
    archivo.seekg(0, ios::beg);

    // Reservar memoria exacta (+1 para '\0' si quieres tratarlo como cadena)
    char* buffer = new char[tam + 1];
    archivo.read(buffer, tam);
    buffer[tam] = '\0'; // opcional: solo si vas a usarlo como cadena C

    archivo.close();
    return buffer; // ¡Recuerda liberar con delete[]!
}




























