// Amanda Gonzalez
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>

// Node struct
struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}

    int data;
    Node* next;
};

// Polynomial class
class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, Polynomial rhs);

    friend bool operator==(const Polynomial& rhs, const Polynomial& lhs);
public:
    Polynomial();

    Polynomial(const std::vector<int>& coefficients);

    Polynomial(const Polynomial& rhs);

    ~Polynomial();

    Polynomial& operator=(const Polynomial& rhs);

    Polynomial& operator+=(const Polynomial& rhs);

    int evaluate(int val);

    void cleanup(Node*& node);

private:
    Node* head;
    size_t degree;
};

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

bool operator!=(const Polynomial& lhs, const Polynomial& rhs);

#endif // !POLYNOMIAL_H
