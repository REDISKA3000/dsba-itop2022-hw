#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <storage.h>
#include <QStandardItemModel>
#include <customproxy.h>
#include <QSortFilterProxyModel>
#include <QDoubleSpinBox>
#include <QWidget>
#include <analyticswindow.h>
#include <logowindow.h>

QT_BEGIN_NAMESPACE
class QDoubleSpinBox;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    Storage* _storage;

    QStandardItemModel *_mainTable;

private slots:
    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void createTable();

    void on_pushButton_clicked();

    void on_actionSave_triggered();

    void on_AddNewItems_clicked();

    void on_plusOne_clicked();

    void on_minusOne_clicked();

    void on_Delete_clicked();

    void setMainTable(QStandardItemModel* mainTable) {_mainTable=mainTable;}

    QStandardItemModel* getMainTable() {return _mainTable;}

    void on_comboBox_activated(int index);

//    void sort(int i,Qt::SortOrder ord);

     void doubleFilterChanged();

     void textFilterChanged();

     void on_logoBtn_clicked();

private:
    int _statBar = 0;
    Ui::MainWindow *ui;
    AnalyticsWindow* _anWindow;
    int _filterByDigitalColumn;
    int _filterByTextColumn;
    CustomProxy* _customProxy;
    QDoubleSpinBox* _fromSpinBox;
    LogoWindow* _logoWindow;
//signals:
//    void rowsAboutToBeRemoved(QPrivateSignal);
};
#endif // MAINWINDOW_H
