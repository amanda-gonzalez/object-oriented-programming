// Amanda Gonzalez
#include "polynomial.h"
#include <iostream>
#include <vector>

using namespace std;

// default constructor
Polynomial::Polynomial() : degree(0) { head = new Node; }

// constructor for Polynomial given a vector of values
Polynomial::Polynomial(const vector<int>& coefficients) : head(nullptr), degree(coefficients.size() - 1) {
    // loops through vector backwards and adds the value as a new node to front of linked list
    for (size_t i = coefficients.size(); i > 0; --i) {
        head = new Node(coefficients[i-1], head);
	}
    // cleans list to ensure there are no unnecessary leading 0's
    cleanup(head);
}

// copy constructor
// copies the objects from rhs to head list
Polynomial::Polynomial(const Polynomial& rhs) : head(nullptr), degree(rhs.degree) {
    Node* rhsPtr = rhs.head;
    if (rhsPtr != nullptr) {
        // creates head node
        head = new Node(rhsPtr->data);
        Node* newList = head;
        // adds to end of list each data object
        while (rhsPtr->next != nullptr) {
            rhsPtr = rhsPtr->next;
            newList->next = new Node(rhsPtr->data);
            newList = newList->next;
        }
    }
}

// destructor
// moves through linked list, deleting each node until it reaches the end
Polynomial::~Polynomial() {
    // when head is nullptr, it is at the end of the list
    while (head != nullptr) {
        Node* toRemove = head;
        head = head->next;
        delete toRemove;
    }
}

// assignment operator
// sets linked list to another linked list
Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    // checks for self-assignment
    if (this != &rhs) {
        // frees up resources
        while (head != nullptr) {
            Node* toRemove = head;
            head = head->next;
            delete toRemove;
        }
        degree = rhs.degree;
        // copies over data
        Node* rhsPtr = rhs.head;
        if (rhsPtr != nullptr) {
            // creates head node
            head = new Node(rhsPtr->data);
            Node* newList = head;
            // adds to end of list each data object
            while (rhsPtr->next != nullptr) {
                rhsPtr = rhsPtr->next;
                newList->next = new Node(rhsPtr->data);
                newList = newList->next;
            }
        }
    }
    return *this;
}

// += operator
// adds a polynomial to self
// rhs polynomial param is constant reference because it is not modified
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    // tempNode to hold coefficients of polynomial if it is
    // larger than the other
    Node* tempNode = nullptr;
    Node* lhsPtr = head;
    Node* rhsPtr = rhs.head;
    // if lhs degree is greater than rhs, lhsPtr moves to term
    // of greates degree that both rhs and lhs have
    if (this->degree > rhs.degree) {
        for (size_t i = 0; i < (degree - rhs.degree); ++i) {
            lhsPtr = lhsPtr->next;
        }
    }
    // if rhs degree greater than lhs, rhsPtr moves to term
    // of greates degree that both rhs and lhs have
    else if (rhs.degree > this->degree) {
        for (size_t i = 0; i < (rhs.degree-degree); ++i) {
            // adds greater degree nodes to tempNode list
            tempNode = new Node(rhsPtr->data, tempNode);
            rhsPtr = rhsPtr->next;
        }
    }
    // lhs adds node data from rhs until it reaches the end
    while (lhsPtr != nullptr) {
        lhsPtr->data += rhsPtr->data;
        lhsPtr = lhsPtr->next;
        rhsPtr = rhsPtr->next;
    }
    // pushes to front the larger degree nodes from the rhs
    while (tempNode != nullptr) {
        head = new Node(tempNode->data, head);
        tempNode = tempNode->next;
        // increases degree of self
        degree++;
    }
    // check to make sure there are no unnecesary leading 0's
    cleanup(head);
    return *this;
}

// evaluate method
// takes in an int val to be substiuted as x in polynomial equation
int Polynomial::evaluate(int val) {
    int res = 0;
    int power = degree;
    // performs power and summation operations on polynomial terms
    while (head != nullptr) {
        int multiplier = 1;
        // multipler is set equal to val to the power of each degree
        for (int i = 0; i < power; ++i) {
            multiplier *= val;
        }
        res += head->data * multiplier;
        head = head->next;
        // decrement power by 1 as loop goes through the polynomial values
        power--;
    }
    return res;
}

// cleanup method
// deletes any leading 0's
// reference to Node* to directly modify it
void Polynomial::cleanup(Node*& node) {
    // checks that list is not empty
    if (node != nullptr) {
        // deletes leading 0's
        while (node->data == 0) {
            Node* toRemove = node;
            node = node->next;
            delete toRemove;
            // decrements degree to account for deleted objects
            degree--;
        }
    }
}

// output operator
// displays polynomial as a function of variables and powers
ostream& operator<<(ostream& os, Polynomial rhs) {
    // loops through polynomial starting from highest degree
    for (size_t i = rhs.degree; i > 0; --i) {
        // power is greater than 1
        if (i > 1) {
            // if coefficient is 1, it is not displayed
            // only variable x to the power output
            if (rhs.head->data == 1) {
                os << "x^" << i << " + ";
            }
            // if coefficient is not 1 or 0, it is diplayed with
            // varible x to the power of the degree
            else if (rhs.head->data != 0) {
                os << rhs.head->data << "x^" << i << " + ";
            }
        }
        // if power is 1, it is not ouput as degree
        else {
            // if coefficient is 1, it is not displayed
            // only varible x 
            if (rhs.head->data == 1) {
                os << "x" << " + ";
            }
            // if coefficient is not 1 or 0, it is displayed with
            // varible x
            else if (rhs.head->data != 0) {
                os << rhs.head->data << "x" << " + ";
            }
        }
        rhs.head = rhs.head->next;
    }
    // ouputs constant term
    os << rhs.head->data;
    return os;
}

// == operator
// true or false if two polynomial instances are the same
// both polynomial objects are constant because they are not modified
bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    Node* lhsHead = lhs.head;
    Node* rhsHead = rhs.head;
    // false if lhs and rhs do not have the same highest power
    if (lhs.degree != rhs.degree) {
        return false;
    }
    // compares each object in lhs to rhs
    for (size_t i = 0; i < lhs.degree; ++i) {
        if (lhsHead->data != rhsHead->data) {
            return false;
        }
        lhsHead = lhsHead->next;
        rhsHead = rhsHead->next;
    }
    return true;
}

// + operator
// returns the sum of two polynomials
// both polynomial objects are constant because they are not modified
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial res = lhs;
    res += rhs;
    return res;
}

// != operator
// returns the opposite of ==
// both polynomial objects are constant because they are not modified
bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs == rhs);
}


