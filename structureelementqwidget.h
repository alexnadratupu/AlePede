#ifndef STRUCTUREELEMENTQWIDGET_H
#define STRUCTUREELEMENTQWIDGET_H

#include <QWidget>
#include "mainwindow.h"

class MainWindow;

//namespace Ui {
//class StructureElementQwidget;
//}

class StructureElementQwidget : public QWidget
{
    Q_OBJECT

public:
    explicit StructureElementQwidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~StructureElementQwidget();

private slots:

    void on_spinBox_valueChanged(int arg1);
    void on_spinBox_2_valueChanged(int arg2);
    void on_pushButtonDilate_clicked();
    void on_pushButtonErosion_clicked();
    void on_pushButtonOpening_clicked();
    void on_pushButtonClosing_clicked();

private:
    StructureElementQwidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
    QLineEdit ***qLineEditMatrix;
    int heigthS,widthS;
    double widthLineEdit, heightLineEdit,widthTable,heightTable;
    int initialX, initialY;
    QFont font;

    void deleteTable();
};

#endif // STRUCTUREELEMENTQWIDGET_H
