#include <iostream>
#include <limits> // Para limpiar errores de entrada
using namespace std;

// Estructura del nodo del �rbol geneal�gico
struct Nodo {
    int id;                    // Identificador �nico
    string nombre;             // Nombre del miembro
    string posicion;           // Posici�n (padre, hijo, rey, etc.)
    Nodo* izquierdo;          // Puntero al hijo izquierdo
    Nodo* derecho;            // Puntero al hijo derecho
};

int contadorID = 1; // Contador global para asignar IDs autom�ticamente

// Funci�n para crear un nuevo nodo con nombre y posici�n
Nodo* nuevoNodo(string nombre, string posicion) {
    Nodo* nodo = new Nodo();
    nodo->id = contadorID++;
    nodo->nombre = nombre;
    nodo->posicion = posicion;
    nodo->izquierdo = NULL;
    nodo->derecho = NULL;
    return nodo;
}

// Inserta un nodo en el �rbol binario ordenado alfab�ticamente por nombre
Nodo* insertar(Nodo* raiz, string nombre, string posicion) {
    if (raiz == NULL) {
        return nuevoNodo(nombre, posicion);
    }
    if (nombre < raiz->nombre) {
        raiz->izquierdo = insertar(raiz->izquierdo, nombre, posicion);
    } else if (nombre > raiz->nombre) {
        raiz->derecho = insertar(raiz->derecho, nombre, posicion);
    } else {
        cout << "Ya existe un miembro con ese nombre.\n";
    }
    return raiz;
}

// Recorrido preorden: nodo - izquierdo - derecho
void preorden(Nodo* nodo) {
    if (nodo != NULL) {
        cout << "ID: " << nodo->id << ", Nombre: " << nodo->nombre << ", Posici�n: " << nodo->posicion << endl;
        preorden(nodo->izquierdo);
        preorden(nodo->derecho);
    }
}

// Recorrido inorden: izquierdo - nodo - derecho
void inorden(Nodo* nodo) {
    if (nodo != NULL) {
        inorden(nodo->izquierdo);
        cout << "ID: " << nodo->id << ", Nombre: " << nodo->nombre << ", Posici�n: " << nodo->posicion << endl;
        inorden(nodo->derecho);
    }
}

// Recorrido postorden: izquierdo - derecho - nodo
void postorden(Nodo* nodo) {
    if (nodo != NULL) {
        postorden(nodo->izquierdo);
        postorden(nodo->derecho);
        cout << "ID: " << nodo->id << ", Nombre: " << nodo->nombre << ", Posici�n: " << nodo->posicion << endl;
    }
}

// Buscar un nodo por nombre
Nodo* buscar(Nodo* raiz, string nombre) {
    if (raiz == NULL || raiz->nombre == nombre)
        return raiz;
    if (nombre < raiz->nombre)
        return buscar(raiz->izquierdo, nombre);
    else
        return buscar(raiz->derecho, nombre);
}

// Mostrar men� de opciones
void mostrarMenu() {
    cout << "\n========= MEN� =========" << endl;
    cout << "1. Insertar miembro" << endl;
    cout << "2. Mostrar recorridos" << endl;
    cout << "3. Buscar miembro" << endl;
    cout << "4. Salir" << endl;
    cout << "Seleccione una opci�n: ";
}

int main() {
    Nodo* raiz = NULL;
    int opcion;
    string nombre, posicion;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer

        switch (opcion) {
            case 1:
                cout << "\nNombre: ";
                getline(cin, nombre);
                if (nombre.empty()) {
                    cout << "El nombre no puede estar vac�o.\n";
                    break;
                }
                cout << "Posici�n (padre, hijo, rey, etc.): ";
                getline(cin, posicion);
                raiz = insertar(raiz, nombre, posicion);
                break;

            case 2:
                cout << "\nRecorrido Preorden:\n";
                preorden(raiz);
                cout << "\nRecorrido Inorden:\n";
                inorden(raiz);
                cout << "\nRecorrido Postorden:\n";
                postorden(raiz);
                break;

            case 3:
                cout << "\nBuscar miembro por nombre: ";
                getline(cin, nombre);
                if (nombre.empty()) {
                    cout << "Debe ingresar un nombre.\n";
                    break;
                }
                {
                    Nodo* encontrado = buscar(raiz, nombre);
                    if (encontrado != NULL) {
                        cout << "Encontrado - ID: " << encontrado->id
                             << ", Nombre: " << encontrado->nombre
                             << ", Posici�n: " << encontrado->posicion << endl;
                    } else {
                        cout << "No se encontr� a " << nombre << ".\n";
                    }
                }
                break;

            case 4:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opci�n no v�lida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 4);

    return 0;
}

