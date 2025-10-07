#include <iostream>
#include <fstream>
using namespace std;


char* leerArchivo_Original(const char* nombre);
char* encrip_xor(char *texto, int tamaño ,int clave);
char* texto_Binario(const char* texto, long tam);

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


char* texto_Binario(const char* texto, long tam) {
    if (tam <= 0) {
        char* vacio = new char[1];
        vacio[0] = '\0';
        return vacio;
    }

    long tamBin = tam * 8;
    char* binario = new char[tamBin + 1];
    int pos = 0;

    for (long i = 0; i < tam; i++) {
        unsigned char c = static_cast<unsigned char>(texto[i]);
        for (int bit = 7; bit >= 0; bit--) {
            binario[pos++] = ((c >> bit) & 1) ? '1' : '0';
        }
    }
    binario[pos] = '\0';
    return binario;
}

























