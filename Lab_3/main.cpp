#include <iostream>
#include <fstream>
using namespace std;


char* leerArchivo_Original(const char* nombre);
char* encrip_metodo1(char *texto, int tamaño ,int clave);
char* texto_Binario(const char* texto, long tam);
char* codificarMetodo1(const char* binario, long tamBin, int n);

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


char* codificarMetodo1(const char* binario, long tamBin, int n) {
    // Asegurar que la longitud sea múltiplo de n
    long tamAjustado = tamBin;
    if (tamBin % n != 0) {
        tamAjustado = ((tamBin / n) + 1) * n;
    }

    // Crear copia ajustada del binario (con ceros al final si es necesario)
    char* binAjustado = new char[tamAjustado + 1];
    for (long i = 0; i < tamBin; i++) {
        binAjustado[i] = binario[i];
    }
    for (long i = tamBin; i < tamAjustado; i++) {
        binAjustado[i] = '0';
    }
    binAjustado[tamAjustado] = '\0';

    // Resultado codificado
    char* codificado = new char[tamAjustado + 1];
    long numBloques = tamAjustado / n;

    for (long b = 0; b < numBloques; b++) {
        // Copiar bloque original al resultado (por ahora)
        for (int i = 0; i < n; i++) {
            codificado[b * n + i] = binAjustado[b * n + i];
        }

        if (b == 0) {
            // Primer bloque: invertir todos los bits
            for (int i = 0; i < n; i++) {
                codificado[i] = (codificado[i] == '0') ? '1' : '0';
            }
        } else {
            // Analizar bloque anterior del binario ORIGINAL (binAjustado)
            const char* bloqueAnt = binAjustado + (b - 1) * n;
            int ceros = 0, unos = 0;
            for (int i = 0; i < n; i++) {
                if (bloqueAnt[i] == '0') ceros++;
                else unos++;
            }

            char* bloqueActual = codificado + b * n;

            if (ceros == unos) {
                // Invertir todos los bits del bloque actual
                for (int i = 0; i < n; i++) {
                    bloqueActual[i] = (bloqueActual[i] == '0') ? '1' : '0';
                }
            } else if (ceros > unos) {
                // Invertir cada 2 bits: [0,1] → [1,0], [2,3] → [3,2], etc.
                for (int i = 0; i < n; i += 2) {
                    if (i + 1 < n) {
                        char temp = bloqueActual[i];
                        bloqueActual[i] = bloqueActual[i + 1];
                        bloqueActual[i + 1] = temp;
                    }
                }
            } else { // unos > ceros
                // Invertir cada 3 bits: [0,1,2] → [2,0,1]
                for (int i = 0; i < n; i += 3) {
                    if (i + 2 < n) {
                        char temp0 = bloqueActual[i];
                        char temp1 = bloqueActual[i + 1];
                        char temp2 = bloqueActual[i + 2];
                        bloqueActual[i]     = temp2; // posición 0 ← 2
                        bloqueActual[i + 1] = temp0; // posición 1 ← 0
                        bloqueActual[i + 2] = temp1; // posición 2 ← 1
                    }
                    // Si quedan 1 o 2 bits al final (n no múltiplo de 3), se dejan igual
                }
            }
        }
    }

    codificado[tamAjustado] = '\0';
    delete[] binAjustado;
    return codificado;
}



