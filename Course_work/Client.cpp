#include "Header.h"

string Client::takeHash(string pass, string salt)
{
    string result, hashMsg, msg = salt+pass;
    HexEncoder encoder(new StringSink(result));
    Weak::MD5 hash;
    hash.Update((const byte*)&msg[0], msg.size());
    hashMsg.resize(hash.DigestSize());
    hash.Final((byte*)&hashMsg[0]);
    StringSource(hashMsg, true, new Redirector(encoder));
    cout << "Generated HASH: " << result << endl << endl;
    return result;
}