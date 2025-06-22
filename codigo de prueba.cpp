#include <iostream>
using namespace std;

// Basado en la estructura de la imagen proporcionada
struct Nodo {
    int id;                  // Identificador único
    string nombre;           // Nombre del miembro
    string posicion;         // Posición (padre, hijo, rey, etc.)
    Nodo* izquierdo;         // Hijo izquierdo
    Nodo* derecho;           // Hijo derecho
};

int contadorID = 1; // Contador global para asignar IDs automáticamente

// Crear un nuevo nodo
Nodo* nuevoNodo(string nombre, string posicion) {
    Nodo* nodo = new Nodo();
    nodo->id = contadorID++;
    nodo->nombre = nombre;
    nodo->posicion = posicion;
    nodo->izquierdo = NULL;
    nodo->derecho = NULL;
    return nodo;
}

// Insertar nodos de manera binaria según el nombre (orden alfabético)
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

// Recorridos
void preorden(Nodo* nodo) {
    if (nodo != NULL) {
        cout << "ID: " << nodo->id << ", Nombre: " << nodo->nombre << ", Posición: " << nodo->posicion << endl;
        preorden(nodo->izquierdo);
        preorden(nodo->derecho);
    }
}

void inorden(Nodo* nodo) {
    if (nodo != NULL) {
        inorden(nodo->izquierdo);
        cout << "ID: " << nodo->id << ", Nombre: " << nodo->nombre << ", Posición: " << nodo->posicion << endl;
        inorden(nodo->derecho);
    }
}

void postorden(Nodo* nodo) {
    if (nodo != NULL) {
        postorden(nodo->izquierdo);
        postorden(nodo->derecho);
        cout << "ID: " << nodo->id << ", Nombre: " << nodo->nombre << ", Posición: " << nodo->posicion << endl;
    }
}

// Buscar por nombre
Nodo* buscar(Nodo* raiz, string nombre) {
    if (raiz == NULL || raiz->nombre == nombre)
        return raiz;
    if (nombre < raiz->nombre)
        return buscar(raiz->izquierdo, nombre);
    else
        return buscar(raiz->derecho, nombre);
}

int main() {
    Nodo* raiz = NULL;
    int n;
    string nombre, posicion;

    cout << "¿Cuántos miembros deseas registrar?: ";
    cin >> n;
    cin.ignore(); // Limpiar buffer

    for (int i = 0; i < n; i++) {
        cout << "Nombre: ";
        getline(cin, nombre);
        cout << "Posición (padre, hijo, rey, etc.): ";
        getline(cin, posicion);
        raiz = insertar(raiz, nombre, posicion);
    }

    cout << "\nRecorrido Preorden:\n";
    preorden(raiz);

    cout << "\nRecorrido Inorden:\n";
    inorden(raiz);

    cout << "\nRecorrido Postorden:\n";
    postorden(raiz);

    // Buscar miembro
    cout << "\nBuscar miembro por nombre: ";
    getline(cin, nombre);
    Nodo* encontrado = buscar(raiz, nombre);
    if (encontrado != NULL) {
        cout << "Encontrado - ID: " << encontrado->id << ", Nombre: " << encontrado->nombre << ", Posición: " << encontrado->posicion << endl;
    } else {
        cout << "No se encontró a " << nombre << ".\n";
    }

    return 0;
}

