#include "Header.h"





void ConnectTCP::connection()
{
    //	Create a socket

    if (sock == -1) {
        exit(0);
    }
    //	Create a hint structure for the server we're connecting with
    int port = 33333;
    string ipAddress = "127.0.0.1";
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
    //	Connect to the server on the socket
    int connectRes = connect(sock, (const sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1) {
        cout << "Error connection" << endl;
        exit(0);
    }
}
int ConnectTCP::sendingID(string ID)
{
    char userInput[ID.length()];
    ID.copy(userInput,ID.length());

    //		Enter lines of text

    //		Send to server
    int sendRes = send(sock, userInput, sizeof(userInput), 0);
    if (sendRes == -1) {
        cout << "Could not send to server! Whoops!\r\n";
        return 1;
    }
}
void ConnectTCP::takeSalt()
{
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096, 0);
    sBuf = string(buf);
    if (bytesReceived == -1) {
        cout << "There was an error getting response from server\r\n";
        exit(0);
    }
}
string ConnectTCP::sendingPass(string completeHASH)
{
    char charsMSG[completeHASH.length()];
    completeHASH.copy(charsMSG, completeHASH.length());
    int sendRes1 = send(sock, charsMSG, sizeof(charsMSG), 0);
    if (sendRes1 == -1) {
        cout << "Could not send to server! Whoops!\r\n";
        exit(0);
    }

    return charsMSG;//////////
}
string ConnectTCP::sendingData(unsigned int number, vector<unsigned int> sizes, vector <vector<uint32_t>> vData)
{
    unsigned int bufNumber[1];
    bufNumber[0] = number;
    int sendRes3 = send(sock, bufNumber, sizeof(bufNumber), 0);
    if (sendRes3 == -1) {
        cout << "Could not send to server! Whoops!\r\n";
        exit(0);
    }

    int i = 0;
    while(i<number) {
        unsigned int bufSizeTemporary[1];
        bufSizeTemporary[0] = sizes[i];
        int sendRes1 = send(sock, bufSizeTemporary, sizeof(bufSizeTemporary), 0); //отправка массива[1] размер строки
        if (sendRes1 == -1) {
            cout << "Could not send to server! Whoops!\r\n";
            exit(0);
        }


        uint32_t bufDataTemporary[sizes[i]];
        for (int l = 0; l < sizes[i]; l++) {
            bufDataTemporary[l] = vData[i][l];
        }

        int sendRes2 = send(sock, bufDataTemporary, sizeof(bufDataTemporary), 0); //отправка элементов
        if (sendRes2 == -1) {
            cout << "Could not send to server! Whoops!\r\n";
            exit(0);
        }
        //memset(bufRecv, 0, 4096);
        //cout <<  << endl
        int bytesReceived1 = recv(sock, bufRecv, 32, 0);
        cout << "Responce from server: " << bufRecv << endl; //из байтов в числа!!!!! первый перевод неверный//ВЫВОДИТЬ В ВИДЕ ДВОИЧНОГО ЧИСЛА В ФАЙЛ
        
        i++;
    }

    close(sock);
    return 0;
}
