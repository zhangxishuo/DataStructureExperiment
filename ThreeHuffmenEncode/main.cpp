#include <iostream>
using namespace std;

const int INIT = 65535;

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
    void Init();
    void Generate();
    void Print();
};

Huffmen::Huffmen(int number) {
    size = number;
    character = new Character[size * 2 - 1];
}

void Huffmen::Init() {
    for (int i = 0; i < size; i ++) {
        cout << "Input The Character:";
        cin  >> character[i].value;
        cout << "Input The Weight:";
        cin  >> character[i].weight;

        character[i].parent = NULL;
        character[i].lChild = NULL;
        character[i].rChild = NULL;
    }
}

void Huffmen::Generate() {
    int node_first, node_second;
    int min_first,  min_second;
    for (int length = size; length <= size * 2 - 1; length ++) {
        
        node_first = node_second = -1;
        min_first  = min_second  = INIT;

        for (int i = 0; i < length; i ++) {
            if (character[i].parent == NULL) {
                if (character[i].weight <= min_first) {
                    min_second  = min_first;
                    node_second = node_first;

                    min_first   = character[i].weight;
                    node_first  = i;
                } else if (character[i].weight <= min_second) {
                    min_second  = character[i].weight;
                    node_second = i;
                }
            }
        }
        character[i].weight  = min_first + min_second;
        character[i].parent  = NULL;
        character[i].lChild  = &character[node_first];
        character[i].rChild  = &character[node_second];
        character[node_first].parent  = &character[i];
        character[node_second].parent = &character[i];
    }
}

void Huffmen::Print() {
    for (int i = 0; i < size * 2 - 1; i ++) {
        cout << "character:" << character[i].weight << endl;
    }
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
            huffmen.Init();
            huffmen.Generate();
            huffmen.Print();
            getchar();
            getchar();
            getchar();
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