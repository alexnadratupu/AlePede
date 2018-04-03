#ifndef CANNYWIDGET_H
#define CANNYWIDGET_H

#include <QWidget>
#include <mainwindow.h>


//namespace Ui {
//    class CannyWidget;
//}

class CannyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CannyWidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~CannyWidget();

private slots:
    void on_buttonEdgeCanny_clicked();

    void on_spinBoxDown_valueChanged(int );

    void on_spinBoxHigh_valueChanged(int );

private:
    CannyWidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
};

#endif // CANNYWIDGET_H
