#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include "Header.h"

using namespace std;

class Client
{
public:
    int a11;
    int b11;
    int Printsss(int a, int b)
    {
        cout << a << endl;
        cout << b11 + b << endl;
        return b11+a11;
    }


    string takeHash(string pass, string salt)
    {
        string result, hashMsg, msg = salt+pass; ///////////если ошибка поменять местами
        HexEncoder encoder(new StringSink(result));
        Weak::MD5 hash;
        hash.Update((const byte*)&msg[0], msg.size());
        hashMsg.resize(hash.DigestSize());
        hash.Final((byte*)&hashMsg[0]);
        StringSource(hashMsg, true, new Redirector(encoder));
        cout << "Generated HASH: " << result << endl << endl;
        return result;
    }
};

//test//test//test//test//test//test//test


class Interface   //принимает значения из комстроки и правильно выводит данные из файла
{
public:
    static int serverPort;
    int fileStrNumber()
    {
        ifstream input(sourceFile);
        string l;
        getline(input, l);
        int sNumber = stoi(string(1, l[0]));
        strNumber = sNumber;
        input.close();
        return strNumber;
    }
    vector<unsigned int> fileStrSize()
    {
        ifstream input(sourceFile);
        vector<unsigned int> sizeVect(strNumber+1);
        string l;
        int i = 0;
        while(i <= strNumber) {
            getline(input, l);
            sizeVect.at(i) = stoi(string(1, l[0]));
            i++;
        }
        sizeVect.erase(sizeVect.begin());//удаление первого значения
        /*for (int i = 0; i < sizeVect.size(); i++) { //если надо отобразить вектор
            cout << sizeVect[i] << " ";
        }*/
        input.close();
        return sizeVect;
    }
    vector <vector<double>> fileVectData()
    {
        ifstream input1(sourceFile);
        string l;
        getline(input1, l);
        vector <vector<double>> vec(strNumber);
        string parsed;
        int i = 0;
        while(i < strNumber) {
            getline(input1, l);
            l.erase(0, 2); //удаляем первый символ и пробел
            stringstream input_stringstream(l);
            for(int j = 0; j < fileStrSize()[i]; j++) {
                if (getline(input_stringstream,parsed,' ')) {
                    double dou = atof(parsed.c_str());
                    vec.at(i).push_back(dou);
                }
            }
            if(!input1.eof()) {
                i++;
            }
        }
        /*cout << "\n\nПросмотр vec:" << endl << endl; //если надо отобразить вектор double
        for (int i = 0; i < strNumber; i++) {
            cout << "\n" << endl;
            for (int j = 0; j < fileStrSize()[i]; j++) {
                cout << vec[i][j] << " ";
            }
        }*/
        input1.close();
        return vec;
    }
    void vectIn(int argc, char **argv) //vector <string>
    {
        // !!!!!!!!!! сохранять данные в переменные их public и использовать уже не vector <string> а void
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
            if(opt == 't') { //сетевой адрес сервера
                serverPort = stoi(a); ///////////////////////////////пока что не работает
            } else if(opt == 'r') { //путь к файлу с исходными данными
                sourceFile = a;
            } else if(opt == 'y') { //путь к файлу сохранения результатов
                resultFile = a;
            }
        }
    }
    string getClientPass()
    {
        return clientPass;
    }
    string getClientID()
    {
        return clientID;
    }
    string getPathResult()
    {
        return resultFile;
    }
    string getPathSource()
    {
        return sourceFile;
    }
private:
    int strNumber;
    string sourceFile;
    string resultFile;
    string clientID = "user";
    string clientPass = "P@ssW0rd";
};
int Interface::serverPort = 0;






int main(int argc, char **argv)
{



    string inpath = "/home/stud/Kursach/input_data";//
    string outpath = "/home/stud/Kursach/output_data";//
    Client User;
    ConnectTCP TCP;
    Interface InterfFile;
    //while берет вектор и оправляет на сервер, должен быть в TCP классе
    InterfFile.vectIn(argc, argv); //Вызывать обязательно!!!!!
    vector <unsigned int> test;
    //cout << InterfFile.fileStrSize()[0] << endl; //test+ вывод вектора размеров
    //cout << InterfFile.fileVectData()[1][0] <<endl; //test+ вывод вектора значений

    cout << "\nFile contents: " << endl;

    InterfFile.vectIn(argc, argv); //Вызывать обязательно!!!!!
    for(int i = 0; i < InterfFile.fileStrNumber(); i++) { //можно использовать для перезаписи в файл
        cout << "\n";
        for(int j = 0; j < InterfFile.fileStrSize()[i]; j++) {
            cout << InterfFile.fileVectData()[i][j] << " ";
        }
    }
    cout << "\n\nUser ID: " << InterfFile.getClientID() << endl << endl;
    cout << "User password: " << InterfFile.getClientPass() << endl << endl;
    cout << "Server port: " << Interface::serverPort << endl << endl;





    TCP.connection();
    TCP.sendingID(InterfFile.getClientID());
    TCP.takeSalt();
    TCP.sendingPass(User.takeHash(InterfFile.getClientPass(), TCP.sBuf));
    TCP.sendingData(InterfFile.fileStrNumber(), InterfFile.fileStrSize(), InterfFile.fileVectData());





}
