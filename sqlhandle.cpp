#include "sqlhandle.h"
#include <QSqlRecord>
Sqlhandle::Sqlhandle(QObject *parent) : QObject(parent)
{

}

Sqlhandle::~Sqlhandle()
{
    delete model;
    model =nullptr;
}

void Sqlhandle::init()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

void Sqlhandle::open()
{
    db.setDatabaseName("data.db");
    db.open();
}

bool Sqlhandle::isopen()
{
    return db.isOpen();
}

void Sqlhandle::close()
{
    db.close();
}

QVector<Camera> Sqlhandle::readline()
{
    QVector<Camera> devvec;
    model=new QSqlTableModel(this,db);
    model->setTable("camera");
    model->setSort(1, Qt::AscendingOrder);
    model->select();
    for (int i = 0; i < model->rowCount(); ++i) {
        Camera dev;
        dev.brief = model->record(i).value("brief").toString();
        dev.id = model->record(i).value("id").toInt();
        dev.ip = model->record(i).value("ip").toString();
        dev.port = model->record(i).value("port").toInt();
        dev.username = model->record(i).value("username").toString();
        dev.password = model->record(i).value("password").toString();
        devvec.append(dev);
    }
    return devvec;
}

