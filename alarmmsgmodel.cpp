#include "alarmmsgmodel.h"
#include <QSqlQuery>
#include <QDebug>
#include <QColor>
#include <QDateTime>
QString alarmstrfromid(int id)
{
    switch (id) {
    case 0:
        return QString("无");
        break;
    case 1:
        return QString("吊车");
        break;
    case 2:
        return QString("挖掘机");
        break;
    case 3:
        return QString("水泥泵车");
        break;
    case 4:
        return QString("推土机");
        break;
    case 5:
        return QString("扬臂吊车");
        break;
    case 6:
        return QString("塔吊");

    }
}
AlarmmsgModel::AlarmmsgModel(QObject *parent) : QSqlQueryModel(parent)
{

}

QVariant AlarmmsgModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);
    if (role == Qt::TextColorRole && item.column()==0)
        return qVariantFromValue(QColor(Qt::red));
    if(role == Qt::TextAlignmentRole)
    {
        value = (Qt::AlignVCenter+Qt::AlignHCenter);
    }

    if(role == Qt::DisplayRole && item.column()==1)
    {
        value = alarmstrfromid(value.toInt());
    }

    if(role == Qt::DisplayRole && item.column()==3)
    {
        value =QDateTime::fromTime_t(value.toInt()).toString("yyyy-MM-dd hh:mm:ss");
    }

    return value;
}


