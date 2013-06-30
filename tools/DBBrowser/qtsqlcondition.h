#ifndef QTSQLCONDITION_H
#define QTSQLCONDITION_H

#include <QString>
#include <QStringList>
#include "sscore/data/ssvisitcondition.h"
#include "sscore/data/ssdataprovider.h"

class QtSqlCondition : public SSVisitCondition
{
public:
    enum SQL_CONDITION_TYPE {
        SQL_INSERT = 0,
        SQL_DELETE,
        SQL_UPDATE,
        SQL_SELECT,
        SQL_SELECT_DISTINCT,
        SQL_COUNT,
        SQL_EXIST,

        SQL_UNKNOWN
    };

    QtSqlCondition(SSDataProvider* data);
    virtual ~QtSqlCondition();

    virtual void setVisitType(int type);
    virtual int getVisitType();

    virtual void appendRangeCondition(string condName
                                      , string min
                                      , COMPARE_TYPE minType
                                      , string max
                                      , COMPARE_TYPE maxType);
    virtual void appendCondition(string condName, string value, COMPARE_TYPE type);
    virtual void appendOrderBy(string field, ORDER_TYPE type);
    virtual void appendDataProvider(SSDataProvider* provider);

    virtual string toString();

protected:
    static QString getCompareString(COMPARE_TYPE type);
    virtual QString loadProviderString(SSDataProvider* provider);

    virtual QString toInsertString();
    virtual QString toDeleteString();
    virtual QString toUpdateString();
    virtual QString toSelectString();
    virtual QString toSelectDistinctString();
    virtual QString toSelectCountString();

    virtual QString getWhereString();
    virtual QString getOptionString();

private:
    SQL_CONDITION_TYPE _type;
    SSDataProvider* _appendedProvider;
    QStringList _rangeList;
    QStringList _extCond;
    QStringList _orderBy;
};

#endif // QTSQLCONDITION_H
