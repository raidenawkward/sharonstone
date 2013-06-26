#include "testprintclassprintable.h"
#include <QDebug>
#include <string.h>

TestPrintClassPrintable::TestPrintClassPrintable(const TestPrintClass* obj)
{
    _object = obj;
}


string TestPrintClassPrintable::getPrintableName() const
{
    return TESTPRINTCLASS_CLASSNAME;
}

bool TestPrintClassPrintable::traversePrintable(SSPrintableCallback* callback)
{
    if (!callback)
        return false;

    if (!callback->onPrintablePrint(CLASS_HEADER, getPrintableItemTitle(CLASS_HEADER), getPrintableItemValue(CLASS_HEADER)))
        return false;

    if (!callback->onPrintablePrint(CLASS_TITLE, getPrintableItemTitle(CLASS_TITLE), getPrintableItemValue(CLASS_TITLE)))
        return false;

    if (!callback->onPrintablePrint(CLASS_OBJECT, getPrintableItemTitle(CLASS_OBJECT), getPrintableItemValue(CLASS_OBJECT)))
        return false;

    if (!callback->onPrintablePrint(CLASS_DATE, getPrintableItemTitle(CLASS_DATE), getPrintableItemValue(CLASS_DATE)))
        return false;

    for (int i = 0; i < _object->getItemCount(); ++i) {
        if (!callback->onPrintablePrint(CLASS_ITEMS, getPrintableItemTitle(CLASS_ITEMS, i), getPrintableItemValue(CLASS_ITEMS, i)))
            return false;
    }

    return true;
}

string TestPrintClassPrintable::getPrintableItemTitle(int type, int index)
{
    if (!_object)
        return NULL;

    switch ((CLASS_CONTENT)type) {
    case CLASS_HEADER:
        return "header";
    case CLASS_TITLE:
        return "title";
    case CLASS_OBJECT:
        return "object";
    case CLASS_DATE:
        return "date";
    case CLASS_ITEMS:
        return QString("item.").append(QString::number(index)).toStdString().c_str();
    case CLASS_ITEMS_COUNT:
        return "item count";
    case CLASS_UNKNOWN:
    default:
        break;
    }

    return NULL;
}

string TestPrintClassPrintable::getPrintableItemValue(int type, int index)
{
    QString res;

    if (!_object)
        return NULL;

    switch ((CLASS_CONTENT)type) {
    case CLASS_HEADER:
        res = _object->getHeader();
        break;
    case CLASS_TITLE:
        res = _object->getTitle();
        break;
    case CLASS_OBJECT:
        res = _object->getObject();
        break;
    case CLASS_DATE:
        res = _object->getDate().toString("yyyy-M-d");
        break;
    case CLASS_ITEMS:
        res = _object->getItem(index);
        break;
    case CLASS_ITEMS_COUNT:
        res = QString::number(_object->getItemCount());
        break;
    case CLASS_UNKNOWN:
    default:
        res = "unknown";
        break;
    }

    return res.toStdString();
}
