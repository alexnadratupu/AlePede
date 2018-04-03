#ifndef CONVOLUTIONQWIDGET_H
#define CONVOLUTIONQWIDGET_H

#include <QWidget>
#include "mainwindow.h"

class MainWindow;

//namespace Ui {
//class ConvolutionQwidget;
//}

class ConvolutionQwidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConvolutionQwidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~ConvolutionQwidget();

private slots:

    void on_spinBox_valueChanged(int arg1);
    void on_pushButton_clicked();

private:
    ConvolutionQwidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
    QLineEdit ***qLineEditMatrix;
    int kernelSize;

    void deleteTable();
};

#endif // CONVOLUTIONQWIDGET_H
