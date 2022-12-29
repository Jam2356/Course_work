#include <UnitTest++/UnitTest++.h>
#include "/home/stud/C++Projects/C++Project/Client1/Interface.cpp"
#include "/home/stud/C++Projects/C++Project/Client1/ClassTCP.cpp"
#include "/home/stud/C++Projects/C++Project/Client1/Client.cpp"
#include "/home/stud/C++Projects/C++Project/Client1/Header.h"
#include <string>
#include <string.h>

SUITE(TPort)
{
    TEST(nullPort) {
        CHECK_THROW(ConnectTCP().connection(0),Errors);
    }
    TEST(lowPort) {
        CHECK_THROW(ConnectTCP().connection(333),Errors);
    }
    TEST(bigPort) {
        CHECK_THROW(ConnectTCP().connection(50000),Errors);
    }
}
SUITE(Connection)
{
    TEST(connection) {
        ConnectTCP().sock;
        CHECK_EQUAL(1,ConnectTCP().connection(33333));
    }
    TEST(connectionErr) {
        ConnectTCP().sock;
        CHECK_THROW(ConnectTCP().connection(3333),Errors);
    }
}
SUITE(HASH)
{
    TEST(THash1) {
        CHECK_EQUAL("F9C1E496823EBD52340672DC1CB2D87F",Client().takeHash("pass","salt"));
    }
    TEST(Hash2) {
        CHECK_EQUAL("0DDE5185DB7DA5C81F0FA71696506E4F",Client().takeHash("salt","123"));
    }
}
SUITE(TInterface)
{
    TEST(Interface1) {
        string sourceFile = "/home/stud/Kursach/sadasdas";
        CHECK_THROW(Interface().fileStrNumber(sourceFile),Errors);
    }
    TEST(Interface2) {
        string sourceFile = "/home/stud/Kursach/sa";
        CHECK_THROW(Interface().fileStrSize(sourceFile),Errors);
    }
    TEST(Interface3) {
        string sourceFile = "/home/stud/Kursach/saff";
        CHECK_THROW(Interface().fileVectData(sourceFile),Errors);
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
