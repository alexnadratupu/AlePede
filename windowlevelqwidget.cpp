#include "windowlevelqwidget.h"
#include "ui_windowlevelqwidget.h"

WindowLevelQWidget::WindowLevelQWidget(QWidget * parent,
        MainController *                         controller,
        MainWindow *                             window):
    QWidget(parent),
    ui(new Ui::WindowLevelQWidget)
{
    ui -> setupUi(this);

    mainwindow     = window;
    mainController = controller;

    ui -> labelLevelValue -> setNum(ui -> verticalSliderLevel -> value());
    ui -> labelWindowValue -> setNum(ui -> verticalSliderWindow -> value());
}

WindowLevelQWidget::~WindowLevelQWidget()
{
    delete ui;
}

void WindowLevelQWidget::on_comboBoxPresets_currentIndexChanged(const QString & arg1)
{
    if (arg1 == "Brain")
    {
        ui -> verticalSliderWindow -> setValue(110);
        ui -> verticalSliderLevel -> setValue(35);
    }

    if (arg1 == "Abdomen")
    {
        ui -> verticalSliderWindow -> setValue(320);
        ui -> verticalSliderLevel -> setValue(50);
    }

    if (arg1 == "Mediastinum")
    {
        ui -> verticalSliderWindow -> setValue(400);
        ui -> verticalSliderLevel -> setValue(80);
    }

    if (arg1 == "Bone")
    {
        ui -> verticalSliderWindow -> setValue(2000);
        ui -> verticalSliderLevel -> setValue(350);
    }

    if (arg1 == "Lung")
    {
        ui -> verticalSliderWindow -> setValue(1500);
        ui -> verticalSliderLevel -> setValue(-500);
    }

    if (arg1 == "MIP")
    {
        ui -> verticalSliderWindow -> setValue(300);
        ui -> verticalSliderLevel -> setValue(120);
    }
}

void WindowLevelQWidget::on_verticalSliderLevel_valueChanged(int value)
{
    mainController -> applyWindowLevel(ui -> verticalSliderWindow -> value(), value);
    mainwindow -> displayResults(mainController -> getQImage());
}

void WindowLevelQWidget::on_verticalSliderWindow_valueChanged(int value)
{
    mainController -> applyWindowLevel(value, ui -> verticalSliderLevel -> value());
    mainwindow -> displayResults(mainController -> getQImage());
}
