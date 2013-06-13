#include "ssprinter.h"
#include <stdlib.h>

SSPrinter::SSPrinter(SSPrintImpl *impl)
    : _printImpl(impl)
{
}

SSPrinter::SSPrinter()
    : _printImpl(NULL)
{
}

SSPrinter::~SSPrinter()
{
}

bool SSPrinter::print()
{
    if (!onPrePrint())
        return false;

    if (!onPrint())
        return false;

    onPrintDone();

    return true;
}

void SSPrinter::preview()
{
    onPreview();
}

bool SSPrinter::onPrePrint()
{
    if (!_printImpl)
        return false;

    return _printImpl->preparePrint();
}

bool SSPrinter::onPrint()
{
    if (!_printImpl)
        return false;

    return _printImpl->startPrint();
}

void SSPrinter::onPrintDone()
{
    if (!_printImpl)
        return;

    _printImpl->fihishPrint();
}

void SSPrinter::onPreview()
{
    if (!_printImpl)
        return;

    _printImpl->preview();
}

SSPrintImpl* SSPrinter::getPrintImpl()
{
    return _printImpl;
}

void SSPrinter::setPrintImpl(SSPrintImpl* impl)
{
    _printImpl = impl;
}
