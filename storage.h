#ifndef STORAGE_H
#define STORAGE_H

#include <QObject>
#include <QStringListModel>
#include <vector>
class Storage : public QObject
{
    Q_OBJECT;
public:
    explicit Storage(QObject *parent = nullptr);

public:
    // Opens a file by the given fileName and reads data from it to the ..model..
    void loadFile(const QString& filename);

    QStringListModel* getModel() const { return _model; }

    QString getFileName() const {return _fileName;}

    bool getVal() const {return _val;}

    QStringList getLabels() const {return _labels;}

    void addItemToModel(QModelIndex itemIndex, QVariant item);

    void setLabels(QStringList labels) {_labels = labels;}

    void setModel(QStringListModel* model) {_model=model;}

    QStringList getLabels() {return _labels;}

protected:
    bool readFile();            ///< read a file actually

protected:
    QString _fileName;          ///< stores a given filename
    QStringListModel* _model;   ///< stores a ptr to our model
    bool _val = false;
    QStringList _labels;

signals:
    void onFileReaded();        ///< signal is emit when a file with model data is read succesfully.
};

#endif // STORAGE_H
