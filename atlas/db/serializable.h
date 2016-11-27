#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#endif

#ifdef USEMONGO
#include <mongo/client/dbclient.h>
#else
#include <QJsonObject>
#endif

class Serializable
{
public:
    explicit Serializable();
    ~Serializable();

#if USEMONGO
    virtual mongo::BSONObj toBson() = 0;
#else
    virtual QJsonObject toJson() = 0;
#endif
};

#endif // SERIALIZABLE_H
