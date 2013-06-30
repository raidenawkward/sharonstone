/**
 * [INTERFACE]
 * provides add, delete, update and select
 * for sql like, or other data restoring system
 */

#ifndef SSDATAVISITOR_H
#define SSDATAVISITOR_H

#include "sscore/data/ssdatabase.h"
#include "sscore/data/ssdataprovider.h"
#include "sscore/data/ssvisitcondition.h"

#include <string>
#include <vector>

using namespace std;


class SSDataVisitor
{
public:

    virtual int visit(string cmd) = 0;
    virtual vector<SSDataProvider*> visitResult(SSDataProvider* prototype) = 0;
    virtual void clearResult() = 0;

    virtual string error() = 0;

    /// for database
    virtual SSDatabase* getDatabase() { return _db; }
    virtual void setDatabase(SSDatabase* db) { _db = db; }

protected:
    SSDataVisitor(SSDatabase* db) { _db = db; }

private:
    SSDatabase* _db;
};

#endif // SSDATAVISITOR_H
