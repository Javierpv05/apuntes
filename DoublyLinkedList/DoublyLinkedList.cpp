#include <bits/stdc++.h>
using namespace std;

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    DNode* head;
    DNode* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~DoublyLinkedList() { clear(); }

    // Insertar al frente
    void insertFront(int val) {
        DNode* newNode = new DNode(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    // Insertar al final
    void insertBack(int val) {
        DNode* newNode = new DNode(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    // Insertar en posición
    void insertAt(int val, int pos) {
        if (pos < 0 || pos > size) throw out_of_range("Posición inválida");
        if (pos == 0) { insertFront(val); return; }
        if (pos == size) { insertBack(val); return; }

        DNode* temp = head;
        for (int i = 0; i < pos; ++i) temp = temp->next;
        DNode* newNode = new DNode(val);
        // temp es el nodo que estará después de newNode
        DNode* prevNode = temp->prev;
        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = temp;
        temp->prev = newNode;
        size++;
    }

    // Eliminar frente
    void removeFront() {
        if (!head) return;
        DNode* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        size--;
    }

    // Eliminar final
    void removeBack() {
        if (!head) return;
        DNode* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        size--;
    }

    // Eliminar en posición
    void removeAt(int pos) {
        if (pos < 0 || pos >= size) throw out_of_range("Posición inválida");
        if (pos == 0) { removeFront(); return; }
        if (pos == size - 1) { removeBack(); return; }

        DNode* temp = head;
        for (int i = 0; i < pos; ++i) temp = temp->next;
        DNode* prevNode = temp->prev;
        DNode* nextNode = temp->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        delete temp;
        size--;
    }

    // Eliminar por valor (primera ocurrencia)
    void removeByValue(int val) {
        if (!head) return;
        DNode* curr = head;
        while (curr && curr->data != val) curr = curr->next;
        if (!curr) return; // no encontrado

        if (curr == head) { removeFront(); return; }
        if (curr == tail) { removeBack(); return; }

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        size--;
    }

    // Búsqueda
    bool search(int val) const {
        DNode* curr = head;
        while (curr) {
            if (curr->data == val) return true;
            curr = curr->next;
        }
        return false;
    }

    int getSize() const { return size; }
    bool isEmpty() const { return head == nullptr; }

    // Imprimir de frente
    void print() const {
        DNode* curr = head;
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    // Imprimir inverso (opcional)
    void printReverse() const {
        DNode* curr = tail;
        while (curr) {
            cout << curr->data << " ";
            curr = curr->prev;
        }
        cout << endl;
    }

    // Invertir la lista (intercambiar prev y next de cada nodo)
    void reverse() {
        if (!head || head == tail) return;
        DNode* curr = head;
        while (curr) {
            swap(curr->prev, curr->next);
            curr = curr->prev; // porque despues del swap, prev es el siguiente original
        }
        swap(head, tail);
    }

    // Vaciar
    void clear() {
        while (head) {
            DNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    int getAt(int pos) const {
        if (pos < 0 || pos >= size) throw out_of_range("Posición inválida");
        DNode* curr = head;
        for (int i = 0; i < pos; ++i) curr = curr->next;
        return curr->data;
    }

    void updateAt(int pos, int newVal) {
        if (pos < 0 || pos >= size) throw out_of_range("Posición inválida");
        DNode* curr = head;
        for (int i = 0; i < pos; ++i) curr = curr->next;
        curr->data = newVal;
    }
};

// --- MAIN para probar ---
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    DoublyLinkedList list;
    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);
    list.insertFront(5);
    list.insertAt(15, 2);
    list.print(); // 5 10 15 20 30

    list.removeFront();
    list.removeBack();
    list.removeAt(1);
    list.print(); // 10 15

    list.insertBack(100);
    list.reverse();
    list.print(); // 100 15 10

    cout << "Tamaño: " << list.getSize() << endl;
    cout << "¿Está 15? " << (list.search(15) ? "Sí" : "No") << endl;

    return 0;
}