#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Hikvison::hikvison_init();
    player=new HikvisonWapper(ui->openGLWidget);
    ui->openGLWidget->setPlayer(player);
    ui->ptzwidget->setPlayer(player);
    connect(player,&HikvisonWapper::errormsg,this,&Widget::onplayererror);
    connect (ui->listWidget,&DeviceListWidget::senddevice,this,&Widget::opencamera);
    connect (ui->listWidget,&DeviceListWidget::sendCameraname,ui->tableView,&AlarmMsgView::recievecameraip);
}

void Widget::onplayererror(const QString &msg)
{
    qDebug()<<"ontest"<<msg;
    QMessageBox::critical(NULL, "error",msg, QMessageBox::Yes);
}

void Widget::opencamera(const Camera& dev)
{
    qDebug()<<dev.ip<<dev.port<<dev.username<<dev.password;
    this->dev=dev;
    player->close();
    player->open(dev.ip,dev.port,dev.username,dev.password);
}


void Widget::closeEvent(QCloseEvent *event)
{
    player->close();
    Hikvison::hikvison_destory();
}

Widget::~Widget()
{
    delete player;
    delete ui;
}
