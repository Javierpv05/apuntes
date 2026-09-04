#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;
    int size;

public:
    // Constructor y destructor
    SinglyLinkedList() : head(nullptr), size(0) {}
    ~SinglyLinkedList() { clear(); }

    // Insercion
    // al inicio
    void insertFront(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        size++;
    }
    // al final 
    void insertBack(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        size++;
    }
    // en una posicion 
    void insertAt(int val, int pos) {
        if (pos < 0 || pos > size) throw out_of_range("Posición inválida");
        if (pos == 0) { insertFront(val); return; }
        Node* newNode = new Node(val);
        Node* temp = head;
        for (int i = 0; i < pos - 1; ++i) temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    }

    // Eliminacion
    // el de en frente
    void removeFront() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }
    //el final 
    void removeBack() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node* temp = head;
            while (temp->next->next) temp = temp->next;
            delete temp->next;
            temp->next = nullptr;
        }
        size--;
    }
    //el de una posicion 
    void removeAt(int pos) {
        if (pos < 0 || pos >= size) throw out_of_range("Posición inválida");
        if (pos == 0) { removeFront(); return; }
        Node* temp = head;
        for (int i = 0; i < pos - 1; ++i) temp = temp->next;
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        size--;
    }
    //elimiar por valor 
    void removeByValue(int val) {
        if (!head) return;
        if (head->data == val) { removeFront(); return; }
        Node* temp = head;
        while (temp->next && temp->next->data != val) temp = temp->next;
        if (temp->next) {
            Node* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
            size--;
        }
    }

    // Busqueda y utilidades
    // buscar 
    bool search(int val) const {
        Node* temp = head;
        while (temp) {
            if (temp->data == val) return true;
            temp = temp->next;
        }
        return false;
    }
    // tamanno de la lista 
    int getSize() const { return size; }
    // verificar si la lista esta vacia 
    bool isEmpty() const { return head == nullptr; }
    // imprimir la lista 
    void print() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
    // invertir el orden 
    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }
    // eliminar toda la lista 
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }
    // elemento en la posicion
    int getAt(int pos) const {
        if (pos < 0 || pos >= size) throw out_of_range("Posicion invalida");
        Node* temp = head;
        for (int i = 0; i < pos; ++i) temp = temp->next;
        return temp->data;
    }
    // agregar por posicion 
    void updateAt(int pos, int newVal) {
        if (pos < 0 || pos >= size) throw out_of_range("Posicion invalida");
        Node* temp = head;
        for (int i = 0; i < pos; ++i) temp = temp->next;
        temp->data = newVal;
    }
};

// --- Main para pruebas ---
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    SinglyLinkedList list;
    list.insertBack(1);
    list.insertBack(20);
    list.insertBack(30);
    list.insertFront(5);
    list.insertAt(15, 2);

    cout << "Lista: ";
    list.print(); // 5 15 20 30

    list.reverse();
    cout << "Invertida: ";
    list.print(); // 30 20 15 10 5

    cout << "Tamaño: " << list.getSize() << "\n";
    cout << "Elemento en índice 2: " << list.getAt(2) << "\n";

    return 0;
}