#ifndef SSPRINTIMPL_H
#define SSPRINTIMPL_H

class SSPrintImpl
{
public:
    virtual bool preparePrint() = 0;
    virtual bool startPrint() = 0;
    virtual void fihishPrint() = 0;
    virtual void preview() = 0;

protected:
    SSPrintImpl() {}
};

#endif // SSPRINTIMPL_H
