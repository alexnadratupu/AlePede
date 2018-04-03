#ifndef THRESHOLDQWIDGET_H
#define THRESHOLDQWIDGET_H

#include <QWidget>
#include "mainwindow.h"

class   MainWindow;

//namespace Ui {
//class ThresholdQwidget;
//}

class ThresholdQwidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThresholdQwidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~ThresholdQwidget();

private slots:

    void on_manualSegPushButton_clicked();

    void on_isodataSegPushButton_clicked();

    void on_otsuSegPushButton_clicked();

private:
    ThresholdQwidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
};


#endif // THRESHOLDQWIDGET_H
