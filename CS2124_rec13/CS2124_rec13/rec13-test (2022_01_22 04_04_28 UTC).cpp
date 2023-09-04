// Amanda Gonzalez
// Doubly linked list

#include <cstdlib>
#include <iostream>
using namespace std;




class List {
    struct Node {
        Node(int data = 0, Node* next = nullptr, Node* prev = nullptr) : data(data),
            next(next), prev(prev) {}

        int data;
        Node* next;
        Node* prev;
    };

    friend ostream& operator<<(ostream& os, const List& rhs) {
        for (Node* p = rhs.header->next; p != rhs.trailer; p = p->next) {
            cout << p->data << ' ';
        }
        return os;
    }

public:
    class iterator {
        friend class List;

        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.ptr == rhs.ptr;
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return !(lhs == rhs);
        }

    public:

        iterator(Node* node) : ptr(node){}

        iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        iterator& operator--() {
            ptr = ptr->prev;
            return *this;
        }

        int& operator*() { 
            return ptr->data;
        }

    private:
        Node* ptr;
    };

    List() : header(nullptr), trailer(nullptr), lst_size(0) {
        header = new Node;
        trailer = new Node;
        header->next = trailer;
        trailer->prev = header;
    }

    void push_back(int data) {
        Node* lastNode = trailer->prev;
        Node* newNode = new Node(data, trailer, lastNode);
        lastNode->next = newNode;
        trailer->prev = newNode;
        lst_size++;
    }

    void pop_back() {
        if (lst_size > 0) {
            Node* lastNode = trailer->prev->prev;
            delete trailer->prev;
            lastNode->next = trailer;
            trailer->prev = lastNode;
            lst_size--;
        }
    }

    int& front() {
        return header->next->data;
    }

    int front() const {
        return header->next->data;
    }

    int& back() {
        return trailer->prev->data;
    }

    int back() const {
        return trailer->prev->data;
    }

    size_t size() const {
        return lst_size;
    }

    void push_front(int data) {
        Node* firstNode = header->next;
        Node* newNode = new Node(data, firstNode, header);
        header->next = newNode;
        firstNode->prev = newNode;
        lst_size++;
    }

    void pop_front() {
        if (lst_size > 0) {
            Node* firstNode = header->next->next;
            delete header->next;
            header->next = firstNode;
            firstNode->prev = header;
            lst_size--;
        }
    }

    void clear() {
        while (lst_size != 0) {
            pop_front();
        }
    }

    int& operator[](size_t idx) {
        Node* nodePtr = header->next;
        for (size_t i = 0; i < idx; ++i) {
            nodePtr = nodePtr->next;
        }
        return nodePtr->data;
    }

    int operator[](size_t idx) const {
        Node* nodePtr = header->next;
        for (size_t i = 0; i < idx; ++i) {
            nodePtr = nodePtr->next;
        }
        return nodePtr->data;
    }

    iterator begin() {
        return iterator(header->next);
    }

    iterator end() {
        return iterator(trailer);
    }

    iterator insert(const iterator& iter, int data) {
        Node* prevNode = iter.ptr->prev;
        Node* newNode = new Node(data, iter.ptr, prevNode);
        prevNode->next = newNode;
        iter.ptr->prev = newNode;
        lst_size++;
        return iterator(newNode);
    }

    iterator erase(iterator iter) {
        if (lst_size == 0) {
            return iterator(trailer);
        }
        Node* prevNode = iter.ptr->prev;
        Node* nextNode = iter.ptr->next;
        delete iter.ptr;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        lst_size--;
        return iterator(nextNode);
    }

private:
    Node* header;
    Node* trailer;
    size_t lst_size;
};

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}    

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";
    
    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";
    
    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";
    
    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);
    
    
    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
    
    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";
    
    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";
    /*
    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
    */
}
