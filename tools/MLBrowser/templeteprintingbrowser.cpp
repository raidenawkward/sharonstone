#include "templeteprintingbrowser.h"

#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QFile>
#include <QRegularExpression>

TempletePrintingBrowser::TempletePrintingBrowser(QWidget *parent) :
    QTextBrowser(parent)
{
    _printer = NULL;
    _printable = NULL;

    _tagPrefix = TEMPLETEPRINTINGBROWSER_DEFAULT_TAG_PREFIX;
    _tagSuffix = TEMPLETEPRINTINGBROWSER_DEFAULT_TAG_SUFFIX;
}

TempletePrintingBrowser::~TempletePrintingBrowser()
{
    if (_printer)
        delete _printer;
}

bool TempletePrintingBrowser::loadPrintable(const SSPrintable* printable)
{
    _printable = printable;

    return true;
}

/*
 * methods from SSTemplete
 */
bool TempletePrintingBrowser::loadTemplete(const char* path)
{
    QFile file(path);

    if (!file.open(QFile::ReadOnly)) {
        return false;
    }

    _templeteContent = QString(file.readAll().constData());

    this->setHtml(_templeteContent);

    return true;
}

bool TempletePrintingBrowser::setTagValue(const char* tag, const char* value)
{
    QString before;
    before.append(_tagPrefix).append(QString(tag)).append(_tagSuffix);

    _templeteContent.replace(before, QString(value));

    return true;
}

bool TempletePrintingBrowser::appendTagValue(const char* tag, const char* value)
{
    QString before;
    before.append(_tagPrefix).append(QString(tag)).append(_tagSuffix);

    QString after = QString(value) + before;

    _templeteContent.replace(before, after);

    return true;
}

bool TempletePrintingBrowser::isTagExist(const char* tag)
{
    QString tagStr;
    tagStr.append(_tagPrefix).append(QString(tag)).append(_tagSuffix);

    return _templeteContent.contains(tagStr);
}

const char* TempletePrintingBrowser::getNextTag()
{
    return NULL;
}

void TempletePrintingBrowser::clearAllTags()
{
    QString expStr;
    expStr.append(_tagPrefix).append("*").append(_tagSuffix);

    QRegularExpression exp(expStr);

    _templeteContent.replace(exp, "");
}

void TempletePrintingBrowser::setTagPrefix(const char* prefix)
{
    _tagPrefix = QString(prefix);
}

void TempletePrintingBrowser::setTagSuffix(const char* suffix)
{
    _tagSuffix = QString(suffix);
}

/*
 * methods from SSPrintImpl
 */
bool TempletePrintingBrowser::preparePrint()
{
    if (_printer)
        delete _printer;

    _printer = new QPrinter();
    _printer->setPageSize(QPrinter::A4);
    _printer->setPageMargins(0, 0, 0, 0, QPrinter::Millimeter);

    return true;
}

bool TempletePrintingBrowser::startPrint()
{
    if (!_printer)
        return false;

    QPrintDialog dialog(_printer, 0);
    dialog.setModal(true);

    if (dialog.exec() != QDialog::Accepted)
        return false;

    this->print(_printer);

    return true;
}

void TempletePrintingBrowser::fihishPrint()
{

}

void TempletePrintingBrowser::onPreviewRequest(QPrinter* printer)
{
    this->print(printer);
}

void TempletePrintingBrowser::preview()
{
    QPrintPreviewDialog dialog(_printer, 0);
    dialog.setModal(true);

    connect(&dialog, SIGNAL(paintRequested(QPrinter *)), this, SLOT(onPreviewRequest(QPrinter *)));
    dialog.exec();
}
