#include "Sort.h"
#include <iostream>
using namespace std;

//sawp func
template <typename Temp>
void mySwap(Temp& a, Temp& b) {
    Temp temp = a;
    a = b;
    b = temp;
}

// merge sort
Node* Sort::merge(Node* left, Node* right, int sortKey) {
    if (!left) return right;
    if (!right) return left;

    bool condition;
    switch (sortKey) {
        case 1: condition = left->loanAmount <= right->loanAmount; break;
        case 2: condition = left->loanID <= right->loanID; break;
        default: condition = left->loanAmount <= right->loanAmount; break;
    }

    Node* result;
    if (condition) {
        result = left;
        if (sortKey == 1) {
        cout << "Left Value: " << left->loanAmount << " is less than Right Value " << right->loanAmount << ", switching places..." << endl;
        } else if (sortKey == 2) { 
            cout << "Left Value: " << left->loanID << " is less than Right Value " << right->loanID << ", switching places..." << endl;
        }
        result->next = merge(left->next, right, sortKey);
    } else {
        result = right;
        if (sortKey == 1) {
        cout << "Right Value: " << right->loanAmount << " is less than Left Value " << left->loanAmount << ", switching places..." << endl;
        } else if (sortKey == 2) {
            cout << "Right Value: " << right->loanID << " is less than Left Value " << left->loanID << ", switching places..." << endl;
        }
        result->next = merge(left, right->next, sortKey);
    }
    return result;
}

void Sort::split(Node* source, Node** front, Node** back) {
    if (!source || !source->next) {
        *front = source;
        *back = NULL;
        return;
    }

    Node* slow = source;
    Node* fast = source->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

Node* Sort::mergeSort(Node* head, int sortKey) {
    if (!head || !head->next) return head;

    Node* left;
    Node* right;

    split(head, &left, &right);

    left = mergeSort(left, sortKey);
    right = mergeSort(right, sortKey);

    return merge(left, right, sortKey);
}

// quick sort
Node* Sort::partition(Node* start, Node* end) {
    string pivot = end->dueDate;
    Node* partIndex = start;
    Node* current = start;

    while (current != end) {
        if (current->dueDate <= pivot) {
            mySwap(partIndex->name, current->name);
            mySwap(partIndex->age, current->age);
            mySwap(partIndex->loanID, current->loanID);
            mySwap(partIndex->loanDate, current->loanDate);
            mySwap(partIndex->dueDate, current->dueDate);
            mySwap(partIndex->loanAmount, current->loanAmount);
            mySwap(partIndex->origAmount, current->origAmount);
            partIndex = partIndex->next;
        }
        current = current->next;
    }

    mySwap(partIndex->name, end->name);
    mySwap(partIndex->age, end->age);
    mySwap(partIndex->loanID, end->loanID);
    mySwap(partIndex->loanDate, end->loanDate);
    mySwap(partIndex->dueDate, end->dueDate);
    mySwap(partIndex->loanAmount, end->loanAmount);
    mySwap(partIndex->origAmount, end->origAmount);

    return partIndex;
}

void Sort::quickSort(Node* start, Node* end) {
    if (start == end || start == NULL || end == NULL) return;

    Node* pivot = partition(start, end);

    if (pivot != start) {
        Node* temp = start;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        quickSort(start, temp);
    }

    if (pivot != end) {
        quickSort(pivot->next, end);
    }
}