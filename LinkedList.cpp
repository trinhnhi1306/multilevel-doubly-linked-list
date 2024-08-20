#include "LinkedList.h"

// Hàm đệ quy để xây dựng multilevel doubly linked list
Node* buildList(Node*& head, ifstream& file, int childCount=4) {
    string line;
    Node* current = nullptr;

    while (getline(file, line) && childCount > 0) {
        stringstream ss(line);
        string header, data;
        int count;

        // Đọc thông tin từ dòng
        getline(ss, header, ',');
        getline(ss, data, ',');
        ss >> count;

        // Tạo một node mới với header và data
        Node* newNode = new Node(header, data);

        // Liên kết node mới vào danh sách
        if (!head) {
            head = newNode;
            current = head;
        } else {
            newNode->prev = current;
            current->next = newNode;
            current = newNode;
        }

        childCount--;

        // Nếu có child, gọi đệ quy để tạo child list
        if (count > 0) {
            buildList(current->child, file, count);
        }
        
        if(childCount == 0) {
            break;
        }
    }

    return head;
}

void printMultilevelDoublyLinkedList(Node* head, int level = 0) {
    Node* curr = head;
    while (curr) {
        for (int i = 0; i < level; ++i) {
            cout << "    ";
        }

        cout << curr->header << endl;

        if (curr->data != "") {
            for (int i = 0; i < level + 1; ++i) {
                cout << "    ";
            }
            cout << curr->data << endl;
        }

        if (curr->child) {
            printMultilevelDoublyLinkedList(curr->child, level + 1);
        }

        curr = curr->next;
    }
}

void printFlattenList(Node* head) {
    Node* curr = head;
    while (curr) {
        cout << curr->header << endl;
        if (curr->data != "") {
            cout << "    " << curr->data << endl;
        }
        curr = curr->next;
    }
}

Node* flattenGetTail(Node* head) {
    Node* cur = head;
    Node* tail = nullptr;

    while (cur) {
        Node* next = cur->next;
        if (cur->child) {
            Node* child = cur->child;
            Node* childTail = flattenGetTail(cur->child);

            cur->child = nullptr;
            cur->next = child;
            child->prev = cur;
            childTail->next = next;

            if (next)
                next->prev = childTail;

            tail = childTail;
        } else {
            tail = cur;
        }

        cur = next;
    }

    return tail;
}

Node* flatten(Node* head) {
    flattenGetTail(head);
    return head;
}

void freeList(Node* head) {
    Node* current = head;
    while (current) {
        // If the current node has a child, free the child list first
        if (current->child) {
            freeList(current->child);
        }
        
        // Move to the next node
        Node* nextNode = current->next;
        
        // Delete the current node
        delete current;
        
        // Move to the next node in the list
        current = nextNode;
    }
}

void readFileToList(Node*& head, string fileName) {
    ifstream file(fileName);

    if (!file) {
        cerr << "Can not open file" << endl;
        return;
    }

    buildList(head, file);

    file.close();
}

void badFunction(Node* head) {
    Node* leakedNode = (Node*)malloc(sizeof(Node));
    leakedNode->header = "Test header";
    leakedNode->data = "Test data";
    leakedNode->next = NULL;
    leakedNode->prev = NULL;
    leakedNode->child = NULL;

    cout << leakedNode->header;

    freeList(head->child);

    head->child->header = "Crash header";
}