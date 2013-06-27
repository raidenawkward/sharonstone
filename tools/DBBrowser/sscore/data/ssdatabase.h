/*
 * [INTERFACE]
 * for data base connection
 * a database could be database services, file system and so on
 */

#ifndef SSDATABASE_H
#define SSDATABASE_H


#include <string>

using namespace std;


class SSDatabase
{
public:
    virtual bool connect() = 0;
    virtual bool open() = 0;
    virtual void close() = 0;

    virtual bool isConnected() = 0;
    virtual bool isOpened() = 0;

    virtual string error() = 0;

    virtual void setDatabaseName(string name) = 0;
    virtual string getDatabaseName() = 0;

    virtual void setUser(string user) = 0;
    virtual void setPassword(string password) = 0;

    virtual void* databaseInfo() = 0;

protected:
    SSDatabase() {}
};

#endif // SSDATABASE_H
