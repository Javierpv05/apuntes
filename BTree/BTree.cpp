#include <iostream>
#include <queue>

using namespace std;

/*
    ARBOL BINARIO

    Un árbol binario es una estructura donde cada nodo
    puede tener como máximo dos hijos:

        - hijo izquierdo
        - hijo derecho

    IMPORTANTE:
    Un árbol binario NO tiene una regla de orden.

    Por eso, para esta implementación:

        - Inserción: por niveles.
        - Búsqueda: recorrido por niveles.
        - Eliminación: eliminamos el nodo encontrado
          reemplazándolo por el último nodo del árbol.

    Ejemplo:

             10
            /  \
           20   30
          / \
         40  50

    No importa que 20 sea mayor que 10.
    Esto NO es un BST.
*/

struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(int valor) {
        this->valor = valor;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

class ArbolBinario {

private:

    Nodo* raiz;

public:

    ArbolBinario() {
        raiz = nullptr;
    }

    // ------------------------------------------------
    // INSERTAR
    // ------------------------------------------------

    void insertar(int valor) {

        Nodo* nuevo = new Nodo(valor);

        // Si el árbol está vacío
        if (raiz == nullptr) {
            raiz = nuevo;
            return;
        }

        queue<Nodo*> cola;

        cola.push(raiz);

        while (!cola.empty()) {

            Nodo* actual = cola.front();
            cola.pop();

            // Intentamos colocar en el hijo izquierdo
            if (actual->izquierdo == nullptr) {

                actual->izquierdo = nuevo;
                return;
            }

            cola.push(actual->izquierdo);

            // Intentamos colocar en el hijo derecho
            if (actual->derecho == nullptr) {

                actual->derecho = nuevo;
                return;
            }

            cola.push(actual->derecho);
        }
    }

    // ------------------------------------------------
    // BUSCAR
    // ------------------------------------------------

    Nodo* buscar(int valor) {

        if (raiz == nullptr)
            return nullptr;

        queue<Nodo*> cola;

        cola.push(raiz);

        while (!cola.empty()) {

            Nodo* actual = cola.front();
            cola.pop();

            // Encontramos el valor
            if (actual->valor == valor)
                return actual;

            if (actual->izquierdo != nullptr)
                cola.push(actual->izquierdo);

            if (actual->derecho != nullptr)
                cola.push(actual->derecho);
        }

        // No encontrado
        return nullptr;
    }

    // ------------------------------------------------
    // ELIMINAR
    // ------------------------------------------------

    void eliminar(int valor) {

        if (raiz == nullptr)
            return;

        // Caso: solamente existe la raíz
        if (raiz->izquierdo == nullptr &&
            raiz->derecho == nullptr) {

            if (raiz->valor == valor) {

                delete raiz;
                raiz = nullptr;
            }

            return;
        }

        Nodo* objetivo = nullptr;
        Nodo* ultimo = nullptr;
        Nodo* padreUltimo = nullptr;

        queue<pair<Nodo*, Nodo*>> cola;

        cola.push({raiz, nullptr});

        while (!cola.empty()) {

            auto [actual, padre] = cola.front();
            cola.pop();

            if (actual->valor == valor)
                objetivo = actual;

            ultimo = actual;
            padreUltimo = padre;

            if (actual->izquierdo != nullptr)
                cola.push({
                    actual->izquierdo,
                    actual
                });

            if (actual->derecho != nullptr)
                cola.push({
                    actual->derecho,
                    actual
                });
        }

        // El valor no existe
        if (objetivo == nullptr)
            return;

        /*
            Copiamos el valor del último nodo
            al nodo que queremos eliminar.
        */

        objetivo->valor = ultimo->valor;

        /*
            Eliminamos físicamente el último nodo.
        */

        if (padreUltimo->izquierdo == ultimo)
            padreUltimo->izquierdo = nullptr;
        else
            padreUltimo->derecho = nullptr;

        delete ultimo;
    }
};