#include "imagelistwidget.h"
#include <QDebug>
#include <QSqlRecord>
#include <QPixmap>
#include <QFileInfo>
#include <QLabel>
#include <QDateTime>

static QString alarmstrfromid(int id)
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

ImageListWidget::ImageListWidget(QWidget *parent) : QListWidget(parent)
{
    init();
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
        qDebug()<<"数据库："<<db.isOpen();

    }else
    {
        qDebug()<<"数据库："<<db.isOpen();
    }
    model=new QSqlQueryModel(this);

}

void ImageListWidget::init()
{
    setSpacing(1);
    setResizeMode(QListView::Adjust);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(200,200));
    setMovement(QListView::Static);
    setWrapping(false);
    setFlow(QListView::LeftToRight);
    timer = new QTimer(this);
    timer->setInterval(5000);
    connect(timer,&QTimer::timeout, this,&ImageListWidget::updateview);
    timer->start();
    connect(this,&ImageListWidget::doubleClicked,this,&ImageListWidget::ondoubleClicked);
}

void ImageListWidget::updateview()
{
    getdata();
}


void ImageListWidget::addimageItem(const QString &name)
{
    QPixmap pix(name);
    if(!pix.isNull())
    {
        QFileInfo fi = QFileInfo(name);
        QString file_name = fi.baseName();
        QListWidgetItem *item = new QListWidgetItem(QIcon(pix.scaled(QSize(500,400))),file_name);
        item->setData(Qt::EditRole,name);
        qDebug()<<"data = " <<item->text();
        this->addItem(item);
    }
}

void ImageListWidget::getdata()
{
    clear();
    //qDebug()<<"void ImageListWidget::getdata()";
    QString query=QString("SELECT id As %1,"
                          "obj_type As %2,"
                          "credibility As %3,"
                          "timestamp As %4,"
                          "camera_name As %5,"
                          "camera_ip As %6,"
                          "alarm_pic As %7 "
                          "FROM t_alarminfo "
                          "where %6 = '%8' group by image_id ORDER BY image_id DESC").arg("序号")
            .arg("类别").arg("可信度").arg("时间").arg("摄像机名称").arg("摄像机ip").arg("报警图片").arg(cameraip);
    //qDebug()<<query;
    model->setQuery(query);
    model->sort(1, Qt::DescendingOrder);

    for (int i = 0; i < model->rowCount(); ++i)
    {
        QSqlRecord record = model->record(i);
        QString name = record.value("报警图片").toString();
        QString type = alarmstrfromid(record.value("类别").toInt());
        QString timestamp = QDateTime::fromTime_t(record.value("时间").toInt()).toString("yyyyMMdd/hh:mm:ss");
        QPixmap pix(name);
        if(!pix.isNull())
        {
            QFileInfo fi = QFileInfo(name);
            QString file_name = fi.baseName();
            QListWidgetItem *item = new QListWidgetItem(QIcon(pix.scaled(QSize(500,400))),file_name);
            item->setData(Qt::EditRole,timestamp);
            item->setData(Qt::UserRole,name);
            item->setData(Qt::ToolTipRole,type);
            this->addItem(item);
        }
    }
}

void ImageListWidget::ondoubleClicked(const QModelIndex &index)
{
    int row = index.row();
    QString jpgname=item(row)->data(Qt::UserRole).toString();

    static PreviewWidget label;
    label.setWindowTitle(item(row)->data(Qt::DisplayRole).toString());
    label.setPixmap(jpgname);
    label.show();
    label.raise();
}

void ImageListWidget::recievecameraip(const QString &ip)
{
    cameraip = ip;
    getdata();
}
