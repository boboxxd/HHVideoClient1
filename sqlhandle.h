#ifndef SQLHANDLE_H
#define SQLHANDLE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "common.h"
class Sqlhandle : public QObject
{
    Q_OBJECT
public:
    explicit Sqlhandle(QObject *parent = nullptr);
    ~Sqlhandle();
    void init();
    void open();
    bool isopen();
    void close();
    QVector<Camera> readline();
signals:

public slots:

private:
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // SQLHANDLE_H
