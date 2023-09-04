#include "polynomial.h"
#include <iostream>
#include <vector>

using namespace std;

Polynomial::Polynomial() : degree(0) { head = new Node; }

Polynomial::Polynomial(const vector<int>& coefficients) : degree(coefficients.size() - 1) {
    for (size_t i = 0; i < coefficients.size(); ++i) {
        if (head != nullptr) {
            head->next = new Node(coefficients[i]);
            head = head->next;
        }
        else {
            head = new Node(coefficients[i]);
        }
    }
}

Polynomial::Polynomial(const Polynomial& rhs) : degree(rhs.degree) {
    if (head != nullptr) {
        Node* newHead = nullptr;
        newHead = new Node(rhs.head->data, newHead);
        head = head->next;
        while (head != nullptr) {
            newHead->next = new Node(head->data);
            head = head->next;
            newHead = newHead->next;
        }
    }
}

Polynomial::~Polynomial() {
    while (head != nullptr) {
        Node* toRemove = head;
        head = head->next;
        delete toRemove;
    }
}

Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    if (this != &rhs) {
        while (head != nullptr) {
            Node* toRemove = head;
            head = head->next;
            delete toRemove;
        }
        degree = rhs.degree;
        if (head != nullptr) {
            Node* newHead = nullptr;
            newHead = new Node(rhs.head->data, newHead);
            while (head != nullptr) {
                head = head->next;
                newHead->next = new Node(head->data);
                newHead = newHead->next;
            }
        }
    }
    return *this;
}

ostream& operator<<(ostream& os, Polynomial rhs) {
    for (size_t i = rhs.degree; i > 0; --i) {
        if (i > 1) {
            os << rhs.head->data << "x^" << i << endl;
        }
        else {
            os << rhs.head->data << "x" << endl;
        }
        os << " + ";
        rhs.head = rhs.head->next;
    }
    os << rhs.head;
    return os;
}



