#include <iostream>
using namespace std;

class Node {
public:
    int password;
    Node *next;
};

class CircularList {
private:
    Node *headPointer;
public:
    CircularList();
    void insert(int password);
    void show();
};

CircularList::CircularList() {
    headPointer = (Node *) malloc (sizeof(Node));
    headPointer->next = NULL;
}

void CircularList::insert(int password) {
    Node *node, *p;
    node = (Node *) malloc (sizeof(Node));
    node->password = password;

    if (headPointer->next == NULL) {
        headPointer->next = node;
        node->next = node;
    } else {
        for (p = headPointer->next; p->next != headPointer->next; p = p->next);
        p->next = node;
        node->next = headPointer->next;
        headPointer->next = node;
    }
}

void CircularList::show() {
    Node *p = headPointer->next;
    for (; p->next != headPointer->next; p = p->next) {
        cout << p->password;
    }
    cout << p->password;
}

int main() {
    CircularList circularList;

    int num, i;
    cout << "Numbers:" << endl;
    cin  >> num;
    int *password = new int[num];

    for (i = 0; i < num; i ++) {
        cout << "the " << i + 1 << " password" << endl;
        cin  >> password[i];
    }

    for (i = num - 1; i >= 0; i --) {
        circularList.insert(password[i]);
    }

    circularList.show();

    return 0;
}