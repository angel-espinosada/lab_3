#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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

// Codifica invirtiendo los bits (sencillo)
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

int main() {
    int opcion = 1;
    while (opcion != 0) {
        cout << "\n--- Menu ---\n";
        cout << "1. Codificar archivo\n";
        cout << "2. Decodificar archivo\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string entrada, salida;
            cout << "Archivo de entrada: ";
            cin >> entrada;
            cout << "Archivo de salida: ";
            cin >> salida;

            string texto = leerArchivo(entrada);
            string codificado = codificar(texto);
            guardarArchivo(salida, codificado);

            cout << "Archivo codificado guardado como: " << salida << endl;
        }
        else if (opcion == 2) {
            string entrada, salida;
            cout << "Archivo codificado (entrada): ";
            cin >> entrada;
            cout << "Archivo decodificado (salida): ";
            cin >> salida;

            string texto = leerArchivo(entrada);
            string decodificado = decodificar(texto);
            guardarArchivo(salida, decodificado);

            cout << "Archivo decodificado guardado como: " << salida << endl;
        }
        else if (opcion != 0) {
            cout << "Opcion no valida.\n";
        }
    }

    cout << "Programa finalizado.\n";
    return 0;
}


