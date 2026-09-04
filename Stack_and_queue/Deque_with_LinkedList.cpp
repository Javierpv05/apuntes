#include <bits/stdc++.h>
using namespace std;

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class Deque {
private:
    DNode* head;
    DNode* tail;
    int sz;

public:
    Deque() : head(nullptr), tail(nullptr), sz(0) {}
    ~Deque() { while (!empty()) pop_front(); }

    void push_front(int val) {
        DNode* newNode = new DNode(val);
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        sz++;
    }

    void push_back(int val) {
        DNode* newNode = new DNode(val);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        sz++;
    }

    void pop_front() {
        if (empty()) return;
        DNode* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        sz--;
    }

    void pop_back() {
        if (empty()) return;
        DNode* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        sz--;
    }

    int front() const {
        if (empty()) throw runtime_error("Deque vacío");
        return head->data;
    }

    int back() const {
        if (empty()) throw runtime_error("Deque vacío");
        return tail->data;
    }

    bool empty() const { return head == nullptr; }
    int size() const { return sz; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Deque dq;

    dq.push_back(10);
    dq.push_back(20);
    dq.push_front(5);
    dq.push_front(1);

    cout << "Tamaño: " << dq.size() << "\n";
    cout << "Front: " << dq.front() << "\n";
    cout << "Back: " << dq.back() << "\n";

    dq.pop_front();
    cout << "Front después de pop_front: " << dq.front() << "\n";

    dq.pop_back();
    cout << "Back después de pop_back: " << dq.back() << "\n";

    dq.pop_front();
    dq.pop_back();
    cout << "Tamaño: " << dq.size() << "\n";
    cout << "¿Vacía? " << (dq.empty() ? "Sí" : "No") << "\n";

    try {
        cout << dq.front() << "\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }

    return 0;
}