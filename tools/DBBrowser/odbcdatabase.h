#ifndef ODBCDATABASE_H
#define ODBCDATABASE_H

#include "sscore/data/ssdatabase.h"

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>


class ODBCDatabase : public SSDatabase
{
public:
    ODBCDatabase(const QString& connName = QString());
    virtual ~ODBCDatabase();

    virtual bool connect();
    virtual bool open();
    virtual void close();

    virtual bool isConnected();
    virtual bool isOpened();

    virtual string error();

    virtual void setDatabaseName(string name);
    virtual string getDatabaseName();

    virtual void setUser(string user);
    virtual void setPassword(string password);

    virtual void* databaseInfo();


private:
    QSqlDatabase* _db;
    QString _user;
    QString _password;
};

#endif // ODBCDATABASE_H
