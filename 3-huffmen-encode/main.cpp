#include <iostream>
#include <string>
#include <algorithm>
#include <fcntl.h>
#include <fstream>

using namespace std;

const int INIT = 65535;

class Character {
public:
    char value;
    char code;
    int  weight;
    int  position;
    Character *parent;
    Character *lChild;
    Character *rChild;
};

class Huffmen {
public:
    int size;
    Character *character;

    Huffmen(int number);
    void Init();
    void Generate();
    void Encode();
    void TreeToFile();
    static string GetCode();
    static void WordToCode();
};

Huffmen::Huffmen(int number) {
    size = number;
    character = new Character[size * 2 - 1];
}

void Huffmen::Init() {
    int i;
    for (i = 0; i < size; i++) {
        cout << "Input The Character:";
        cin >> character[i].value;
        cout << "Input The Weight:";
        cin >> character[i].weight;
    }

    for (i = 0; i < size * 2 - 1; i++) {
        character[i].parent = NULL;
        character[i].lChild = NULL;
        character[i].rChild = NULL;
        character[i].position = i + 1;
    }
}

void Huffmen::Generate() {
    int node_first, node_second;
    int min_first, min_second;
    int i;
    for (int length = size; length <= size * 2 - 1; length++) {

        node_first = node_second = -1;
        min_first = min_second = INIT;

        for (i = 0; i < length; i++) {
            if (character[i].parent == NULL) {
                if (character[i].weight <= min_first) {
                    min_second = min_first;
                    node_second = node_first;

                    min_first = character[i].weight;
                    node_first = i;
                }
                else if (character[i].weight <= min_second) {
                    min_second = character[i].weight;
                    node_second = i;
                }
            }
        }
        character[i].weight = min_first + min_second;
        character[i].parent = NULL;
        character[i].lChild = &character[node_first];
        character[i].rChild = &character[node_second];
        character[node_first].code = '0';
        character[node_second].code = '1';
        character[node_first].parent = &character[i];
        character[node_second].parent = &character[i];
    }
}

void Huffmen::Encode() {
    ofstream outfile;
    outfile.open("codeFile.txt");
    string *strArr = new string[size];
    int i;
    for (i = 0; i < size; i++) {
        Character *temp;
        temp = &character[i];
        while (temp->parent != NULL) {
            strArr[i] += temp->code;
            temp = temp->parent;
        }
        strArr[i] = strArr[i].substr(0, strArr[i].length()-1);
        reverse(strArr[i].begin(), strArr[i].end());
    }
    for (i = 0; i < size; i ++) {
        outfile << character[i].value << " " << strArr[i] << " ";
    }
    outfile.close();
}

void Huffmen::TreeToFile() {
    ofstream outfile;
    outfile.open("hfmTree.txt");
    int i;
    for (i = 0; i < size; i ++) {
        outfile << i + 1 << " " << character[i].weight << " " << character[i].parent->position << " 0 0" << endl;
    }
    for (i = size; i < size * 2 - 2; i ++) {
        outfile << i + 1 << " " << character[i].weight << " " << character[i].parent->position << " " << character[i].lChild->position << " " << character[i].rChild->position << endl;
    }
    outfile << i + 1 << " " << character[i].weight << " 0 " << character[i].lChild->position << " " << character[i].rChild->position << endl;
    outfile.close();
}

string Huffmen::GetCode() {
    string data;
    ifstream infile;
    infile.open("codeFile.txt");
    getline(infile, data);
    infile.close();
    cout << data;
    return data;
}

void Huffmen::WordToCode() {
    GetCode();
    string data;
    ifstream infile;
    infile.open("toBeTran.txt");
    infile >> data;
    infile.close();
    cout << data;
}

int main() {

    char operate;

    cout << "I E D P T : ";
    cin >> operate;

    switch (operate) {
        case 'I': {
            int number;
            cout << "Input The Numbers Of Characters: ";
            cin >> number;
            Huffmen huffmen(number);
            huffmen.Init();
            huffmen.Generate();
            huffmen.Encode();
            huffmen.TreeToFile();
            break;
        }
        case 'E': {
            Huffmen::WordToCode();
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