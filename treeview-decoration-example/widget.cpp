#include "widget.h"
#include "ui_widget.h"
#include "model.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->treeView->setModel(new Model);
    ui->treeView->expandAll();
}

Widget::~Widget()
{
    delete ui;
}
