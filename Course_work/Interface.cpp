/** @file
 * @author Pavlov I.V.
 * @version 2.4
 * @date 23.12.2022
 * @brief Interface.cpp
 */
#include "Header.h"

/**
 * @brief Number of lines in file.
 * @return Return number of lines.
 * @throw Errors: Error open file source.
 */
unsigned int Interface::fileStrNumber(string sourceFile)
{
    ifstream input(sourceFile);
    string l;
    if(!input.is_open()) {
        throw Errors("Error open file source\nClass and metod: Interface::fileStrNumber\nVariable: input.is_open = false");
    }
    getline(input, l);
    int sNumber = stoi(string(1, l[0]));
    strNumber = sNumber;
    input.close();
    return strNumber;
}
/**
 * @brief Size of lines in file.
 * @return Return vector of size lines.
 * @throw Errors: Error open file source.
 */
vector<unsigned int> Interface::fileStrSize(string sourceFile)
{
    ifstream input(sourceFile);
    if(!input.is_open()) {
        throw Errors("Error open file source\nClass and metod: Interface::fileStrSize\nVariable: input.is_open = false");
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
/**
 * @brief Value of lines in file.
 * @return Return 2D vector with vectors of values of all lines in file.
 * @throw Errors: Error open file source.
 */
vector <vector<uint32_t>> Interface::fileVectData(string sourceFile)
{
    ifstream input1(sourceFile);
    if(!input1.is_open()) {
        throw Errors("Error open file source\nClass and metod: Interface::fileVectData\nVariable: input1.is_open = false");
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
/**
 * @brief Getting data from cmd.
 */
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
        if(opt == 't') { 
            serverPort = stoi(a);
        } else if(opt == 'r') { 
            sourceFile = a;
        } else if(opt == 'y') { 
            resultFile = a;
        }
    }
}
/**
 * @brief Save number results.
 */
int Interface::saveResultNumber(uint32_t number, string resultF)
{
    ofstream outputF(resultF, ios::binary);
    outputF.write((char*)&number, sizeof(number));
    outputF.close();
    return 0;
}
/**
 * @brief Save data results.
 */
int Interface::saveResultData(uint32_t resultDat[], string resultF)
{
    ofstream outputF(resultF, ios::binary | ios::app);
    outputF.write((char*)&resultDat, sizeof(resultDat));
    outputF.close();
    return 0;
}
/**
 * @return Server port.
 */
int Interface::getServerPort()
{
    return serverPort;
}
/**
 * @return Client password.
 */
string Interface::getClientPass()
{
    return clientPass;
}
/**
 * @return Client ID.
 */
string Interface::getClientID()
{
    return clientID;
}
/**
 * @return Path result file.
 */
string Interface::getPathResult()
{
    return resultFile;
}
/**
 * @return Path source file.
 */
string Interface::getPathSource()
{
    return sourceFile;
}
