#ifndef QTDATAVISITOR_H
#define QTDATAVISITOR_H

#include "sscore/data/ssdatavisitor.h"
#include "sscore/data/ssdatabase.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlResult>
#include <QtSql/QSqlField>


class QtDataVisitor : public SSDataVisitor
{
public:
    QtDataVisitor();
    QtDataVisitor(SSDatabase* db);
    virtual ~QtDataVisitor();

    /// data operate interface
    virtual bool add(SSVisitCondition* dest);
    virtual bool remove(SSVisitCondition* cond);
    virtual bool update(SSVisitCondition* cond, SSVisitCondition* dest);
    // will select all if cond == NULL
    virtual vector<SSDataProvider*> select(SSVisitCondition* cond = NULL);

    virtual int count(SSVisitCondition* cond = NULL);
    // may be similar to select()
    virtual bool exist(SSVisitCondition* dest);

    virtual string error();

    virtual void setDatabase(SSDatabase* db);

    static QString loadWhereFromCond(SSVisitCondition* cond);
private:
    QSqlQuery* _query;
};

#endif // QTDATAVISITOR_H
