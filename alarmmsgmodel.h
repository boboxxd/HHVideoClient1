#ifndef ALARMMSGMODEL_H
#define ALARMMSGMODEL_H

#include <QSqlQueryModel>

class AlarmmsgModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit AlarmmsgModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex & item, int role = Qt::DisplayRole) const;
signals:

public slots:
};

#endif // ALARMMSGMODEL_H
