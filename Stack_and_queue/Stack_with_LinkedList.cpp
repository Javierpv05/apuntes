#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Stack {
private:
    Node* head;
    int sz;

public:
    Stack() : head(nullptr), sz(0) {}
    ~Stack() { while (!empty()) pop(); }

    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        sz++;
    }

    void pop() {
        if (empty()) return;
        Node* temp = head;
        head = head->next;
        delete temp;
        sz--;
    }

    int top() const {
        if (empty()) throw runtime_error("Stack vacío");
        return head->data;
    }

    bool empty() const { return head == nullptr; }
    int size() const { return sz; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Stack pila;

    pila.push(10);
    pila.push(20);
    pila.push(30);
    pila.push(40);

    cout << "Tamaño: " << pila.size() << "\n";
    cout << "Top: " << pila.top() << "\n";

    pila.pop();
    cout << "Top después de pop: " << pila.top() << "\n";

    pila.pop();
    pila.pop();
    cout << "Tamaño: " << pila.size() << "\n";
    cout << "Top: " << pila.top() << "\n";

    pila.pop();
    cout << "¿Vacía? " << (pila.empty() ? "Sí" : "No") << "\n";

    try {
        cout << pila.top() << "\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }

    return 0;
}