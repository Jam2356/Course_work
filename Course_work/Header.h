#pragma once
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/cryptlib.h>
using namespace std;
using namespace CryptoPP;
class ConnectTCP
{
public:
    char buf[4096];
    string sBuf;
    char okErr[2];
    uint32_t bufRecv[32];
    uint32_t countNumberResult = 0;
    uint32_t saveData[200]; // если больше будет ошибка
    int serverPortTCP;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int connection(int);
    int sendingID(string);
    void getSalt();
    string sendingPass(string);
    int sendingData(unsigned int, vector<unsigned int>, vector <vector<uint32_t>>);
    void closeConnect();
};
class cipher_error: public invalid_argument
{
public:
    explicit cipher_error(const string& what_arg):
        invalid_argument(what_arg) {}
};
class Client
{
public:
    string takeHash(string, string);
};
class Interface
{
public:
    unsigned int fileStrNumber(string);
    vector<unsigned int> fileStrSize(string);
    vector <vector<uint32_t>> fileVectData(string);
    void vectIn(int argc, char **argv);
    int saveResultNumber(uint32_t number, string resultF);
    int saveResultData(uint32_t resultDat[], string resultF);
    int getServerPort();
    string getClientPass();
    string getClientID();
    string getPathResult();
    string getPathSource();
    unsigned int strNumber;
    string sourceFile;
    string resultFile;
    string clientID = "user";
    string clientPass = "P@ssW0rd";
    int serverPort = 0;
};