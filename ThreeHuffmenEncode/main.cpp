#include <iostream>
using namespace std;

class Character {
public:
    char value;
    int  weight;
    Character *parent;
    Character *lChild;
    Character *rChild;
};

class Huffmen {
public:
    int size;
    Character *character;

    Huffmen (int number);
    void Insert();
    void Generate();
};

Huffmen::Huffmen(int number) {
    size = number;
    character = new Character[size];
}

void Huffmen::Insert() {
    for (int i = 0; i < size; i ++) {
        cout << "Input The Character:";
        cin  >> character[i].value;
        cout << "Input The Weight:";
        cin  >> character[i].weight;
    }
}

void Huffmen::Generate() {
    
}

int main() {

    char operate;

    cout << "I E D P T : ";
    cin  >> operate;

    switch(operate) {
        case 'I': {
            int number;
            cout << "Input The Numbers Of Characters: ";
            cin  >> number;
            Huffmen huffmen(number);
            huffmen.Insert();
            break;
        }
        case 'E': {
            break;
        }
        case 'D': {
            break;
        }
        case 'P': {
            break;
        }
        case 'T': {
            break;
        }
    }

    return 0;
}