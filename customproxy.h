#ifndef CUSTOMPROXY_H
#define CUSTOMPROXY_H

#include <QSortFilterProxyModel>

class CustomProxy : public QSortFilterProxyModel
{

    Q_OBJECT

public:
    CustomProxy(QObject* parent = 0);

    void setColumn(int index) {_filterColumn = index + 3;}

    void setMinimum(double minimum);

    void setMaximum(double maximum);

    void filterProxy();

    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

private:
    QSortFilterProxyModel* _proxyModel;
    QVariant _minimum;
    QVariant _maximum;
    int _filterColumn = 3;
};

#endif // CUSTOMPROXY_H
