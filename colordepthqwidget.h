#ifndef COLORDEPTHQWIDGET_H
#define COLORDEPTHQWIDGET_H

#include <QWidget>
#include "mainwindow.h"

//class   MainWindow;
class MainWindow;
//namespace Ui {
//class ColorDepthQwidget;
//}

class ColorDepthQwidget : public QWidget
{
    Q_OBJECT
    //MainWindow *window= new MainWindow();
public:
    explicit ColorDepthQwidget(QWidget *parent, MainController *controller, MainWindow *window, int ColorDensity);
    ~ColorDepthQwidget();

private slots:
    void on_pushButton_clicked();

private:
    ColorDepthQwidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
};

#endif // COLORDEPTHQWIDGET_H
