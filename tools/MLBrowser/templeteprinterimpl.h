#ifndef TEMPLETEPRINTERIMPL_H
#define TEMPLETEPRINTERIMPL_H

#include "print/ssprintimpl.h"
#include "print/ssprintable.h"

class TempletePrinterImpl : public SSPrintImpl
{
public:
    TempletePrinterImpl(const SSPrintable* printable);
    virtual ~TempletePrinterImpl();

    virtual bool preparePrint();
    virtual bool print();
    virtual void fihishPrint();
    virtual void preview();

    SSPrintable* printable() const;

private:
    const SSPrintable* _printable;
};

#endif // TEMPLETEPRINTERIMPL_H
