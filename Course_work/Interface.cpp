#include "Header.h"


unsigned int Interface::fileStrNumber(string sourceFile)
{
    ifstream input(sourceFile);
    string l;
    if(!input.is_open()) {
        throw cipher_error("Error open file source\nClass and metod: Interface::fileStrNumber\nVariable: input.is_open = false");
    }
    getline(input, l);
    int sNumber = stoi(string(1, l[0]));
    strNumber = sNumber;
    input.close();
    return strNumber;
}
vector<unsigned int> Interface::fileStrSize(string sourceFile)
{
    ifstream input(sourceFile);
    if(!input.is_open()) {
        throw cipher_error("Error open file source\nClass and metod: Interface::fileStrSize\nVariable: input.is_open = false");
    }
    vector<unsigned int> sizeVect(strNumber+1);
    string l;
    int i = 0;
    while(i <= strNumber) {
        getline(input, l);
        sizeVect.at(i) = stoi(string(l));
        i++;
    }
    sizeVect.erase(sizeVect.begin());
    input.close();
    return sizeVect;
}
vector <vector<uint32_t>> Interface::fileVectData(string sourceFile)
{
    ifstream input1(sourceFile);
    if(!input1.is_open()) {
        throw cipher_error("Error open file source\nClass and metod: Interface::fileVectData\nVariable: input1.is_open = false");
    }
    string l;
    getline(input1, l);
    vector <vector<uint32_t>> vec(strNumber);
    string parsed;
    int i = 0;
    while(i < strNumber) {
        getline(input1, l);
        l.erase(0, 2);
        stringstream input_stringstream(l);
        for(int j = 0; j < fileStrSize(sourceFile)[i]; j++) {
            if (getline(input_stringstream,parsed,' ')) {
                uint32_t dou = atoi(parsed.c_str());
                vec.at(i).push_back(dou);
            }
        }
        if(!input1.eof()) {
            i++;
        }
    }
    input1.close();
    return vec;
}
void Interface::vectIn(int argc, char **argv)
{
    if(argc == 1 or (argc == 2 and getopt(argc, argv, "h") == 'h')) {
        cout << "\n\t\tСправка\n" << "\nВведите:\n" << "\t-t сетевой адрес сервера\n"  << "\t-r путь до файла с исходными данными\n" << "\t-y путь до файла сохранения результатов\n" << endl;
        cout << "Должно получиться: ./программа -t сетевой_адрес -r путь_к_файлу -y путь_к_файлу\n" << endl;
        cout << "Примечани:\n" << endl;
        cout << "\tВызов справки -h или запуск без параметров\n" << endl;
        exit(0);
    }
    int opt;
    while((opt = getopt(argc, argv, "t:r:y:"))!= -1) {
        string a = optarg;
        if(opt == 't') { //server port
            serverPort = stoi(a);
        } else if(opt == 'r') { //puth file-source
            sourceFile = a;
        } else if(opt == 'y') { //puth file-result
            resultFile = a;
        }
    }
}
int Interface::saveResultNumber(uint32_t number, string resultF)
{
    ofstream outputF(resultF, ios::binary);
    outputF.write((char*)&number, sizeof(number));
    outputF.close();
    return 0;
}
int Interface::saveResultData(uint32_t resultDat[], string resultF)
{
    ofstream outputF(resultF, ios::binary | ios::app);
    outputF.write((char*)&resultDat, sizeof(resultDat));
    outputF.close();
    return 0;
}
int Interface::getServerPort()
{
    return serverPort;
}
string Interface::getClientPass()
{
    return clientPass;
}
string Interface::getClientID()
{
    return clientID;
}
string Interface::getPathResult()
{
    return resultFile;
}
string Interface::getPathSource()
{
    return sourceFile;
}
