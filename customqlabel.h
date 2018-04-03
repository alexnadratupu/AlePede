#ifndef CUSTOMQLABEL_H
#define CUSTOMQLABEL_H

#include <QWidget>
#include "mainwindow.h"

#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
#include <QWidget>

namespace Ui {
class CustomQLabel;
}

class CustomQLabel : public QWidget
{
    Q_OBJECT

public:
    explicit CustomQLabel(QWidget *parent = 0);
    ~CustomQLabel();

private:
    Ui::CustomQLabel *ui;
};

#endif // CUSTOMQLABEL_H
