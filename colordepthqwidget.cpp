#include "colordepthqwidget.h"
#include "ui_colordepthqwidget.h"

ColorDepthQwidget::ColorDepthQwidget(QWidget * parent,
                                     MainController *                       controller,
                                     MainWindow *                           window,
                                     int                                    ColorDensity):
    QWidget(parent),
    ui(new Ui::ColorDepthQwidget)
{
    ui -> setupUi(this);

    mainController = controller;
    mainwindow     = window;
    ui -> verticalSlider -> setMaximum(ColorDensity);
    ui -> verticalSlider -> setValue(ColorDensity);
}

ColorDepthQwidget::~ColorDepthQwidget()
{
    delete ui;
}

void ColorDepthQwidget::on_pushButton_clicked()
{
    int depth = (int) ui -> lcdNumber -> value();

    // In case some dicom images hava a bigger value
    if (depth>8) {
        depth=8;
        ui -> verticalSlider -> setMaximum(depth);
        ui -> verticalSlider -> setValue(depth);
    }

    if (mainController -> isThereAnUploadedImage())
    {
        QTextStream(stdout) << "CAMBIANDO DE " << (log2(mainController -> getImage() -> getColorDepth() + 1)) << " A: "
                            << depth << endl;

        mainController -> changeColorDepth(depth);
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
