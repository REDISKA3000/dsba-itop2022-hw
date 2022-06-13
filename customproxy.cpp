#include "customproxy.h"
#include <iostream>

CustomProxy::CustomProxy(QObject* ) :
    QSortFilterProxyModel() {}

void CustomProxy::setMinimum(double minimum)
{
    _minimum = minimum;
    invalidateFilter();
}

void CustomProxy::setMaximum(double maximum)
{
    _maximum = maximum;
    invalidateFilter();
}

bool CustomProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{

    QModelIndex index0 = sourceModel()->index(sourceRow, 0);
    QModelIndex index1 = sourceModel()->index(sourceRow, 1);
    QModelIndex index2 = sourceModel()->index(sourceRow, 2);


    if (_minimum.isValid() == 0 || _maximum.isValid() == 0)
        return true;
    double mi = _minimum.toDouble();
    double ma = _maximum.toDouble();
    double col = _filterColumn;
    if (col < 3 || col > 16)
        return true;

    QModelIndex ind = sourceModel()->index(sourceRow,col,sourceParent);

    double val = sourceModel()->data(ind).toDouble();
    if ((val < mi) || (val > ma))
        return false;
    if  (/*((val < mi) || (val > ma)) &&*/
         (!(filterRegExp().isEmpty())) &&
         (!(sourceModel()->data(index0).toString().contains(filterRegExp()) ||
          sourceModel()->data(index2).toString().contains(filterRegExp()) ||
          sourceModel()->data(index1).toString().contains(filterRegExp()))))
        return false;
    return true;

}
