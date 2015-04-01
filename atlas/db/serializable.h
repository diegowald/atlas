#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#endif

#include <mongo/client/dbclient.h>

class Serializable
{
public:
    explicit Serializable();
    ~Serializable();

    virtual mongo::BSONObj toBson() = 0;
};

#endif // SERIALIZABLE_H
