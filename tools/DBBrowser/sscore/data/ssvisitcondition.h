/**
 * [CLASS]
 * class for external condition for visiting.
 * for db system,
 * it may present one or more of:
 * 1. range
 * 2. distinct
 * 3. order by
 */

#ifndef SSVISITCONDITION_H
#define SSVISITCONDITION_H

#include "sscore/data/ssdataprovider.h"
#include <string.h>

using namespace std;

class SSVisitCondition
{
public:

    enum ORDER_TYPE {
        ORDER_ASC = 0,
        ORDER_DESC,
        ORDER_ANY
    };

    enum COMPARE_TYPE {
        CMP_EQUAL = 0,
        CMP_NOT_EQUAL,
        CMP_GREATE_THAN,
        CMP_GREATE_EQUEAL,
        CMP_LESS_THAN,
        CMP_LESS_EQUAL,
        CMP_ANY
    };

    virtual void setVisitType(int type) = 0;
    virtual int getVisitType() = 0;

    virtual void appendRangeCondition(string condName
                                      , string min
                                      , COMPARE_TYPE minType
                                      , string max
                                      , COMPARE_TYPE maxTypw) = 0;
    virtual void appendCondition(string condName, string value, COMPARE_TYPE type) = 0;
    virtual void appendOrderBy(string field, ORDER_TYPE type) = 0;
    virtual void appendDataProvider(SSDataProvider* provider) = 0;

    virtual string toString() = 0;
    virtual SSDataProvider* getDataProvider() { return _data; }

protected:
    SSVisitCondition(SSDataProvider* data) { _data = data; }

private:
    SSDataProvider* _data;
};

#endif // SSVISITCONDITION_H
