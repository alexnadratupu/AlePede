#include "customqlabel.h"
#include "ui_customqlabel.h"

CustomQLabel::CustomQLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomQLabel)
{
    ui->setupUi(this);
}

CustomQLabel::~CustomQLabel()
{
    delete ui;
}
