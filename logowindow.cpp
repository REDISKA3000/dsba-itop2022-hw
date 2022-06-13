#include "logowindow.h"
#include "ui_logowindow.h"
#include<logoclass.h>

LogoWindow::LogoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogoWindow)
{
    ui->setupUi(this);
    _logo = new LogoClass;
    ui->gridLayout->addWidget(_logo);
}

LogoWindow::~LogoWindow()
{
    delete ui;
}
