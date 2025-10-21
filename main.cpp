#include <iostream>

#include <fstream>
using namespace std;


char* leerArchivo_Original(const char* nombre);
char* encrip_metodo1(char *texto, int tamaño ,int clave);
char* texto_Binario(const char* texto, long tam);
char* codificarMetodo1(const char* binario, long tamBin, int n);
void guardarArchivoBinario(const char* binario, long tamBin, const char* nombreSalida);
char* leerArchivoBinarioComoBinario(const char* nombre, long& tamBits);
char* decodificarMetodo1(const char* binarioCodif, long tamBin, int n);
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

                cout << "Ingrese nombre del archivo de entrada: ";
                string nombreIn;
                cin >> nombreIn;

                cout << "Ingrese nombre del archivo de salida: ";
                string nombreOut;
                cin >> nombreOut;

                cout << "Ingrese la semilla n: ";
                int n;
                cin >> n;

                cout << "Ingrese método (1 o 2): ";
                int metodo;
                cin >> metodo;

                if (metodo != 1) {
                    cout << "Solo se implementa el método 1 por ahora.\n";
                    break;
                }

                // 1. Leer archivo original
                char* contenido = leerArchivo_Original(nombreIn.c_str());
                if (!contenido) break;

                // 2. Calcular tamaño real
                long tam = 0;
                while (contenido[tam] != '\0') tam++;

                // 3. Convertir a binario
                char* binario = texto_Binario(contenido, tam);

                // 4. Codificar
                long tamBin = tam * 8;
                char* binCodif = codificarMetodo1(binario, tamBin, n);

                // 5. Guardar como binario
                long tamCodif = 0;
                while (binCodif[tamCodif] != '\0') tamCodif++;
                guardarArchivoBinario(binCodif, tamCodif, nombreOut.c_str());

                cout << "Archivo codificado guardado en: " << nombreOut << "\n";

                // Liberar memoria
                delete[] contenido;
                delete[] binario;
                delete[] binCodif;
                break;

            }
            case 2: {
                cout << "Archivo codificado (entrada): ";
                string in;
                cin >> in;
                cout << "Archivo decodificado (salida): ";
                string out;
                cin >> out;
                cout << "Semilla n: ";
                int n;
                cin >> n;
                cout << "Método (1): ";
                int m;
                cin >> m;

                if (m != 1) { cout << "Solo método 1.\n"; break; }

                long tamBits;
                char* binCodif = leerArchivoBinarioComoBinario(in.c_str(), tamBits);
                if (!binCodif) break;

                char* binOriginal = decodificarMetodo1(binCodif, tamBits, n);

                // Guardar como archivo de texto
                ofstream archivo(out);
                if (!archivo.is_open()) {
                    cerr << "Error al crear " << out << "\n";
                } else {
                    // Convertir de binario ('0'/'1') a texto
                    long tamBytes = 0;
                    while (binOriginal[tamBytes] != '\0') tamBytes++;
                    tamBytes /= 8;
                    for (long i = 0; i < tamBytes; i++) {
                        char byte = 0;
                        for (int j = 0; j < 8; j++) {
                            if (binOriginal[i * 8 + j] == '1')
                                byte |= (1 << (7 - j));
                        }
                        archivo << byte;
                    }
                    archivo.close();
                    cout << "Archivo decodificado guardado en: " << out << "\n";
                }

                delete[] binCodif;
                delete[] binOriginal;
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


void guardarArchivoBinario(const char* binario, long tamBin, const char* nombreSalida) {
    ofstream archivo(nombreSalida, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo crear el archivo de salida.\n";
        return;
    }

    // Convertir cadena de '0'/'1' a bytes reales
    for (long i = 0; i < tamBin; i += 8) {
        char byte = 0;
        for (int j = 0; j < 8 && (i + j) < tamBin; j++) {
            if (binario[i + j] == '1') {
                byte |= (1 << (7 - j));
            }
        }
        archivo.write(&byte, 1);
    }
    archivo.close();
}


char* decodificarMetodo1(const char* binarioCodif, long tamBin, int n) {
    // Asegurar múltiplo de n
    long tamAjustado = (tamBin % n == 0) ? tamBin : ((tamBin / n) + 1) * n;
    char* codifAjustado = new char[tamAjustado + 1];
    for (long i = 0; i < tamBin; i++) codifAjustado[i] = binarioCodif[i];
    for (long i = tamBin; i < tamAjustado; i++) codifAjustado[i] = '0';
    codifAjustado[tamAjustado] = '\0';

    // Resultado: binario original reconstruido
    char* original = new char[tamAjustado + 1];
    long numBloques = tamAjustado / n;

    for (long b = 0; b < numBloques; b++) {
        const char* bloqueCodif = codifAjustado + b * n;
        char* bloqueOrig = original + b * n;

        if (b == 0) {
            // Primer bloque: invertir todos los bits
            for (int i = 0; i < n; i++) {
                bloqueOrig[i] = (bloqueCodif[i] == '0') ? '1' : '0';
            }
        } else {
            // Usar bloque original anterior (ya reconstruido)
            const char* bloqueAntOrig = original + (b - 1) * n;
            int ceros = 0, unos = 0;
            for (int i = 0; i < n; i++) {
                if (bloqueAntOrig[i] == '0') ceros++;
                else unos++;
            }

            // Copiar bloque codificado temporalmente
            for (int i = 0; i < n; i++) {
                bloqueOrig[i] = bloqueCodif[i];
            }

            if (ceros == unos) {
                // Invertir todos los bits
                for (int i = 0; i < n; i++) {
                    bloqueOrig[i] = (bloqueOrig[i] == '0') ? '1' : '0';
                }
            } else if (ceros > unos) {
                // Invertir cada 2 bits (misma operación que en codificación)
                for (int i = 0; i < n; i += 2) {
                    if (i + 1 < n) {
                        char temp = bloqueOrig[i];
                        bloqueOrig[i] = bloqueOrig[i + 1];
                        bloqueOrig[i + 1] = temp;
                    }
                }
            } else { // unos > ceros
                // Aplicar permutación INVERSA para 3 bits: [x,y,z] → [y,z,x]
                for (int i = 0; i < n; i += 3) {
                    if (i + 2 < n) {
                        char x = bloqueOrig[i];
                        char y = bloqueOrig[i + 1];
                        char z = bloqueOrig[i + 2];
                        bloqueOrig[i]     = y; // posición 0 ← y
                        bloqueOrig[i + 1] = z; // posición 1 ← z
                        bloqueOrig[i + 2] = x; // posición 2 ← x
                    }
                }
            }
        }
    }

    original[tamAjustado] = '\0';
    delete[] codifAjustado;
    return original;
}

char* leerArchivoBinarioComoBinario(const char* nombre, long& tamBits) {
    ifstream archivo(nombre, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error al abrir " << nombre << "\n";
        return nullptr;
    }

    // Leer todo el archivo en un buffer
    archivo.seekg(0, ios::end);
    long tamBytes = archivo.tellg();
    archivo.seekg(0, ios::beg);

    char* buffer = new char[tamBytes];
    archivo.read(buffer, tamBytes);
    archivo.close();

    // Convertir a cadena de '0'/'1'
    tamBits = tamBytes * 8;
    char* binario = new char[tamBits + 1];
    int pos = 0;
    for (long i = 0; i < tamBytes; i++) {
        unsigned char c = buffer[i];
        for (int bit = 7; bit >= 0; bit--) {
            binario[pos++] = ((c >> bit) & 1) ? '1' : '0';
        }
    }
    binario[pos] = '\0';

    delete[] buffer;
    return binario;
}


