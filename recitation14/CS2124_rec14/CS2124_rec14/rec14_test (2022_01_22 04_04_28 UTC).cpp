// Amanda Gonzalez

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// 9. Function to print list with iterator
void iterPrint(const list<int>& lst) {
    // list<int>::iterator iter;
    list<int>::const_iterator iter;
    for (iter = lst.begin(); iter != lst.end(); ++iter) {
        cout << *iter << ' ';
    }
}

// 10. Function to print list for ranged for
void forPrint(const list<int>& lst) {
    for (int val : lst) {
        cout << val << ' ';
    }
}

// 11. Function to print every other item in list
void printEveryOther(const list<int>& lst) {
    for (auto iter = lst.begin(); iter != lst.end(); ++iter) {
        cout << *iter << ' ';
        ++iter;
    }
}

// 12. Function to find item in list
list<int>::const_iterator findItem(const list<int>& lst, int item) {
    list<int>::const_iterator iter;
    for (iter = lst.begin(); iter != lst.end(); ++iter) {
        if (*iter == item) {
            return iter;
        }
    }
    return lst.end();
}

// 13. Fucntion to find item in list using auto
auto findItem2(const list<int>& lst, int item) {
    for (auto iter = lst.begin(); iter != lst.end(); ++iter) {
        if (*iter == item) {
            return iter;
        }
    }
    return lst.end();
}

// 15. Bool function to determine if int is even
bool isEven(int n) {
    return n % 2 == 0;
}

// 16. Class for functor call
class FunctorIsEven {
public:
    bool operator()(int n) const {
        return n % 2 == 0;
    }
};

// 19. ourFind function 
list<int>::iterator ourFind(list<int>::iterator begin, list<int>::iterator end, int target) {
    cout << "using ourFind() function... ";
    for (list<int>::iterator i = begin; i != end; ++i) {
        if (*i == target) {
            return i;
        }
    }
    return end;
}

// 20. Templated ourFind function
template<typename T, typename U>
T ourFind(T begin, T end, U target) {
    cout << "using TEMPLATED ourFind() function... ";
    for (T i = begin; i != end; ++i) {
        if (*i == target) {
            return i;
        }
    }
    return end;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vect = {1, 5, 3, 6, 2, 4};
    for (int val : vect) {
        cout << val << ' ';
    }
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> lst(vect.begin(), vect.end());
    for (int val : lst) {
        cout << val << ' ';
    }
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vect.begin(), vect.end());
    for (int val : vect) {
        cout << val << ' ';
    }
    cout << endl;
    for (int val : lst) {
        cout << val << ' ';
    }
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < vect.size(); i+=2) {
        cout << vect[i] << ' ';
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    //for (size_t i = 0; i < lst1.size(); i+=2) {
    //    cout << lst1[i] << ' ';
    //}
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    vector<int>::iterator vIter;
    for (vIter = vect.begin(); vIter != vect.end(); vIter+=2) {
        cout << *vIter << ' ';
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    list<int>::iterator lIter;
    for (lIter = lst.begin(); lIter != lst.end(); ++lIter) {
        cout << *lIter << ' ';
        ++lIter;
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    lst.sort();
    for (int val : lst) {
        cout << val << ' ';
    }
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    iterPrint(lst);
    cout << "\n=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    forPrint(lst);
    cout << "\n=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printEveryOther(lst);
    cout << "\n=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    findItem(lst, 2);
    findItem(lst, 99);
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    findItem2(lst, 2);
    findItem2(lst, 99);
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    list<int>::iterator findIter = find(lst.begin(), lst.end(), 2);
    cout << *findIter;
    auto findIter2 = find(lst.begin(), lst.end(), 99);
    // error because not in list
    // cout << *findIter2;
    cout << "\n=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    vector<int>::iterator findIfIter = find_if(vect.begin(), vect.end(), isEven);
    cout << *findIfIter << endl;
    auto findIfIter2 = find_if(lst.begin(), lst.end(), isEven);
    cout << *findIfIter2 << endl;
    // trying with vector of strings
        // doesn't work because isEven only takes in int
    //vector<string> vectStrings = { "abc", "cat", "dog" };
    //auto findIfIter3 = find_if(vectStrings.begin(), vectStrings.end(), isEven);
    //cout << *findIfIter3;
    cout << "\n=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    auto functorIter = find_if(vect.begin(), vect.end(), FunctorIsEven());
    cout << *functorIter << endl;
    list<int>::iterator functorIter2 = find_if(lst.begin(), lst.end(), FunctorIsEven());
    cout << *functorIter2;
    cout << "\n=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    [](int a, int b) { cout << a + b << endl; } (4, 5);
    [](vector<int> vect) { for (int val : vect) { if (val % 2 == 0) { cout << val << endl; break; } }}(vect);
    auto functorIter = find_if(vect.begin(), vect.end(), [](int val) {return val % 2 == 0;});
    int res = [](auto lst) -> int {for (int val : lst) { if (val % 2 == 0) { return val; } }}(lst);
    cout << res;
    cout << "\n=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* arr = new int[6];
    copy(vect.begin(), vect.end(), arr);
    for (size_t i = 0; i < 6; ++i) {
        cout << arr[i] << ' ';
    }
    cout << endl;
    auto arrIter = find(arr, &arr[vect.size()], 2);
    cout << *arrIter << endl;
    int* arrIter2 = find_if(arr, &arr[vect.size()], FunctorIsEven());
    cout << *arrIter2;
    delete[]arr;
    cout << "\n=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    list<int>::iterator ourFindIter = ourFind(lst.begin(), lst.end(), 4);
    cout << *ourFindIter;
    cout << "\n=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    auto ourFindIter2 = ourFind(lst.begin(), lst.end(), 4);
    cout << *ourFindIter2;
    cout << "\n=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    string word;
    vector<string> words;
    ifstream ifs("pooh-nopunc.txt");
    while (ifs >> word) {
        if (words.end() == find(words.begin(), words.end(), word)) {
            words.push_back(word);
        }
    }
    ifs.close();
    cout << words.size();
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    ifs.open("pooh-nopunc.txt");
    set<string> wordsSet;
    while (ifs >> word) {
        wordsSet.insert(word);
    }
    cout << wordsSet.size();
    ifs.close();
    cout << "\n=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> wordMap;
    int position = 1;
    ifs.open("pooh-nopunc.txt");
    while (ifs >> word) {
        wordMap[word].push_back(position);
        ++position;
    }
    for (auto& elem : wordMap) {
        cout << elem.first << ": ";
        for (int pos : elem.second) {
            cout << pos << ' ';
        }
        cout << endl;
    }
    ifs.close();
    cout << "\n=======\n";
}
