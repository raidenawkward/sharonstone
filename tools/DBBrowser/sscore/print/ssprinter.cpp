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

bool SSPrinter::openOptionDialog()
{
    return onOpenOptionDialog();
}

bool SSPrinter::print()
{
    if (!onPrePrint())
        return false;

    if (!onPrint())
        return false;

    onFinishPrint();

    return true;
}

void SSPrinter::preview()
{
    if (!onPrePreview())
        return;

    if (!onPreview())
        return;

    onFinishPreview();

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

    return _printImpl->printDoc();
}

void SSPrinter::onFinishPrint()
{
    if (!_printImpl)
        return;

    _printImpl->fihishPrint();
}

bool SSPrinter::onPrePreview()
{
    if (!_printImpl)
        return false;

    return _printImpl->preparePreview();
}

bool SSPrinter::onPreview()
{
    if (!_printImpl)
        return false;

    return _printImpl->preview();
}

void SSPrinter::onFinishPreview()
{
    if (!_printImpl)
        return;

    _printImpl->finishPreview();
}

bool SSPrinter::onOpenOptionDialog()
{
    if (!_printImpl)
        return false;

    return _printImpl->openOptionDialog();
}

SSPrintImpl* SSPrinter::getPrintImpl()
{
    return _printImpl;
}

void SSPrinter::setPrintImpl(SSPrintImpl* impl)
{
    _printImpl = impl;
}
