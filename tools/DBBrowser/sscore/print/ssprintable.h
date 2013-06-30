#ifndef SSPRINTABLE_H
#define SSPRINTABLE_H

#include <stdlib.h>
#include <string>

using namespace std;

class SSPrintable
{
public:

    class SSPrintableCallback {
    public:
        virtual bool onPrintablePrint(int type, string title, string value) = 0;
    };

    virtual bool traversePrintable(SSPrintableCallback* callback) { return callback; }

    virtual string getPrintableItemTitle(int type, int index = -1) = 0;
    virtual string getPrintableItemValue(int type, int index = -1) = 0;

    virtual string getPrintableName() const = 0;

protected:
    SSPrintable() {}
};

#endif // SSPRINTABLE_H
