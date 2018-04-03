#include "thresholdqwidget.h"
#include "ui_thresholdqwidget.h"

ThresholdQwidget::ThresholdQwidget(QWidget *        parent,
                                   MainController * controller,
                                   MainWindow *     window):
    QWidget(parent),
    ui(new Ui::ThresholdQwidget)
{
    ui -> setupUi(this);

    mainwindow     = window;
    mainController = controller;

    ui -> verticalSlider -> setMaximum(mainController -> getImage() -> getColorDepth());
}

ThresholdQwidget::~ThresholdQwidget()
{
    delete ui;
}

void ThresholdQwidget::on_isodataSegPushButton_clicked()
{
    if (mainController -> isThereAnUploadedImage())
    {
        mainController -> isodataSegmentation();
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


void ThresholdQwidget::on_otsuSegPushButton_clicked()
{
    if (mainController -> isThereAnUploadedImage())
    {
        mainController -> otsuSegmentation();
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


void ThresholdQwidget::on_manualSegPushButton_clicked()
{
    int threshold = (int) ui -> lcdNumber -> value();

    if (mainController -> isThereAnUploadedImage())
    {
        mainController -> bimodalSegmentaion(threshold);
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
