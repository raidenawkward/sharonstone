#include "templeteprintingbrowser.h"

#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QFile>
#include <QRegularExpression>
#include <QDebug>
#include <string.h>

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

bool TempletePrintingBrowser::loadPrintable(SSPrintable* printable)
{
    _printable = printable;

    if (!_printable)
        return false;

    _printable->traversePrintable(this);

    clearAllTags();

    this->setHtml(_templeteContent);

    return true;
}

bool TempletePrintingBrowser::onPrintablePrint(int ,string title, string v)
{
    QString tag = QString(title.c_str());
    QString value = QString(v.c_str());

    qDebug()<<"tag: "<<tag<<" value: "<<value;

    if (title.empty())
        return true;

    if (!tag.contains(".")) {
        setTagValue(tag.toUtf8().constData(), value.toUtf8().constData());
    } else {
        int dotIndex = tag.indexOf(".");
        QString tagInTemplete = tag.mid(0, dotIndex);

        appendTagValue(tagInTemplete.toStdString(), value.toStdString());
        appendTagValue(tagInTemplete.toStdString(), "<br>");
    }

    return true;
}

/*
 * methods from SSTemplete
 */
bool TempletePrintingBrowser::loadTemplete(string path)
{
    QFile file(path.c_str());

    if (!file.open(QFile::ReadOnly)) {
        return false;
    }

    _templeteContent = QString(file.readAll().constData());

    this->setHtml(_templeteContent);

    return true;
}

bool TempletePrintingBrowser::setTagValue(string tag, string value)
{
    QString before;
    before.append(_tagPrefix).append(QString(tag.c_str())).append(_tagSuffix);

    _templeteContent.replace(before, QString(value.c_str()));

    return true;
}

bool TempletePrintingBrowser::appendTagValue(string tag, string value)
{
    QString before;
    before.append(_tagPrefix).append(QString(tag.c_str())).append(_tagSuffix);

    QString after = QString(value.c_str()) + before;

    _templeteContent.replace(before, after);

    return true;
}

bool TempletePrintingBrowser::isTagExist(string tag)
{
    QString tagStr;
    tagStr.append(_tagPrefix).append(QString(tag.c_str())).append(_tagSuffix);

    return _templeteContent.contains(tagStr);
}

string TempletePrintingBrowser::getNextTag()
{
    return NULL;
}

void TempletePrintingBrowser::clearAllTags()
{
    while(_templeteContent.contains(_tagPrefix)) {
        int start = _templeteContent.indexOf(_tagPrefix);
        if (start < 0)
            break;

        int end = _templeteContent.indexOf(_tagSuffix, start);
        if (end < 0)
            break;

        _templeteContent.replace(start, end - start + 1, "");
    }
}

void TempletePrintingBrowser::setTagPrefix(string prefix)
{
    _tagPrefix = QString(prefix.c_str());
}

void TempletePrintingBrowser::setTagSuffix(string suffix)
{
    _tagSuffix = QString(suffix.c_str());
}

/*
 * methods from SSPrintImpl
 */
bool TempletePrintingBrowser::preparePrint()
{
    if (!_printer) {
        _printer = new QPrinter();
        _printer->setPageSize(QPrinter::A4);
        _printer->setPageMargins(0, 0, 0, 0, QPrinter::Millimeter);
    }

    return true;
}

bool TempletePrintingBrowser::printDoc()
{
    if (!_printer)
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

bool TempletePrintingBrowser::preparePreview()
{
    return preparePrint();
}

bool TempletePrintingBrowser::preview()
{
    QPrintPreviewDialog dialog(_printer, 0);
    dialog.setModal(true);

    connect(&dialog, SIGNAL(paintRequested(QPrinter *)), this, SLOT(onPreviewRequest(QPrinter *)));
    dialog.exec();

    return true;
}

void TempletePrintingBrowser::finishPreview()
{

}

bool TempletePrintingBrowser::openOptionDialog()
{
    if (!_printer)
        preparePrint();

    QPrintDialog dialog(_printer, 0);
    dialog.setModal(true);

    return dialog.exec() == QDialog::Accepted;
}
