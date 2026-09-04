#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Queue {
private:
    Node* frontNode;
    Node* backNode;
    int sz;

public:
    Queue() : frontNode(nullptr), backNode(nullptr), sz(0) {}
    ~Queue() { while (!empty()) pop(); }

    void push(int val) {
        Node* newNode = new Node(val);
        if (empty()) {
            frontNode = backNode = newNode;
        } else {
            backNode->next = newNode;
            backNode = newNode;
        }
        sz++;
    }

    void pop() {
        if (empty()) return;
        Node* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) backNode = nullptr;
        delete temp;
        sz--;
    }

    int front() const {
        if (empty()) throw runtime_error("Cola vacía");
        return frontNode->data;
    }

    int back() const {
        if (empty()) throw runtime_error("Cola vacía");
        return backNode->data;
    }

    bool empty() const { return frontNode == nullptr; }
    int size() const { return sz; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Queue cola;

    cola.push(10);
    cola.push(20);
    cola.push(30);
    cola.push(40);

    cout << "Tamaño: " << cola.size() << "\n";
    cout << "Front: " << cola.front() << "\n";
    cout << "Back: " << cola.back() << "\n";

    cola.pop();
    cout << "Front después de pop: " << cola.front() << "\n";

    cola.pop();
    cola.pop();
    cout << "Tamaño: " << cola.size() << "\n";
    cout << "Front: " << cola.front() << "\n";

    cola.pop();
    cout << "¿Vacía? " << (cola.empty() ? "Sí" : "No") << "\n";

    try {
        cout << cola.front() << "\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }

    return 0;
}