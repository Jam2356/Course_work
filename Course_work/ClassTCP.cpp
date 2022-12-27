#include "Header.h"
int ConnectTCP::connection(int port)
{
    if (sock == -1) {
        throw cipher_error("Error socket\nClass and metod: ConnectTCP::connection\nVariable: sock = -1");
    }
    string ipAddress = "127.0.0.1";
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
    //	Connect to the server on the socket
    int connectRes = connect(sock, (const sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1) {
        throw cipher_error("Error connection\nClass and metod: ConnectTCP::connection\nVariable: connectRes = -1");
    }
    return 1;
}
int ConnectTCP::sendingID(string ID)
{
    char userInput[ID.length()];
    ID.copy(userInput,ID.length());
    int sendRes = send(sock, userInput, sizeof(userInput), 0);
    if (sendRes == -1) {
        throw cipher_error("Error sending ID\nClass and metod: ConnectTCP::sendingID\nVariable: sendRes = -1");
    }
    return 1;
}
void ConnectTCP::getSalt()
{
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096, 0);
    sBuf = string(buf);
    if (bytesReceived == -1) {
        throw cipher_error("Error geting SALT\nClass and metod: ConnectTCP::getSalt\nVariable: bytesReceived = -1");
    }
}
string ConnectTCP::sendingPass(string completeHASH)
{
    char charsMSG[completeHASH.length()];
    completeHASH.copy(charsMSG, completeHASH.length());
    int sendRes1 = send(sock, charsMSG, sizeof(charsMSG), 0);
    if (sendRes1 == -1) {
        throw cipher_error("Error sending password\nClass and metod: ConnectTCP::sendingPass\nVariable: sendRes1 = -1");
    }
    int bytesReceived1 = recv(sock, okErr, 2, 0);
    if (bytesReceived1 == -1) {
        throw cipher_error("Error geting authentication\nClass and metod: ConnectTCP::sendingPass\nVariable: bytesReceived1 = -1");
    }
    return charsMSG;//////////
}
int ConnectTCP::sendingData(unsigned int number, vector<unsigned int> sizes, vector <vector<uint32_t>> vData)
{
    unsigned int bufNumber[1];
    uint32_t saveDataTemporaryArr[number];
    bufNumber[0] = number;
    int sendRes3 = send(sock, bufNumber, sizeof(bufNumber), 0);
    if (sendRes3 == -1) {
        throw cipher_error("Error sending number of rows\nClass and metod: ConnectTCP::sendingData\nVariable: sendRes3 = -1");
    }
    int i = 0;
    while(i<number) {
        unsigned int bufSizeTemporary[1];
        bufSizeTemporary[0] = sizes[i];
        int sendRes1 = send(sock, bufSizeTemporary, sizeof(bufSizeTemporary), 0); //отправка массива[1] размер строки
        if (sendRes1 == -1) {
            throw cipher_error("Error sending string size\nClass and metod: ConnectTCP::sendingData\nVariable: sendRes1 = -1");
        }
        uint32_t bufDataTemporary[sizes[i]];
        for (int l = 0; l < sizes[i]; l++) {
            bufDataTemporary[l] = vData[i][l];
        }
        int sendRes2 = send(sock, bufDataTemporary, sizeof(bufDataTemporary), 0); //отправка элементов
        if (sendRes2 == -1) {
            throw cipher_error("Error sending string values\nClass and metod: ConnectTCP::sendingData\nVariable: sendRes2 = -1");
        }
        int bytesReceived2 = recv(sock, bufRecv, 32, 0);
        if (bytesReceived2 == -1) {
            throw cipher_error("Error getting result\nClass and metod: ConnectTCP::sendingData\nVariable: bytesReceived2 = -1");
        }
        countNumberResult += 1;
        cout << "Result: " << *bufRecv << endl;
        saveDataTemporaryArr[i] = *bufRecv;
        i++;
    }
    cout << "\nNumber results: " << countNumberResult << endl << endl;
    for(int k = 0; k<number; k++) {
        saveData[k] = saveDataTemporaryArr[k];
    }
    return 0;
}
void ConnectTCP::closeConnect()
{
    close(sock);
}
