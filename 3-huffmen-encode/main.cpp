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
    void RemoveOtherNode(char **tree, int row, int index, int depth, bool isParent);
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
    outfile.open("code.txt", ios_base::out);
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
    cout << "Please Input data:" << endl;
    cin >> data;

    getchar();

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
        int *temp = new int[enCode->size() + 1];
        int tempSize = enCode->size() + 1;
        for (j = 0; j <= tempSize; j ++) {
            temp[j] = (int)data.find(enCode[j]);
        }
        int min = INIT;
        int min_site = 0;
        int state = 0;
        for (j = 0; j <= tempSize; j ++) {
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
    cout << endl;

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
    /* 获取深度, 建立二维数组 */
    int i, j;
    int depth   = this->GetDepth();
    int row     = depth;
    int col     = (int)pow(2, depth - 1) * 4;
    char **tree = new char*[row];
    for (i = 0; i < row; i ++) {
        tree[i] = new char[col];
    }
    for (i = 0; i < row; i ++) {
        for (j = 0; j < col; j ++) {
            tree[i][j] = ' ';
        }
    }

    /* 获取编码 */
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

    /* 将满二叉树插入数组中 */
    for (i = 0; i < depth; i ++) {
        int *temp = new int[(int)pow(2, i)];
        for (j = 0; j < pow(2, i); j ++) {
            temp[j] = col * (j + 1) / ((int)pow(2, i) + 1);
            tree[i][temp[j]] = '+';
        }
    }

    /* 字符替换 */
    for (i = 0; i < size; i ++) {
        int index  = 0;
        int length = (int)enCode[i].length();
        for (j = 1; j <= length; j ++) {
            if (enCode[i][j - 1] == '0') {
                index = 2 * index + 0;
            } else {
                index = 2 * index + 1;
            }
        }
        int position = col * (index + 1) / ((int)pow(2, length) + 1);
        tree[length][position] = value[i];
        if (length < depth - 1) {
            this->RemoveOtherNode(tree, length, index, depth, true);
        }
    }

    ofstream outfile;
    outfile.open("treePrint.txt");

    /* 输出数组 */
    for (i = 0; i < row; i ++) {
        for (j = 0; j < col; j ++) {
            cout << tree[i][j];
            outfile << tree[i][j];
        }
        cout << endl;
        outfile << endl;
    }

    outfile.close();
}

void Huffmen::RemoveOtherNode(char **tree, int row, int index, int depth, bool isParent) {

    if (row != depth) {
        int col             = (int)pow(2, depth - 1) * 4;
        int position        = col * (index + 1) / ((int)pow(2, row) + 1);
        if (!isParent) {
            tree[row][position] = ' ';
        }
        this->RemoveOtherNode(tree, row + 1, index * 2, depth, false);
        this->RemoveOtherNode(tree, row + 1, index * 2 + 1, depth, false);
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