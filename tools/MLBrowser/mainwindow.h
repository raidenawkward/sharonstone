#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPrinter>

#include "sscore/print/ssprinter.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadFile(const QString path);
    bool prePrint();
    void print();

private slots:
    void on_actionAbout_triggered();
    void on_actionOpen_triggered();
    void on_actionRefresh_triggered();
    void on_actionPrint_triggered();
    void on_actionPreview_triggered();
    void on_actionExit_triggered();
    void on_actionFont_triggered();
    void on_actionTest_triggered();

private:
    Ui::MainWindow *ui;
    QString _file;
    SSPrinter* _printer;
};

#endif // MAINWINDOW_H
