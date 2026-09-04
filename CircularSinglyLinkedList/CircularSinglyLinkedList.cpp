#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    CircularLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~CircularLinkedList() { clear(); }

    // Insertar al frente
    void insertFront(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
            tail->next = head;  // apunta a sí mismo
        } else {
            newNode->next = head;
            head = newNode;
            tail->next = head;  // tail sigue apuntando a head
        }
        size++;
    }

    // Insertar al final
    void insertBack(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
            tail->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
        size++;
    }

    // Insertar en posición (0 = frente)
    void insertAt(int val, int pos) {
        if (pos < 0 || pos > size) throw out_of_range("Posición inválida");
        if (pos == 0) { insertFront(val); return; }
        if (pos == size) { insertBack(val); return; }

        Node* newNode = new Node(val);
        Node* temp = head;
        for (int i = 0; i < pos - 1; ++i) temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    }

    // Eliminar frente
    void removeFront() {
        if (!head) return;
        if (head == tail) { // único nodo
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = head;
            head = head->next;
            tail->next = head;
            delete temp;
        }
        size--;
    }

    // Eliminar final
    void removeBack() {
        if (!head) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = head;
            while (temp->next != tail) temp = temp->next;
            delete tail;
            tail = temp;
            tail->next = head;
        }
        size--;
    }

    // Eliminar en posición
    void removeAt(int pos) {
        if (pos < 0 || pos >= size) throw out_of_range("Posición inválida");
        if (pos == 0) { removeFront(); return; }
        if (pos == size - 1) { removeBack(); return; }

        Node* temp = head;
        for (int i = 0; i < pos - 1; ++i) temp = temp->next;
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        size--;
    }

    // Eliminar por valor (primera ocurrencia)
    void removeByValue(int val) {
        if (!head) return;
        Node* curr = head;
        Node* prev = tail; // el anterior al head es tail
        do {
            if (curr->data == val) {
                if (curr == head) { removeFront(); return; }
                if (curr == tail) { removeBack(); return; }
                prev->next = curr->next;
                delete curr;
                size--;
                return;
            }
            prev = curr;
            curr = curr->next;
        } while (curr != head);
    }

    // Búsqueda
    bool search(int val) const {
        if (!head) return false;
        Node* temp = head;
        do {
            if (temp->data == val) return true;
            temp = temp->next;
        } while (temp != head);
        return false;
    }

    int getSize() const { return size; }
    bool isEmpty() const { return head == nullptr; }

    // Imprimir (cuidado con listas vacías)
    void print() const {
        if (!head) { cout << "Lista vacía\n"; return; }
        Node* temp = head;
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }

    // Invertir orden (redefiniendo head y tail y reconstruyendo enlaces)
    void reverse() {
        if (!head || head == tail) return;
        Node* prev = tail;
        Node* curr = head;
        Node* next = nullptr;
        do {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        } while (curr != head);
        // Al final, head y tail intercambian
        swap(head, tail);
        tail->next = head; // aseguramos circularidad
    }

    // Vaciar lista
    void clear() {
        if (!head) return;
        Node* curr = head;
        do {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        } while (curr != head);
        head = tail = nullptr;
        size = 0;
    }

    // Obtener elemento en posición
    int getAt(int pos) const {
        if (pos < 0 || pos >= size) throw out_of_range("Posición inválida");
        Node* temp = head;
        for (int i = 0; i < pos; ++i) temp = temp->next;
        return temp->data;
    }

    // Actualizar valor en posición
    void updateAt(int pos, int newVal) {
        if (pos < 0 || pos >= size) throw out_of_range("Posición inválida");
        Node* temp = head;
        for (int i = 0; i < pos; ++i) temp = temp->next;
        temp->data = newVal;
    }
};

// --- MAIN para probar ---
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    CircularLinkedList list;
    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);
    list.insertFront(5);
    list.insertAt(15, 2);
    list.print(); // 5 10 15 20 30

    list.removeFront();
    list.removeBack();
    list.removeAt(1);
    list.print(); // 10 20

    list.insertBack(100);
    list.reverse();
    list.print(); // 100 20 10

    cout << "Tamaño: " << list.getSize() << endl;
    cout << "¿Está 15? " << (list.search(15) ? "Sí" : "No") << endl;

    return 0;
}