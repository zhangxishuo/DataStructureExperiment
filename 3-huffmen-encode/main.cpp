#include <iostream>
#include <cstring>
#include <algorithm>
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

    Huffmen();
    Huffmen(int number);
    int  GetDepth();
    void Init();
    void Print();
    void Encode();
    void Generate();
    void TreeToFile();
    void WordToCode();
    void CodeToWord();
    void PrintTree();
    string GetCode();
    vector<string> Split(string str, string sep);
};

Huffmen::Huffmen() {

}

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
    int min_first,  min_second;
    int i;
    for (int length = size; length <= size * 2 - 1; length++) {

        node_first = node_second = -1;
        min_first  = min_second  = INIT;

        for (i = 0; i < length; i++) {
            if (character[i].parent == NULL) {
                if (character[i].weight <= min_first) {
                    min_second  = min_first;
                    node_second = node_first;

                    min_first  = character[i].weight;
                    node_first = i;
                }
                else if (character[i].weight <= min_second) {
                    min_second  = character[i].weight;
                    node_second = i;
                }
            }
        }
        character[i].weight = min_first + min_second;
        character[i].parent = NULL;
        character[i].lChild = &character[node_first];
        character[i].rChild = &character[node_second];
        character[node_first].code    = '0';
        character[node_second].code   = '1';
        character[node_first].parent  = &character[i];
        character[node_second].parent = &character[i];
    }
}

void Huffmen::Encode() {
    ofstream outfile;
    outfile.open("codeFile.txt");
    string *strArr = new string[size];
    int i;
    for (i = 0; i < size; i ++) {
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
        outfile << character[i].weight << " " << character[i].parent->position << " 0 0 " << character[i].value << endl;
    }
    for (i = size; i < size * 2 - 2; i ++) {
        outfile << character[i].weight << " " << character[i].parent->position << " " << character[i].lChild->position << " " << character[i].rChild->position << endl;
    }
    outfile << character[i].weight << " 0 " << character[i].lChild->position << " " << character[i].rChild->position;
    outfile.close();
}

string Huffmen::GetCode() {
    string data;
    ifstream infile;
    infile.open("code.txt");
    getline(infile, data);
    infile.close();
    return data;
}

void Huffmen::WordToCode() {
    int i, j;
    string code = this->GetCode();
    string data;
    ifstream infile;
    infile.open("toBeTran.txt");
    infile >> data;
    cout << data << endl;
    infile.close();

    vector<string> codes = this->Split(code, " ");

    size = (int)codes.size() / 2;

    char   *value  = new char[size];
    string *enCode = new string[size];

    for (i = 0; i < codes.size(); i ++) {
        if (i % 2 == 0) {
            value[i / 2] = codes[i][0];
        } else {
            enCode[(i - 1) / 2] = codes[i];
        }
    }

    for (j = 0; j < data.length(); j ++) {
        for (i = 0; i < size; i ++) {
            int result = (int)data.find(value[i]);
            if (result != -1) {
                data.replace(data.find(value[i]), 1, enCode[i]);
            }
        }
    }

    ofstream outfile;
    outfile.open("codeFile.txt");
    outfile << data;
    outfile.close();
}

void Huffmen::CodeToWord() {
    int i, j;
    string code = this->GetCode();
    string data;
    ifstream infile;
    infile.open("codeFile.txt");
    infile >> data;
    infile.close();

    vector<string> codes = this->Split(code, " ");

    size = (int)codes.size() / 2;

    string *value  = new string[size];
    string *enCode = new string[size];

    for (i = 0; i < codes.size(); i ++) {
        if (i % 2 == 0) {
            value[i / 2] = codes[i];
        } else {
            enCode[(i - 1) / 2] = codes[i];
        }
    }

    for (i = 0; data[i] != '\0'; i ++) {
        int *temp = new int[enCode->length() + 1];
        for (j = 0; j <= enCode->length(); j ++) {
            temp[j] = (int)data.find(enCode[j]);
        }
        int min = INIT;
        int min_site = 0;
        int state = 0;
        for (j = 0; j <= enCode->length(); j ++) {
            if (temp[j] <= min && temp[j] != -1) {
                min = temp[j];
                min_site = j;
                state = 1;
            }
        }
        if (state == 1) {
            data.replace(min, enCode[min_site].length(), value[min_site]);
        }
    }

    cout << data << endl;

    ofstream outfile;
    outfile.open("textFile.txt");
    outfile << data;
    outfile.close();
}

vector<string> Huffmen::Split(string str, string sep) {
    char* cstr = const_cast<char*>(str.c_str());
    char* current;
    vector<string> arr;
    current = strtok(cstr,sep.c_str());
    while(current != NULL){
        arr.push_back(current);
        current=strtok(NULL, sep.c_str());
    }
    return arr;
}

void Huffmen::Print() {
    int i;
    string data;
    ifstream infile;
    infile.open("codeFile.txt");
    infile >> data;
    infile.close();

    ofstream outfile;
    outfile.open("codePrint.txt");

    for (i = 0; data[i] != '\0'; i ++) {
        cout << data[i];
        outfile << data[i];
        if ((i + 1) % 50 == 0 && i != 0) {
            cout << endl;
            outfile << endl;
        }
    }

    outfile.close();
}

int Huffmen::GetDepth() {
    int i;
    string code = this->GetCode();
    string data;

    vector<string> codes = this->Split(code, " ");

    size = (int)codes.size() / 2;

    string *enCode = new string[size];

    for (i = 0; i < codes.size(); i ++) {
        if (i % 2 != 0) {
            enCode[(i - 1) / 2] = codes[i];
        }
    }

    int *length = new int[size];
    for (i = 0; i < size; i ++) {
        length[i] = (int)enCode[i].length();
    }

    int max = 0;
    for (i = 0; i < size; i ++) {
        if (length[i] > max) {
            max = length[i];
        }
    }

    return max + 1;
}

void Huffmen::PrintTree() {
    int i, j;
    int depth   = this->GetDepth();
    int row     = depth * 4 - 3;
    int col     = (int)pow(2, depth) - 1;
    char **tree = new char*[row];
    for (i = 0; i < row; i ++) {
        tree[i] = new char[col];
    }
    for (i = 0; i < row; i ++) {
        for (j = 0; j < col; j ++) {
            tree[i][j] = ' ';
        }
    }

    string code = this->GetCode();
    vector<string> codes = this->Split(code, " ");

    char   *value  = new char[size];
    string *enCode = new string[size];

    for (i = 0; i < codes.size(); i ++) {
        if (i % 2 == 0) {
            value[i / 2] = codes[i][0];
        } else {
            enCode[(i - 1) / 2] = codes[i];
        }
    }

    for (i = 0; i < size; i ++) {
        cout << value[i] << " " << enCode[i] << endl;
    }

    for (i = 0; i < row; i ++) {
        for (j = 0; j < col; j ++) {
            cout << tree[i][j];
        }
        cout << endl;
    }
}

int main() {

    char operate;

    while (1) {
        cout << "I E D P T Q : ";
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
                Huffmen huffmen;
                huffmen.WordToCode();
                break;
            }
            case 'D': {
                Huffmen huffmen;
                huffmen.CodeToWord();
                break;
            }
            case 'P': {
                Huffmen huffmen;
                huffmen.Print();
                break;
            }
            case 'T': {
                Huffmen huffmen;
                huffmen.PrintTree();
                break;
            }
        }

        if (operate == 'Q') {
            break;
        }
    }

    return 0;
}