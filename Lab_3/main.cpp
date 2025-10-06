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

                char* contenido = leerArchivo_Original("ejemplo.txt");
                if (contenido == nullptr) {
                    cout << "No se pudo abrir 'ejemplo.txt'\n";
                } else {
                    cout << "Contenido del archivo:\n";
                    cout << contenido << endl;  // imprime tal como está
                    delete[] contenido;         // liberar memoria
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

    // Reservar memoria exacta
    char* buffer = new char[tam + 1];
    archivo.read(buffer, tam);
    buffer[tam] = '\0';

    archivo.close();
    return buffer;
}




























