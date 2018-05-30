#include "alarmmsgview.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlRecord>
#include <QHeaderView>
#include <QModelIndex>
#include <QLabel>
AlarmMsgView::AlarmMsgView(QWidget *parent) : QTableView(parent)
{
    initUI();
    cameraip = "";
    static QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/hhit/Desktop/HHVideoClient1/server/local.db");
    //db.setDatabaseName("/usr/local/hhit/carDetection/db/local.db");
    if(db.open())
    {
        qDebug()<<"/usr/local/hhit/carDetection/db/local.db"<<db.isOpen();

    }else
    {
        qDebug()<<db.isOpen();
    }

    model=new AlarmmsgModel(this);
    QString query=QString("SELECT id As %1,"
                          "obj_type As %2,"
                          "credibility As %3,"
                          "timestamp As %4,"
                          "camera_name As %5,"
                          "camera_ip As %6,"
                          "alarm_pic As %7 "
                          "FROM t_alarminfo "
                          "where %6 = '%8'").arg("序号")
            .arg("类别").arg("可信度").arg("时间").arg("摄像机名称").arg("摄像机ip").arg("报警图片").arg(cameraip);
    model->setQuery(query);
    model->sort(1, Qt::DescendingOrder);
    this->setModel(model);

}

void AlarmMsgView::initUI()
{

    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(this,&AlarmMsgView::doubleClicked,this,&AlarmMsgView::ondoubleClicked);

    timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer,&QTimer::timeout, this,&AlarmMsgView::updateview);
    timer->start();
}

AlarmMsgView::~AlarmMsgView()
{
    delete model;
}

void AlarmMsgView::updateview()
{
    qDebug()<<"update view";
    QString query=QString("SELECT id As %1,"
                          "obj_type As %2,"
                          "credibility As %3,"
                          "timestamp As %4,"
                          "camera_name As %5,"
                          "camera_ip As %6,"
                          "alarm_pic As %7 "
                          "FROM t_alarminfo "
                          "where %6 = '%8'").arg("序号")
            .arg("类别").arg("可信度").arg("时间").arg("摄像机名称").arg("摄像机ip").arg("报警图片").arg(cameraip);
    model->setQuery(query);
}

void AlarmMsgView::ondoubleClicked(const QModelIndex &index)
{
    int row = index.row();
    QString jpgname=model->data(model->index(row,6),Qt::EditRole).toString();
    static QLabel label;
    label.setAlignment(Qt::AlignHCenter);
    label.setPixmap(jpgname);
    label.showMaximized();
}

void AlarmMsgView::recievecameraip(const QString &ip)
{
    cameraip = ip;
    updateview();
}
