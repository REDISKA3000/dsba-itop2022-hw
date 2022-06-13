#include "storage.h"

#include <stdexcept>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>
#include <QStringListModel>
#include <vector>

Storage::Storage(QObject* parent)
    : QObject{parent}
{
    _model = new QStringListModel(this);
}

void Storage::loadFile(const QString& filename)
{
    _fileName = filename;

    if (readFile())
        emit onFileReaded();
}

bool Storage::readFile()
{
    if (_fileName.isEmpty())
        throw std::invalid_argument("File name not set");

    QFile file(_fileName);

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox box;
        box.setText("Can't open a file to read. So pity");
        box.exec();

        return false;
    }

    QStringList store;

    QTextStream fStream(&file);
     while(!fStream.atEnd())
     {
        QString line = fStream.readLine();
        store << line;
     }
    _model->setStringList(store);
    int k = _model->rowCount();
    _val = true; // claim that file was successfully opened and read
    return true;
}

void Storage::addItemToModel(QModelIndex itemIndex,QVariant item)
{
//     QStringList list;
//    _model->setStringList(list);
    _model->insertRow(1,itemIndex);
    _model->setData(itemIndex,item);
}
