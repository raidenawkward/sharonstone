/**
 * [CLASS]
 * for data visit query executing
 * based on certain platform
 */

#ifndef SSDATAVISITCMD_H
#define SSDATAVISITCMD_H


#include "sscore/data/ssdatavisitor.h"
#include "sscore/data/ssdataprovider.h"
#include "sscore/data/ssvisitcondition.h"


#include <string>
#include <vector>

using namespace std;


class SSDataVisitCmd
{
public:
    SSDataVisitCmd(SSDataVisitor* visitor) {
        _condition = NULL;
        _visitor = visitor;
    }

    virtual int exec() {
        if (!_visitor)
            return 0;

        return _visitor->visit(this->getQuery());
    }

    virtual void setQuery(string query) { _query = query; }
    virtual void setCondition(SSVisitCondition* cond) {
        _query = cond->toString();
    }
    virtual SSVisitCondition* getCondition() { return _condition; }

    virtual string getQuery() { return _query; }
    virtual void setDataVisitor(SSDataVisitor* visitor) { _visitor = visitor; }
    virtual SSDataVisitor* getDataVisitor() { return _visitor; }


private:
    string _query;
    SSDataVisitor* _visitor;
    SSVisitCondition* _condition;
};

#endif // SSDATAVISITCMD_H
