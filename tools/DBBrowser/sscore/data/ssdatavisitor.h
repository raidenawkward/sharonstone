/*
 * [INTERFACE]
 * provides add, delete, update and select
 * for sql like, or other data restoring system
 */

#ifndef SSDATAVISITOR_H
#define SSDATAVISITOR_H

#include "sscore/data/ssdatabase.h"
#include "sscore/data/ssdataprovider.h"
#include <string>
#include <vector>

using namespace std;


typedef SSDataProvider SSVisitCondition;


class SSDataVisitor
{
public:
    /// data operate interface
    virtual bool add(SSVisitCondition* dest) = 0;
    virtual bool remove(SSVisitCondition* cond) = 0;
    virtual bool update(SSVisitCondition* cond, SSVisitCondition* dest) = 0;
    // will select all if cond == NULL
    virtual vector<SSDataProvider*> select(SSVisitCondition* cond = NULL) = 0;
    //! danger! DO not override if unnecessary
    virtual bool clear() { return false; }

    virtual int count(SSVisitCondition* cond = NULL) = 0;
    // may be similar to select()
    virtual bool exist(SSVisitCondition* dest) = 0;

    virtual string error() = 0;

    /// for database
    virtual SSDatabase* getDatabase() { return _db; }
    virtual void setDatabase(SSDatabase* db) { _db = db; }

protected:
    SSDataVisitor() { _db = NULL; }

private:
    SSDatabase* _db;
};

#endif // SSDATAVISITOR_H
