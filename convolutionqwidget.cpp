#include "convolutionqwidget.h"
#include "ui_convolutionqwidget.h"

ConvolutionQwidget::ConvolutionQwidget(QWidget * parent,
        MainController *                         controller,
        MainWindow *                             window):
    QWidget(parent),
    ui(new Ui::ConvolutionQwidget)
{
    ui -> setupUi(this);

    mainwindow      = window;
    mainController  = controller;
    qLineEditMatrix = NULL;

    on_spinBox_valueChanged(3);
}

ConvolutionQwidget::~ConvolutionQwidget()
{
    deleteTable();

    delete ui;
}

void ConvolutionQwidget::on_spinBox_valueChanged(int arg1)
{
    if (qLineEditMatrix != NULL)
    {
        deleteTable();
    }

    kernelSize = arg1;

    double widthLineEdit  = 30;
    double heightLineEdit = 25;
    double widthTable     = kernelSize * (widthLineEdit + 3);
    double heightTable    = kernelSize * (heightLineEdit + 3);
    int    initialX       = (ui -> widgetTable -> width() - widthTable) / 2;
    int    initialY       = (ui -> widgetTable -> height() - heightTable) / 2;

    qLineEditMatrix = new QLineEdit **[kernelSize];

    for (int i = 0; i < kernelSize; ++i)
    {
        qLineEditMatrix[i] = new QLineEdit *[kernelSize];
    }

    QFont font;

    font.setPointSize(10);

    for (int i = 0; i < kernelSize; ++i)
    {
        int x = initialX;

        for (int j = 0; j < kernelSize; ++j)
        {
            qLineEditMatrix[i][j] = new QLineEdit(ui -> widgetTable);

            qLineEditMatrix[i][j] -> setGeometry(QRect(x, initialY, widthLineEdit, heightLineEdit));
            qLineEditMatrix[i][j] -> setFont(font);
            qLineEditMatrix[i][j] -> setVisible(true);

            x += widthLineEdit + 3;
        }

        initialY += heightLineEdit + 3;
    }
}

void ConvolutionQwidget::deleteTable()
{
    for (int i = 0; i < kernelSize; ++i)
    {
        for (int j = 0; j < kernelSize; ++j)
        {
            delete qLineEditMatrix[i][j];

            qLineEditMatrix[i][j] = 0;
        }

        delete qLineEditMatrix[i];

        qLineEditMatrix[i] = 0;
    }

    delete qLineEditMatrix;

    qLineEditMatrix = 0;
}

void ConvolutionQwidget::on_pushButton_clicked()
{
    int ** kernel = new int *[kernelSize];

    for (int i = 0; i < kernelSize; ++i)
    {
        kernel[i] = new int[kernelSize];
    }

    for (int i = 0; i < kernelSize; ++i)
    {
        for (int j = 0; j < kernelSize; ++j)
        {
            kernel[i][j] = qLineEditMatrix[i][j] -> text().toInt();
        }
    }

    mainController -> convolutionFilter(kernel, kernelSize);
    mainwindow -> displayResults(mainController -> getQImage());
}
