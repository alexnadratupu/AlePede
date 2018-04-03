#include "cannywidget.h"
#include "ui_cannywidget.h"

CannyWidget::CannyWidget(QWidget *        parent,
                         MainController * controller,
                         MainWindow *     window):
    QWidget(parent),
    ui(new Ui::CannyWidget)
{
    ui -> setupUi(this);

    mainwindow     = window;
    mainController = controller;
}

CannyWidget::~CannyWidget()
{
    delete ui;
}

void CannyWidget::on_buttonEdgeCanny_clicked()
{
    if (mainController -> isThereAnUploadedImage())
    {
        int thresholdDown = ui -> spinBoxDown -> value();
        int thresholdHigh = ui -> spinBoxHigh -> value();

        mainController -> edgeDetectorCanny(thresholdHigh, thresholdDown);
        mainwindow -> displayResults(mainController -> getQImage());
        mainwindow -> ShowHistogram();
    }
    else
    {
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}

void CannyWidget::on_spinBoxDown_valueChanged(int i)
{
    int thresholdHigh = ui -> spinBoxHigh -> value();

    if (thresholdHigh < i)
    {
        ui -> spinBoxHigh -> setValue(i);
    }
}

void CannyWidget::on_spinBoxHigh_valueChanged(int i)
{
    int thresholdDown = ui -> spinBoxDown -> value();

    if (thresholdDown > i)
    {
        ui -> spinBoxDown -> setValue(i);
    }
}
