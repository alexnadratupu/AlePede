#ifndef WINDOWLEVELQWIDGET_H
#define WINDOWLEVELQWIDGET_H

#include <QWidget>
#include "mainwindow.h"

class   MainWindow;


//namespace Ui {
//class WindowLevelQWidget;
//}

class WindowLevelQWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WindowLevelQWidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~WindowLevelQWidget();

private slots:
    void on_comboBoxPresets_currentIndexChanged(const QString &arg1);

    void on_verticalSliderLevel_valueChanged(int value);

    void on_verticalSliderWindow_valueChanged(int value);

private:
    WindowLevelQWidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
};
#endif // WINDOWLEVELQWIDGET_H
