#include "qtsqlcondition.h"

QtSqlCondition::QtSqlCondition(SSDataProvider* data)
    : SSVisitCondition(data)
    , _type(SQL_UNKNOWN)
    , _appendedProvider(NULL)
{
}

QtSqlCondition::~QtSqlCondition()
{

}

void QtSqlCondition::setVisitType(int type)
{
    _type = (SQL_CONDITION_TYPE)type;
}

int QtSqlCondition::getVisitType()
{
    return (int)_type;
}

QString QtSqlCondition::getCompareString(COMPARE_TYPE type)
{
    QString res;

    switch (type) {
    case CMP_EQUAL:
        res = "=";
        break;
    case CMP_NOT_EQUAL:
        res = "<>";
        break;
    case CMP_GREATE_THAN:
        res = ">";
        break;
    case CMP_GREATE_EQUEAL:
        res = ">=";
        break;
    case CMP_LESS_THAN:
        res = "<";
        break;
    case CMP_LESS_EQUAL:
        res = "<=";
        break;
    case CMP_ANY:
    default:
        res = "=";
        break;
    }

    return res;
}

QString QtSqlCondition::loadProviderString(SSDataProvider* provider)
{
    QString where;

    if (!provider)
        return where;

    int count = provider->getDataMemberCount();

    for (int i = 0; i < count; ++i) {
        QString title = provider->getDataMemberName(i).c_str();
        QString value = provider->getDataMemberValue(i).c_str();

        if (!value.isEmpty() && !title.isEmpty()) {
            if (!where.isEmpty())
                where.append(" and ");

            where.append(title)
                    .append("='")
                    .append(value)
                    .append("'");
        }
    }

    return where;
}

void QtSqlCondition::appendRangeCondition(string condName
                              , string min
                              , COMPARE_TYPE minType
                              , string max
                              , COMPARE_TYPE maxType)
{
    QString cond = QString(condName.c_str());
    cond.append(getCompareString(minType));
    cond.append("'").append(min.c_str()).append("'");
    cond.append(" and ");
    cond.append(condName.c_str());
    cond.append(getCompareString(maxType));
    cond.append("'").append(max.c_str()).append("'");

    _rangeList.append(cond);
}

void QtSqlCondition::appendCondition(string condName, string value, COMPARE_TYPE type)
{
    QString cond = QString(condName.c_str());
    cond.append(getCompareString(type));
    cond.append("'").append(value.c_str()).append("'");

    _extCond.append(cond);
}

void QtSqlCondition::appendOrderBy(string field, ORDER_TYPE type)\
{
    QString cond = QString(field.c_str());

    switch (type) {
    case ORDER_ASC:
        cond.append(" ASC");
        break;
    case ORDER_DESC:
        cond.append(" DESC");
    case ORDER_ANY:
    default:
        return;
    }

    _orderBy.append(cond);
}

void QtSqlCondition::appendDataProvider(SSDataProvider* provider)
{
    _appendedProvider = provider;
}

QString QtSqlCondition::getWhereString()
{
    if (_type == SQL_INSERT)
        return QString();

    SSDataProvider* data = this->getDataProvider();

    QString where = loadProviderString(data);

    for (int i = 0; i < _rangeList.count(); ++i) {
        QString cond = _rangeList.at(i);

        if (!where.isEmpty())
            where.append(" and ");
        where.append(cond);
    }

    for (int i = 0; i < _extCond.count(); ++i) {
        QString cond = _extCond.at(i);

        if (!where.isEmpty())
            where.append(" and ");
        where.append(cond);
    }

    where.prepend(" where ");
    return where;
}

QString QtSqlCondition::getOptionString()
{
    QString opt;

    // order by
    for (int i = 0; i < _orderBy.count(); ++i) {
        QString cond = _orderBy.at(i);

        if (!opt.isEmpty())
            opt.append(",");
        opt.append(cond);
    }
    opt.prepend(" order by ");

    return opt;
}

QString QtSqlCondition::toInsertString()
{
    SSDataProvider* data = this->getDataProvider();
    if (!data)
        return QString();

    QString command = "insert into ";
    command.append(data->getDataContainerName().c_str());

    QString titleList;
    QString valueList;
    int count = data->getDataMemberCount();

    for (int i = 0; i < count; ++i) {
        QString title = data->getDataMemberName(i).c_str();
        QString value = data->getDataMemberValue(i).c_str();

        if (!value.isEmpty() && !title.isEmpty()) {
            if (i)
                titleList.append(",");

            titleList.append(title);

            if (i)
                valueList.append(",");
            valueList.append("'").append(value).append("'");
        }
    }

    command.append(" (").append(titleList).append(") ");
    command.append("values (").append(valueList).append(");");

    return command;
}

QString QtSqlCondition::toDeleteString()
{
    SSDataProvider* data = this->getDataProvider();

    QString command = QString("delete from ")
                .append(data->getDataContainerName().c_str());

    return command;
}

QString QtSqlCondition::toUpdateString()
{
    SSDataProvider* data = this->getDataProvider();
    if (!data)
        return QString();

    if (!_appendedProvider)
        return QString();

    QString command = QString("update ").append(" ").append(data->getDataContainerName().c_str());
    QString set;
    int count = 0;

    count = _appendedProvider->getDataMemberCount();
    for (int i = 0; i < count; ++i) {
        QString title = _appendedProvider->getDataMemberName(i).c_str();
        QString value = _appendedProvider->getDataMemberValue(i).c_str();

        if (!value.isEmpty() && !title.isEmpty()) {
            if (i)
                set.append(",");

            set.append(title)
                    .append("='")
                    .append(value)
                    .append("'");
        }
    }
    command.append(" set ").append(set);

    return command;
}

QString QtSqlCondition::toSelectString()
{
    SSDataProvider* data = this->getDataProvider();

    QString command = QString("select * from ").append(data->getDataContainerName().c_str());

    return command;
}

QString QtSqlCondition::toSelectDistinctString()
{
    SSDataProvider* data = this->getDataProvider();

    QString command = QString("select distinct * from ").append(data->getDataContainerName().c_str());

    return command;
}

QString QtSqlCondition::toSelectCountString()
{
    SSDataProvider* data = this->getDataProvider();

    QString command = QString("select count(*) from ").append(data->getDataContainerName().c_str());

    return command;
}

string QtSqlCondition::toString()
{
    QString cmd;

    SSDataProvider* data = this->getDataProvider();
    if (!data)
        return cmd.toStdString();

    switch (_type) {
    case SQL_INSERT:
        cmd = toInsertString();
        break;
    case SQL_DELETE:
        cmd = toDeleteString();
        break;
    case SQL_UPDATE:
        cmd = toUpdateString();
        break;
    case SQL_SELECT:
        cmd = toSelectString();
        break;
    case SQL_SELECT_DISTINCT:
        cmd = toSelectDistinctString();
        break;
    case SQL_COUNT:
    case SQL_EXIST:
        cmd = toSelectCountString();
        break;
    case SQL_UNKNOWN:
    default:
        break;
    }

    if (cmd.isEmpty())
        return cmd.toStdString();

    QString where = this->getWhereString();
    if (where.isEmpty())
        return where.toStdString();

    cmd.append(where);

    cmd.append(this->getOptionString());

    return cmd.toStdString();
}
