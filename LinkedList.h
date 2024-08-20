#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Node {
    public:
        string header;
        string data;
        Node* prev;
        Node* next;
        Node* child;

        Node(const string& h, const string& d) : header(h), data(d), prev(nullptr), next(nullptr), child(nullptr) {}
};

// Function declarations
Node* buildList(Node*& head, ifstream& file, int childCount);
void printMultilevelDoublyLinkedList(Node* head, int level);
void printFlattenList(Node* head);
Node* flattenGetTail(Node* head);
Node* flatten(Node* head);
void freeList(Node* head);
void readFileToList(Node*& head, string fileName);
void badFunction(Node* head);

#endif // LINKEDLIST_H