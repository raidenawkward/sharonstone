#ifndef QTSQLDBVISITOR_H
#define QTSQLDBVISITOR_H

#include "sscore/data/ssdatavisitcmd.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlResult>
#include <QtSql/QSqlField>

class QtSqlDBVisitor : public SSDataVisitor
{
public:
    QtSqlDBVisitor(SSDatabase* db);
    virtual ~QtSqlDBVisitor();

    virtual int visit(string cmd) = 0;
    virtual vector<SSDataProvider*> visitResult(SSDataProvider* prototype) = 0;
    virtual void clearResult();

    virtual string error();

    virtual void setDatabase(SSDatabase* db);

private:
    QSqlQuery* _query;
    SSDataVisitCmd* _cmd;
};

#endif // QTSQLDBVISITOR_H
