#ifndef SSPRINTER_H
#define SSPRINTER_H

#include "ssprintimpl.h"

class SSPrinter
{
public:
    SSPrinter(SSPrintImpl *impl);
    virtual ~SSPrinter();

    virtual bool print();
    virtual void preview();

protected:
    SSPrinter();

    virtual bool onPrePrint();
    virtual bool onPrint();
    virtual void onPrintDone();
    virtual void onPreview();

    SSPrintImpl* getPrintImpl();
    void setPrintImpl(SSPrintImpl* impl);

private:
    SSPrintImpl* _printImpl;
};

#endif // SSPRINTER_H
