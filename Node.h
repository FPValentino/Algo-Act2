#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;

class Node {
public:
    string name;
    int age;
    int loanID;
    string loanDate;
    string dueDate;
    int loanAmount;
    int origAmount;
    Node* next;

    Node(string name, int age, int loanID, string loanDate, string dueDate, int loanAmount, int origAmount) {
        this->name = name;
        this->age = age;
        this->loanID = loanID;
        this->loanDate = loanDate;
        this->dueDate = dueDate;
        this->loanAmount = loanAmount;
        this->origAmount = origAmount;
        this->next = NULL;
    }
};

#endif
