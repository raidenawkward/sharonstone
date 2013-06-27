#include "odbcdatabase.h"
#include <QtSql/QSqlError>

#define ODBC_DB_CONN_TYPE ("QODBC")
#define ODBC_DB_FILE_NAME "barcode.mdb"
#define ODBC_DB_CONN_STRING "DRIVER={Microsoft Access Driver" \
                            "(*.mdb)};" \
                            "FIL={MS Access};" \
                            "DBQ=%1;" \
                            "UID='%2';PWD='%3'"

ODBCDatabase::ODBCDatabase(const QString& connName)
{
    _db = new QSqlDatabase();
    *_db = QSqlDatabase::addDatabase(ODBC_DB_CONN_TYPE, connName);
}

ODBCDatabase::~ODBCDatabase()
{
    if (_db) {
        if (_db->isOpen())
            _db->close();

        QString connName = _db->connectionName();

        delete _db;
        QSqlDatabase::removeDatabase(connName);
    }
}

bool ODBCDatabase::connect()
{
    if (!_db)
        return false;

    _db->setDatabaseName(QString(ODBC_DB_CONN_STRING)
                         .arg(ODBC_DB_FILE_NAME)
                         .arg(_user)
                         .arg(_password));

    return _db->isValid();
}

bool ODBCDatabase::open()
{
    if (!_db)
        return false;

    return _db->open();
}

void ODBCDatabase::close()
{
    if (_db)
        _db->close();
}

bool ODBCDatabase::isConnected()
{
    if (!_db)
        return false;

    return _db->isValid();
}

bool ODBCDatabase::isOpened()
{
    if (!_db)
        return false;

    return _db->isOpen();
}

string ODBCDatabase::error()
{
    if (!_db)
        return string();

    return _db->lastError().text().toStdString();
}

void ODBCDatabase::setDatabaseName(string name)
{
    if (!_db)
        return;

    _db->setDatabaseName(name.c_str());
}

string ODBCDatabase::getDatabaseName()
{
    if (!_db)
        return string();

    return _db->databaseName().toStdString();
}

void ODBCDatabase::setUser(string user)
{
    _user = user.c_str();
}

void ODBCDatabase::setPassword(string password)
{
    _password = password.c_str();
}

void* ODBCDatabase::databaseInfo()
{
    return (void*)_db;
}
