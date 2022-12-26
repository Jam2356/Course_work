#pragma once
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <cryptopp/cryptlib.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
using namespace std;
using namespace CryptoPP;

class ConnectTCP
{
public:
    char buf[4096];
    string sBuf;
    char bufRecv[32];
    
    int serverPortTCP;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    void connection();
    int sendingID(string);
    void takeSalt();
    string sendingPass(string);
    string sendingData(unsigned int, vector<unsigned int>, vector <vector<uint32_t>>);

};
