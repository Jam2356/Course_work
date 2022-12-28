#include "Header.h"

int main(int argc, char **argv)
{
    // Class objects
    Client User;
    ConnectTCP TCP;
    Interface InterfFile;
    try {
        // String values
        cout << "\nFile contents: " << endl;
        InterfFile.vectIn(argc, argv);
        for(int i = 0; i < InterfFile.fileStrNumber(InterfFile.sourceFile); i++) {
            cout << "\n";
            for(int j = 0; j < InterfFile.fileStrSize(InterfFile.sourceFile)[i]; j++) {
                cout << InterfFile.fileVectData(InterfFile.sourceFile)[i][j] << " ";
            }
        }
        // Row size
        cout << "\n\nString size: \n" << endl;
        for(int i = 0; i < InterfFile.fileStrNumber(InterfFile.sourceFile); i++) {
            cout << InterfFile.fileStrSize(InterfFile.sourceFile)[i] << "\n";
        }
        cout << "\nUser ID: " << InterfFile.getClientID() << endl << endl;
        cout << "User password: " << InterfFile.getClientPass() << endl << endl;
        cout << "Server port: " << InterfFile.getServerPort() << endl << endl;//serverPort
        // Data exchange
        TCP.connection(InterfFile.getServerPort());
        TCP.sendingID(InterfFile.getClientID());
        TCP.getSalt();
        TCP.sendingPass(User.takeHash(InterfFile.getClientPass(), TCP.sBuf));
        TCP.sendingData(InterfFile.fileStrNumber(InterfFile.sourceFile), InterfFile.fileStrSize(InterfFile.sourceFile), InterfFile.fileVectData(InterfFile.sourceFile));
        InterfFile.saveResultNumber(TCP.countNumberResult, InterfFile.getPathResult());
        InterfFile.saveResultData(TCP.saveData, InterfFile.getPathResult());
        TCP.closeConnect();
    } catch (const cipher_error & e) {
        cerr << "\n\tError:\n" << e.what() << endl << endl;
    }
    return 0;
}