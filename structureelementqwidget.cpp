#include "structureelementqwidget.h"
#include "ui_structuringElementQwidget.h"

StructureElementQwidget::StructureElementQwidget(QWidget * parent,
        MainController *                                   controller,
        MainWindow *                                       window):
    QWidget(parent),
    ui(new Ui::StructureElementQwidget)
{
    ui -> setupUi(this);

    mainwindow      = window;
    mainController  = controller;
    qLineEditMatrix = NULL;

    on_spinBox_valueChanged(3);
    on_spinBox_2_valueChanged(3);
}

StructureElementQwidget::~StructureElementQwidget()
{
    deleteTable();

    delete ui;
}

void StructureElementQwidget::on_spinBox_valueChanged(int arg1)
{
    if (qLineEditMatrix != NULL)
    {
        deleteTable();
    }

    heigthS         = arg1;
    widthLineEdit   = 30;
    heightLineEdit  = 25;
    widthTable      = widthS * (widthLineEdit + 3);
    heightTable     = heigthS * (heightLineEdit + 3);
    initialX        = (ui -> widgetTable -> width() - widthTable) / 2;
    initialY        = (ui -> widgetTable -> height() - heightTable) / 2;
    qLineEditMatrix = new QLineEdit **[heigthS];

    for (int i = 0; i < heigthS; ++i)
    {
        qLineEditMatrix[i] = new QLineEdit *[widthS];
    }

    font.setPointSize(10);

    for (int i = 0; i < heigthS; ++i)
    {
        int x = initialX;

        for (int j = 0; j < widthS; ++j)
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

void StructureElementQwidget::on_spinBox_2_valueChanged(int arg2)
{
    if (qLineEditMatrix != NULL)
    {
        deleteTable();
    }

    widthS          = arg2;
    widthLineEdit   = 30;
    heightLineEdit  = 25;
    widthTable      = widthS * (widthLineEdit + 3);
    heightTable     = heigthS * (heightLineEdit + 3);
    initialX        = (ui -> widgetTable -> width() - widthTable) / 2;
    initialY        = (ui -> widgetTable -> height() - heightTable) / 2;
    qLineEditMatrix = new QLineEdit **[heigthS];

    for (int i = 0; i < heigthS; ++i)
    {
        qLineEditMatrix[i] = new QLineEdit *[widthS];
    }

    font.setPointSize(10);

    for (int i = 0; i < heigthS; ++i)
    {
        int x = initialX;

        for (int j = 0; j < widthS; ++j)
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

void StructureElementQwidget::deleteTable()
{
    for (int i = 0; i < heigthS; ++i)
    {
        for (int j = 0; j < widthS; ++j)
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

void StructureElementQwidget::on_pushButtonDilate_clicked()
{
    int ** kernel = new int *[heigthS];

    for (int i = 0; i < heigthS; ++i)
    {
        kernel[i] = new int[widthS];
    }

    for (int i = 0; i < heigthS; ++i)
    {
        for (int j = 0; j < widthS; ++j)
        {
            kernel[i][j] = qLineEditMatrix[i][j] -> text().toInt();
        }
    }

    bool ok;
    int  origenX = QInputDialog::getInteger(this, tr("R. Point"), tr("Origen X:"), 0, 0, widthS - 1, 1, &ok);

    if (ok)
    {
        int origenY = QInputDialog::getInteger(this, tr("R. Point"), tr("Origen Y:"), 0, 0, heigthS - 1, 1, &ok);

        if (ok)
        {
            mainController -> dilateOperation(kernel, origenX, origenY, heigthS, widthS);
            mainwindow -> displayResults(mainController -> getQImage());
            mainwindow -> ShowHistogram();
        }
    }
}

void StructureElementQwidget::on_pushButtonErosion_clicked()
{
    int ** kernel = new int *[heigthS];

    for (int i = 0; i < heigthS; ++i)
    {
        kernel[i] = new int[widthS];
    }

    for (int i = 0; i < heigthS; ++i)
    {
        for (int j = 0; j < widthS; ++j)
        {
            kernel[i][j] = qLineEditMatrix[i][j] -> text().toInt();
        }
    }

    bool ok;
    int  origenX = QInputDialog::getInteger(this, tr("R. Point"), tr("Origen X:"), 0, 0, widthS - 1, 1, &ok);

    if (ok)
    {
        int origenY = QInputDialog::getInteger(this, tr("R. Point"), tr("Origen Y:"), 0, 0, heigthS - 1, 1, &ok);

        if (ok)
        {
            mainController -> erosionOperation(kernel, origenX, origenY, heigthS, widthS);
            mainwindow -> displayResults(mainController -> getQImage());
            mainwindow -> ShowHistogram();
        }
    }
}

void StructureElementQwidget::on_pushButtonOpening_clicked()
{
    // on_pushButtonErosion_clicked();
    // on_pushButtonDilate_clicked();
    int ** kernel = new int *[heigthS];

    for (int i = 0; i < heigthS; ++i)
    {
        kernel[i] = new int[widthS];
    }

    for (int i = 0; i < heigthS; ++i)
    {
        for (int j = 0; j < widthS; ++j)
        {
            kernel[i][j] = qLineEditMatrix[i][j] -> text().toInt();
        }
    }

    bool ok;
    int  origenX = QInputDialog::getInteger(this, tr("R. Point"), tr("Origen X:"), 0, 0, widthS - 1, 1, &ok);

    if (ok)
    {
        int origenY = QInputDialog::getInteger(this, tr("R. Point"), tr("Origen Y:"), 0, 0, heigthS - 1, 1, &ok);

        if (ok)
        {
            mainController -> openingOperation(kernel, origenX, origenY, heigthS, widthS);
            mainwindow -> displayResults(mainController -> getQImage());
            mainwindow -> ShowHistogram();
        }
    }
}

void StructureElementQwidget::on_pushButtonClosing_clicked()
{
    // on_pushButtonOpening_clicked();
    // on_pushButtonErosion_clicked();
    int ** kernel = new int *[heigthS];

    for (int i = 0; i < heigthS; ++i)
    {
        kernel[i] = new int[widthS];
    }

    for (int i = 0; i < heigthS; ++i)
    {
        for (int j = 0; j < widthS; ++j)
        {
            kernel[i][j] = qLineEditMatrix[i][j] -> text().toInt();
        }
    }

    bool ok;
    int  origenX = QInputDialog::getInteger(this, tr("R. Point"), tr("Origen X:"), 0, 0, widthS - 1, 1, &ok);

    if (ok)
    {
        int origenY = QInputDialog::getInteger(this, tr("R. Point"), tr("Origen Y:"), 0, 0, heigthS - 1, 1, &ok);

        if (ok)
        {
            mainController -> closingOperation(kernel, origenX, origenY, heigthS, widthS);
            mainwindow -> displayResults(mainController -> getQImage());
            mainwindow -> ShowHistogram();
        }
    }
}
