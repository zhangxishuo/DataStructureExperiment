#include <iostream>
using namespace std;

class Node {
public:
	int num;
	int password;
	Node *next;
};

class CircularList {
private:
	Node *headPointer;
public:
	CircularList();
	void insert(int num, int password);
	void show();
	int remove(int map, int &num);
	bool null();
};

CircularList::CircularList() {
	headPointer = (Node *)malloc(sizeof(Node));
	headPointer->next = NULL;
}

void CircularList::insert(int num, int password) {
	Node *node, *p;
	node = (Node *)malloc(sizeof(Node));
	node->password = password;
	node->num = num;

	if (headPointer->next == NULL) {
		headPointer->next = node;
		node->next = node;
	}
	else {
		for (p = headPointer->next; p->next != headPointer->next; p = p->next);
		p->next = node;
		node->next = headPointer->next;
		headPointer->next = node;
	}
}

void CircularList::show() {
	Node *p = headPointer->next;
	for (; p->next != headPointer->next; p = p->next) {
		cout << p->num << " " << p->password << endl;
	}
	cout << p->num << " " << p->password << endl;
}

int CircularList::remove(int map, int &num) {
	Node *p = headPointer->next;
	Node *q;
	int password;
	if (null()) {
		return -1;
	}
	if (map == 1) {
		if (p->next == p) {
			headPointer->next = NULL;
			free(p);
		}
		else {
			for (; p->next != headPointer->next; p = p->next);
			q = headPointer->next;
			headPointer->next = headPointer->next->next;
			p->next = headPointer->next;
			num = q->num;
			password = q->password;
			free(q);
		}
	}
	else {
		for (int i = 0; i < map - 2; i++) {
			p = p->next;
		}
		Node *delNode = p->next;
		password = delNode->password;
		num = delNode->num;
		p->next = delNode->next;
		headPointer->next = delNode->next;
		if (delNode == delNode->next) {
			headPointer->next = NULL;
		}
		free(delNode);
	}

	return password;
}

bool CircularList::null() {
	if (headPointer->next == NULL) {
		return true;
	}

	return false;
}

int main() {
	CircularList circularList;

	int num, i;
	cout << "Numbers:";
	cin >> num;
	int *password = new int[num];

	// for (i = 0; i < num; i ++) {
	//     cout << "the " << i + 1 << " password:";
	//     cin  >> password[i];
	// }

	for (i = 0; i < num; i++) {
		password[i] = (rand() % 30) + 1;
	}

	for (i = num - 1; i >= 0; i--) {
		circularList.insert(i + 1, password[i]);
	}

	circularList.show();

	int map, index;
	cout << "the start map:";
	cin >> map;

	while (!circularList.null()) {
		map = circularList.remove(map, index);
		cout << index << endl;
	}

	return 0;
}