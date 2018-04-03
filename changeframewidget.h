#ifndef CHANGEFRAMEWIDGET_H
#define CHANGEFRAMEWIDGET_H

#include <QWidget>
#include <mainwindow.h>

//namespace Ui {
//    class ChangeFrameWidget;
//}

class ChangeFrameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeFrameWidget(QWidget *parent,MainController *controller, MainWindow *window);
    ~ChangeFrameWidget();
    void setMaxFrame(int value);

private slots:
    void on_sliderFrame_valueChanged(int value);

private:
    ChangeFrameWidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;

};

#endif // CHANGEFRAMEWIDGET_H
