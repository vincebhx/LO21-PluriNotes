#ifndef NOTEEXCEPTION_H
#define NOTEEXCEPTION_H

#include <iostream>

using namespace std;

class NoteException
{
    string info;
public:
    NoteException(string i): info(i) {}
    const string& getInfo() const { return info; }
};

#endif // NOTEEXCEPTION_H
