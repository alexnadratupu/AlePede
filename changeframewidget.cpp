#include "changeframewidget.h"
#include "ui_changeframewidget.h"

ChangeFrameWidget::ChangeFrameWidget(QWidget * parent,
        MainController *                       controller,
        MainWindow *                           window):
    QWidget(parent),
    ui(new Ui::ChangeFrameWidget)
{
    ui -> setupUi(this);

    this -> mainController = controller;
    this -> mainwindow     = window;
}

ChangeFrameWidget::~ChangeFrameWidget()
{
    delete ui;
}

void ChangeFrameWidget::on_sliderFrame_valueChanged(int value)
{
    if (mainController -> isThereAnUploadedImage())
    {
        mainController -> changeFrame(value);
        ui -> labelNum -> setText(QString::number(value));
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

void ChangeFrameWidget::setMaxFrame(int value)
{
    ui -> sliderFrame -> setMaximum(value);
}
