#include <iostream>
using namespace std;

class Car {
public:
    int license;
    Car *next;
};

class Stack {
public:
    Car *base;
    Car *top;

    static int stack_size;

    Stack();
    void Push(Car car);
    void Pop(Car &car);
    void Show();
    bool Empty();
    int  Length();
};

int Stack::stack_size = 10;

Stack::Stack() {
    base = (Car *) malloc (stack_size * sizeof(Car));
    top  = base;
}

void Stack::Push(Car car) {
    * top ++ = car;
}

void Stack::Pop(Car &car) {
    car = * -- top;
}

void Stack::Show() {
    for (int i = 0; i < Length(); i ++) {
        cout << ( base + i )->license << endl;
    }
}

int Stack::Length() {
    return top - base;
}

bool Stack::Empty() {
    if (!Length()) {
        return true;
    }
    return false;
}

class Queue {
public:
    Car *front;
    Car *rear;

    Queue();
    void Insert(Car &car);
};

Queue::Queue() {
    front = rear = (Car *) malloc (sizeof(Car));
    front->next  = NULL;
}

void Queue::Insert(Car &car) {
    rear->next = &car;
    rear = &car;
}

int main() {

    Stack parkingLot;  // 停车场
    Queue pavement;    // 便道

    return 0;
}