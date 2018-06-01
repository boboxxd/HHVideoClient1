#include "devicelistwidget.h"
#include "ui_devicelistwidget.h"
#include "sqlhandle.h"
#include <QDebug>

DeviceListWidget::DeviceListWidget(QWidget *parent) :
    QListWidget(parent),
    ui(new Ui::DeviceListWidget)
{
    ui->setupUi(this);
    connect(this,&DeviceListWidget::itemDoubleClicked,this,&DeviceListWidget::onitemDoubleClicked);
    connect(this,&DeviceListWidget::itemClicked,this,&DeviceListWidget::onitemClicked);
    init();
}

void DeviceListWidget::init()
{
    //载入从sql导入设备列表
    {
        static Sqlhandle sql;
        sql.init();
        sql.open();
        QVector<Camera> devs=sql.readline();
        for(auto i=devs.begin();i!=devs.end();i++)
        {
            addItem(createItem(*i));
        }
        sql.close();
    }
}

QListWidgetItem* DeviceListWidget::createItem(const Camera &dev)
{
    QVariant va;
    va.setValue(dev);
    QListWidgetItem *item = new QListWidgetItem(this);
    item->setData(Qt::UserRole,va);
    item->setData(Qt::DisplayRole,dev.name);
    return item;
}

Camera DeviceListWidget::deviceInfo(QListWidgetItem *item)
{
    QVariant va=item->data(Qt::UserRole);
    Camera dev= va.value<Camera>();
    return dev;
}

DeviceListWidget::~DeviceListWidget()
{
    delete ui;
}

void DeviceListWidget::onitemDoubleClicked(QListWidgetItem *item)
{
    Camera dev= deviceInfo(item);
    qDebug()<<"DeviceListWidget::"<<dev.ip<<dev.port<<dev.username<<dev.password;
    emit senddevice(dev);
}

void DeviceListWidget::onitemClicked(QListWidgetItem *item)
{
    Camera dev= deviceInfo(item);
    emit sendCameraname(dev.ip);
}
