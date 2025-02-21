#ifndef SORT_H
#define SORT_H

#include "Node.h"

class Sort {
public:
    // Merge Sort
    static Node* mergeSort(Node* head, int sortKey);

    // Quick Sort
    static void quickSort(Node* start, Node* end);

private:
    static Node* merge(Node* left, Node* right, int sortKey);
    static void split(Node* source, Node** front, Node** back);
    static Node* partition(Node* start, Node* end);
};

#endif
