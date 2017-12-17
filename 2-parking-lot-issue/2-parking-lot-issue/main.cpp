#include <iostream>
using namespace std;

class Car {
public:
	int license;
	int time;
};

class Stack {
public:
	Car *base;
	Car *top;
	int size;

	Stack(int size);
	void Push(Car car);
	Car Pop();
	void Show();
	bool Empty();
	bool Full();
	int  Length();
	Car  Elem(Car car);
	Car  Top();
};

Stack::Stack(int length) {
	size = length;
	base = new Car[size];
	top = base;
}

void Stack::Push(Car car) {
	*top++ = car;
}

Car Stack::Pop() {
	Car car = *--top;
	return car;
}

void Stack::Show() {
	for (int i = 0; i < Length(); i++) {
		cout << (base + i)->license << endl;
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

bool Stack::Full() {
	if (Length() == size) {
		return true;
	}
	return false;
}

Car Stack::Elem(Car car) {
	Stack tempStack(size);
	while (Top().license != car.license) {
		tempStack.Push(Pop());
	}
	Car currentCar = Pop();
	while (!tempStack.Empty()) {
		Push(tempStack.Pop());
	}
	return currentCar;
}

Car Stack::Top() {
	return *(top - 1);
}

class QueueElem {
public:
	Car data;
	QueueElem *next;
};

class Queue {
public:
	QueueElem *front;
	QueueElem *rear;

	Queue();
	void Insert(Car car);
	int  Length();
	Car  Remove();
	bool Empty();
};

Queue::Queue() {
	front = new QueueElem();
	front->next = front;
	rear = front;
	rear->next = rear;
}

void Queue::Insert(Car car) {
	QueueElem *elem = new QueueElem();
	elem->data = car;
	elem->next = NULL;
	rear->next = elem;
	rear = elem;
}

int Queue::Length() {
	QueueElem *p = front;
	int i;
	for (i = 0; p != rear; i++, p = p->next);
	return i;
}

Car Queue::Remove() {
	QueueElem *elem = front->next;
	Car car = elem->data;
	front->next = elem->next;
	delete elem;
	return car;
}

bool Queue::Empty() {
	if (front == rear) {
		return true;
	}
	return false;
}

int main() {

	Queue pavement;

	/* Parking Lot */
	int number;
	cout << "The Max Num:";
	cin >> number;
	Stack parkingLot(number);

	/* Input Info Of Car */
	char operat;
	int  i;

	cout << "$10 Per Hour" << endl;
	cout << "Input Car Info, Arrive, Departure Or End" << endl;

	bool end = false;
	for (i = 0; !end; i++) {

		Car temp;

		cin >> operat;
		cin >> temp.license;

		switch (operat) {
		case 'A': {
			cin >> temp.time;
			if (!parkingLot.Full()) {
				parkingLot.Push(temp);
				cout << "Location In ParkingLot:" << parkingLot.Length() << endl;
			}
			else {
				pavement.Insert(temp);
				cout << "Location In Pavement:" << pavement.Length() << endl;
			}
			break;
		}
		case 'D': {
			int time;
			cin >> time;
			temp.time = time - parkingLot.Elem(temp).time;
			cout << temp.license << " Leave, The Time Is: " << temp.time << " Money Is: $" << temp.time * 10 << endl;

			if (!pavement.Empty()) {
				Car tempCar = pavement.Remove();
				tempCar.time = time;
				parkingLot.Push(tempCar);
			}

			break;
		}
		case 'E': {
			end = true;
			break;
		}
		}
	}

	return 0;
}