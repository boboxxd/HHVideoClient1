#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    player=new HikvisonWapper(ui->openGLWidget);

    ui->ptzwidget->setPlayer(player);
    connect(player,&HikvisonWapper::errormsg,this,&Widget::test);
    connect (ui->listWidget,&DeviceListWidget::senddevice,this,&Widget::opencamera);
}

void Widget::test(const QString &msg)
{
    qDebug()<<"ontest"<<msg;
}

void Widget::opencamera(const Camera& dev)
{
    qDebug()<<dev.ip<<dev.port<<dev.username<<dev.password;
    player->close();
    player->destroy();
    player->init();
    player->open(dev.ip,dev.port,dev.username,dev.password);
}

Widget::~Widget()
{
    delete player;
    delete ui;
}
