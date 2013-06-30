#ifndef SSPRINTIMPL_H
#define SSPRINTIMPL_H

#include "sscore/print/ssprintable.h"
#include <string>

using namespace std;

class SSPrintImpl
{
public:
    virtual bool preparePrint() = 0;
    virtual bool printDoc() = 0;
    virtual void fihishPrint() = 0;

    virtual bool preparePreview() = 0;
    virtual bool preview() = 0;
    virtual void finishPreview() = 0;

    virtual bool openOptionDialog() = 0;

    virtual bool loadPrintable(SSPrintable* printable) = 0;

protected:
    SSPrintImpl() {}
};

#endif // SSPRINTIMPL_H
