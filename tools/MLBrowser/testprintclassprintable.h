#ifndef TESTPRINTCLASSPRINTABLE_H
#define TESTPRINTCLASSPRINTABLE_H

#include "sscore/print/ssprintable.h"
#include "testprintclass.h"


#define TESTPRINTCLASS_CLASSNAME ("TestPrintClass")


class TestPrintClassPrintable : public SSPrintable
{
public:

    enum CLASS_CONTENT {
        CLASS_HEADER = 0,
        CLASS_TITLE,
        CLASS_OBJECT,
        CLASS_DATE,
        CLASS_ITEMS,

        CLASS_ITEMS_COUNT,

        CLASS_UNKNOWN
    };

    TestPrintClassPrintable(const TestPrintClass* obj);

    virtual bool traversePrintable(SSPrintableCallback* callback);
    virtual string getPrintableItemTitle(int type, int index = -1);
    virtual string getPrintableItemValue(int type, int index = -1);
    virtual string getPrintableName() const;

private:
    const TestPrintClass* _object;
};

#endif // TESTPRINTCLASSPRINTABLE_H
