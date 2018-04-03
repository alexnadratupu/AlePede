#ifndef SOBELQWIDGET_H
#define SOBELQWIDGET_H

#include <QWidget>
#include "mainwindow.h"

class   MainWindow;

//namespace Ui {
//class SobelQwidget;
//}

class SobelQwidget : public QWidget
{
    Q_OBJECT

public:
    explicit SobelQwidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~SobelQwidget();

private slots:
    void on_sobelHorizontally_clicked();

    void on_sobelVertically_clicked();

    void on_sobelFilter_clicked();

private:
   SobelQwidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
};

#endif // SOBELQWIDGET_H
