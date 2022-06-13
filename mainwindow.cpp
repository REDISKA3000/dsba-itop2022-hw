#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <customproxy.h>

#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QApplication>
#include <QTextStream>
#include <iostream>
#include <storage.h>
#include <QSortFilterProxyModel>
#include <QtWidgets>
#include <QComboBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _storage = new Storage(this);

    _mainTable = new QStandardItemModel(10,10,this);
    _customProxy = new CustomProxy(this);
    _customProxy->setSourceModel(_mainTable);
    _customProxy->dynamicSortFilterChanged(true);
    ui->mainTab->setModel(_mainTable);
    ui->mainTab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->proxyView->setModel(_customProxy);
    ui->proxyView->setRootIsDecorated(true);

    ui->proxyView->setAlternatingRowColors(true);

    ui->toSpinBox->setMaximum(1000);
    ui->toSpinBox->setMinimum(-1000);

    ui->fromSpinBox->setMaximum(1000);
    ui->fromSpinBox->setMinimum(-1000);

    connect(ui->fromSpinBox, &QDoubleSpinBox::textChanged, this, &MainWindow::doubleFilterChanged);

    connect(ui->toSpinBox, &QDoubleSpinBox::textChanged, this, &MainWindow::doubleFilterChanged);

    connect(ui->lineEdit, &QLineEdit::textEdited, this, &MainWindow::textFilterChanged);

    ui->statusbar->showMessage(QString::fromStdString("Filter hasn't been changed yet :("));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = "C:/se/BigPrj/cereals.csv";

    if (fileName.isNull())
            return;

    _storage->loadFile(fileName);
    createTable();
}


void MainWindow::on_actionExit_triggered() {close();}

void MainWindow::createTable()
{
    QStringListModel *current (_storage->getModel());
    QStandardItemModel *cur = new QStandardItemModel(current->rowCount()-1,16,this);
    QModelIndex lineIndex = current->index(0);
    QString line = (current->data(lineIndex)).toString();
    QStringList labels = line.split(',');
    _storage->setLabels(labels);
    QString label1;
    for (int it = 0; it != labels.count(); ++it)
    {
        label1 = (labels.at(it));
        std::string lad = label1.toStdString();
        cur->setHeaderData(it,Qt::Horizontal,label1);
    }
    for (int jt = 0;jt != current->rowCount()-1;++jt)
    {
        lineIndex = current->index(jt+1);
        line = (current->data(lineIndex)).toString();
        QStringList items = line.split(',');
        for (int wt = 0; wt != items.count(); ++wt)
        {
            QVariant word = (items.at(wt));
            if (wt>=4)
                word = (items.at(wt)).toDouble();
            else
                word = word.toString();

            QModelIndex wordIndex = cur->index(jt,wt);
            //ui->mainTab->setCurrentIndex(wordIndex);
            cur->setData(wordIndex,word);
            _storage->addItemToModel(wordIndex,word);
        }
        //sint i = _storage->getModel()->rowCount();
    }
    _mainTable = cur;
    _customProxy->setSourceModel(_mainTable);
    ui->mainTab->setModel(_mainTable);
    ui->proxyView->setModel(_customProxy);
    ui->proxyView->setSortingEnabled(true);
    ui->proxyView->sortByColumn(0, Qt::AscendingOrder);
//    ui->proxyView->sortByColumn(4,Qt::AscendingOrder);
//    ui->mainTab->verticalHeader()->hide();

}

void onRemindersFileReaded() {}


void MainWindow::on_pushButton_clicked()
{
    _anWindow = new AnalyticsWindow(nullptr,_customProxy);
    connect(_anWindow, &AnalyticsWindow::callBack, this, &MainWindow::show);
    _anWindow->show();
    hide();
}


void MainWindow::on_actionSave_triggered()
{
    if (this->_storage->getVal())
    {
        QFile DB("C:/se/BigPrj/cereals.csv");
        DB.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream fStream(&DB);
        QString str;
        QStringList labels = _storage->getLabels();
        std::string listOfLabels;
        for(int it = 0; it != labels.count(); ++it)
        {
            std::string label = labels.at(it).toStdString();
            if (it == labels.count()-1)
            {
                listOfLabels = listOfLabels + label + '\n';
                break;
            }
            listOfLabels += label + ',';
        }
        DB.write(listOfLabels.c_str());
        for(int it = 0; it != _mainTable->rowCount(); ++it)
        {
            std::string str;
            for (int jt = 0; jt != _mainTable->columnCount(); ++jt)
            {
                QModelIndex wordIndex = _mainTable->index(it,jt);
                std::string word = (_mainTable->data(wordIndex)).toString().toStdString();
                if (jt == _mainTable->columnCount()-1)
                {
                    str = str + word + '\n';
                    break;
                }
                str = str + word + ',';
            }
            DB.write(str.c_str());
        }
        DB.close();
    }
}


void MainWindow::on_AddNewItems_clicked()
{
    QStringList store;
    for(int wt = 1; wt != _mainTable->rowCount(); ++wt)
    {
        std::string str;
        for (int jt = 0; jt != _mainTable->columnCount(); ++jt)
        {
            QModelIndex itemIndex = _mainTable->index(wt,jt);
            std::string item1 = (_mainTable->data(itemIndex)).toString().toStdString();
            ui->mainTab->setCurrentIndex(itemIndex);
            if (jt == _mainTable->columnCount()-1)
                str += item1;

            else
                str += item1 +',';
            QString item = QString::fromStdString(item1);
        }
        store << QString::fromStdString(str);
    }
    _storage->getModel()->setStringList(store);

}

void MainWindow::on_plusOne_clicked()
{
    QStandardItem *item = new QStandardItem(1,_storage->getModel()->rowCount());
    _mainTable->insertRow(_mainTable->rowCount(),_mainTable->index(_mainTable->rowCount(),0));
}


void MainWindow::on_minusOne_clicked()
{
//    QStandardItem *item = new QStandardItem(1,_storage->getModel()->rowCount());
    int i = _storage->getModel()->rowCount();
    int j = _mainTable->rowCount();
    if(_storage->getModel()->rowCount()+1<_mainTable->rowCount())
        _mainTable->removeRows((_mainTable->rowCount()-1),1,_storage->getModel()->index(_mainTable->rowCount()-1,0));
}


void MainWindow::on_Delete_clicked()
{
    QModelIndex ind = ui->mainTab->currentIndex();
    _storage->getModel()->removeRows(ind.row(),1);
    _mainTable->removeRows(ind.row(),1);
    ui->mainTab->setModel(_mainTable);
}

void MainWindow::on_comboBox_activated(int index)
{
    _customProxy->setColumn(index);
    double minimum = ui->fromSpinBox->value();
    double maximum = ui->toSpinBox->value();
    _customProxy->setMinimum(minimum);
    _customProxy->setMaximum(maximum);
}

void MainWindow::doubleFilterChanged()
{
    ++_statBar;
    double minimum = ui->fromSpinBox->value();
    double maximum = ui->toSpinBox->value();
    QString bar;
    if (_statBar == 1)
        bar = QString::fromStdString("Filter has been changed " + std::to_string(_statBar) + "-st time :)");
    else if (_statBar == 2)
        bar = QString::fromStdString("Filter has been changed " + std::to_string(_statBar) + "-nd time :)");
    else if (_statBar == 3)
        bar = QString::fromStdString("Filter has been changed " + std::to_string(_statBar) + "-rd time :)");
    else
        bar = QString::fromStdString("Filter has been changed " + std::to_string(_statBar) + "-th time :)");
    ui->statusbar->showMessage(bar);
    _customProxy->setMinimum(minimum);
    _customProxy->setMaximum(maximum);
}

void MainWindow::textFilterChanged()
{
    std::string str = ui->lineEdit->text().toStdString();
    QRegExp regExp(ui->lineEdit->text(),Qt::CaseSensitive,  QRegExp::FixedString);
    _customProxy->setFilterRegExp(regExp);

}


void MainWindow::on_logoBtn_clicked()
{
    _logoWindow = new LogoWindow;
    connect(_logoWindow, &LogoWindow::goBack, this, &MainWindow::show);
    _logoWindow->show();
}

