#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <mongo/client/dbclient.h>

class Serializable
{
public:
    explicit Serializable();
    ~Serializable();

    virtual mongo::BSONObj toBson() = 0;
};

#endif // SERIALIZABLE_H
