// Unorderedmap implementation
#include <bits/stdc++.h>
using namespace std;

// IMPLEMENTACIÓN DE UNORDERED_MAP DESDE CERO

template <typename K, typename V>
class MiMapa {
private:
    // Nodo que guarda clave, valor y puntero al siguiente (lista enlazada)
    struct Nodo {
        K clave;
        V valor;
        Nodo* next;
        Nodo(const K& k, const V& v) : clave(k), valor(v), next(nullptr) {}
    };

    vector<Nodo*> tabla;       // Arreglo de buckets (cada uno es una lista)
    int numElementos;          // Cuántos pares clave-valor hay
    int numBuckets;            // Cuántos buckets tiene la tabla
    const double MAX_LOAD = 1.0;  // Factor de carga máximo antes de rehash

        // FUNCIÓN HASH: convierte la clave en un índice
    int HASH(const K& clave) {
        return hash<K>()(clave) % numBuckets;
    }

    // REHASH: duplica el tamaño y reinserta todos los elementos
    // Se llama cuando el factor de carga supera MAX_LOAD
    void REHASH() {
        vector<Nodo*> viejaTabla = tabla;
        int viejoNumBuckets = numBuckets;
        numBuckets *= 2;
        tabla.assign(numBuckets, nullptr);
        numElementos = 0;

        for (int i = 0; i < viejoNumBuckets; i++) {
            Nodo* actual = viejaTabla[i];
            while (actual != nullptr) {
                INSERTAR(actual->clave, actual->valor);
                Nodo* temp = actual;
                actual = actual->next;
                delete temp;
            }
        }
    }

public:
 MiMapa(int tamInicial = 10) {
        numBuckets = tamInicial;
        numElementos = 0;
        tabla.assign(numBuckets, nullptr);
    }
    ~MiMapa() {
        for (int i = 0; i < numBuckets; i++) {
            Nodo* actual = tabla[i];
            while (actual != nullptr) {
                Nodo* temp = actual;
                actual = actual->next;
                delete temp;
            }
        }
    }
    // INSERTAR(clave, valor): inserta o actualiza un par clave-valor
    // Si la clave ya existe, actualiza su valor.
    // Si no existe, la agrega al bucket correspondiente.
     void INSERTAR(const K& clave, const V& valor) {
        if ((double)numElementos / numBuckets >= MAX_LOAD) {
            REHASH();
        }

        int indice = HASH(clave);
        Nodo* actual = tabla[indice];

        // Buscar si la clave ya existe
        while (actual != nullptr) {
            if (actual->clave == clave) {
                actual->valor = valor;  // Actualizar
                return;
            }
            actual = actual->next;
        }

        // Si no existe, insertar al inicio de la lista
        Nodo* nuevo = new Nodo(clave, valor);
        nuevo->next = tabla[indice];
        tabla[indice] = nuevo;
        numElementos++;
    }

    // BUSCAR(clave): devuelve un puntero al valor o nullptr si no existe
    V* BUSCAR(const K& clave) {
        int indice = HASH(clave);
        Nodo* actual = tabla[indice];
        while (actual != nullptr) {
            if (actual->clave == clave) {
                return &actual->valor;
            }
            actual = actual->next;
        }
        return nullptr;
    }
    // EXISTE(clave): devuelve true si la clave está en el mapa
    bool EXISTE(const K& clave) {
        return BUSCAR(clave) != nullptr;
    }

    // ELIMINAR(clave): elimina la clave y su valor. Devuelve true si se eliminó.
    bool ELIMINAR(const K& clave) {
        int indice = HASH(clave);
        Nodo* actual = tabla[indice];
        Nodo* anterior = nullptr;

        while (actual != nullptr) {
            if (actual->clave == clave) {
                if (anterior == nullptr) {
                    tabla[indice] = actual->next;
                } else {
                    anterior->next = actual->next;
                }
                delete actual;
                numElementos--;
                return true;
            }
            anterior = actual;
            actual = actual->next;
        }
        return false;
    }

    // OPERADOR[]: accede o crea un valor asociado a una clave
    // Si la clave no existe, la crea con el valor por defecto de V.
    V& operator[](const K& clave) {
        V* valor = BUSCAR(clave);
        if (valor != nullptr) {
            return *valor;
        }
        INSERTAR(clave, V());
        return *BUSCAR(clave);
    }

    // TAMANO(): devuelve el número de elementos almacenados
    int TAMANO() const {
        return numElementos;
    }

    // VACIO(): devuelve true si el mapa no tiene elementos
    bool VACIO() const {
        return numElementos == 0;
    }

    // LIMPIAR(): elimina todos los elementos del mapa
    void LIMPIAR() {
        for (int i = 0; i < numBuckets; i++) {
            Nodo* actual = tabla[i];
            while (actual != nullptr) {
                Nodo* temp = actual;
                actual = actual->next;
                delete temp;
            }
            tabla[i] = nullptr;
        }
        numElementos = 0;
    }

    // FACTOR_CARGA(): devuelve el factor de carga actual (elementos / buckets)
    double FACTOR_CARGA() const {
        return (double)numElementos / numBuckets;
    }

    // NUM_BUCKETS(): devuelve la cantidad de buckets actuales
    int NUM_BUCKETS() const {
        return numBuckets;
    }

    // RESERVAR(n): reserva espacio para al menos n elementos
    // Útil para evitar rehashing durante inserciones masivas.
    void RESERVAR(int n) {
        int bucketsNecesarios = (int)(n / MAX_LOAD) + 1;
        while (numBuckets < bucketsNecesarios) {
            REHASH();
        }
    }
};

// EJEMPLO DE USO
int main() {
    MiMapa<string, int> edades(5);

    edades.INSERTAR("Ana", 25);
    edades.INSERTAR("Luis", 30);
    edades.INSERTAR("Ana", 26);  // Actualiza

    cout << "Edad de Ana: " << *edades.BUSCAR("Ana") << "\n";  // 26
    cout << "Existe Luis? " << (edades.EXISTE("Luis") ? "Sí" : "No") << "\n";
    cout << "Tamaño: " << edades.TAMANO() << "\n";

    edades.ELIMINAR("Luis");
    cout << "Existe Luis tras eliminar? " << (edades.EXISTE("Luis") ? "Sí" : "No") << "\n";

    edades["Pedro"] = 40;  // Crea con operator[]
    cout << "Edad de Pedro: " << edades["Pedro"] << "\n";

    return 0;
}