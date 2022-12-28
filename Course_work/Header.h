/** @file
 * @author Pavlov I.V.
 * @version 2.4
 * @date 23.12.2022
 * @brief Header file Header.h
 */
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
/** @brief TCP connection establishment, data transfer.
 * @details Methods: connection - connection establishment,
 * sendingID - send user id,
 * getSalt - receiving salt,
 * sendingPass - send hash,
 * sendingData - correct sending of data.
 */
class ConnectTCP
{
public:
    char buf[4096]; ///< Bufer receive
    string sBuf; ///< Bufer in string
    char okErr[2]; ///< Bufer authentication
    uint32_t bufRecv[32]; ///< Temporary bufer result
    uint32_t countNumberResult = 0; ///< Number result
    uint32_t saveData[200]; ///< Bufer result
    int serverPortTCP; ///< Server port
    int sock = socket(AF_INET, SOCK_STREAM, 0); ///< Socket
    int connection(int);
    int sendingID(string);
    void getSalt();
    string sendingPass(string);
    int sendingData(unsigned int, vector<unsigned int>, vector <vector<uint32_t>>);
    void closeConnect();
};
/** @brief Exception handling.
 */
class Errors: public invalid_argument
{
public:
    explicit Errors(const string& what_arg):
        invalid_argument(what_arg) {}
};
/** @brief Performs MD5 hashing.
 * @details Method: takeHash - MD5 hashing.
 */
class Client
{
public:
    string takeHash(string, string);
};
/** @brief Receiving information from CMD. Correct extraction and sorting of file data.
 * @details Methods: sileStrNumber - number of lines in file,
 * fileStrSize - size of each line in file,
 * fileVectData - values of all lines in file,
 * vectIn - getting CMD options,
 * saveResultNumber - writing the number of results to file,
 * saveResultData - writing results to file.
 * Methods "get": getServerPort, getClientID, getClientPass, getPathResult, getPathSource.
 */
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
    unsigned int strNumber; ///< Number lines
    string sourceFile; ///< Path file source
    string resultFile; ///< Path file result
    string clientID = "user"; ///< Client ID
    string clientPass = "P@ssW0rd"; ///< Client Password
    int serverPort = 0; ///< Server port
};