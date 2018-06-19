#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include "config.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Hikvison::hikvison_init();
    init();
    setSplitScreenNum(Config::GetConfig()->screennum());
    connect (ui->listWidget,&DeviceListWidget::senddevice,this,&Widget::opencamera);
    connect (ui->listWidget,&DeviceListWidget::sendCameraname,ui->imagelistwidget,&ImageListWidget::recievecameraip);
}

void Widget::onplayererror(const QString &msg)
{
    qDebug()<<"ontest"<<msg;
    QMessageBox::critical(NULL, "error",msg, QMessageBox::Yes);
}


void Widget::curscreenindexplus1()
{
        switch(currentpage)
        {
        case 0:
            if(curscreen<1)
            {
              ++curscreen;
            }
            break;
        case 1:
            if(curscreen<4)
            {
              ++curscreen;
            }
            break;
        case 2:
            if(curscreen<9)
            {
              ++curscreen;
            }
            break;
        }
}

void Widget::opencamera(const Camera& dev)
{
    qDebug()<<dev.ip<<dev.port<<dev.username<<dev.password;
    this->dev=dev;
    if(map[curscreen] != nullptr)
    {
        map[curscreen]->close();
        delete map[curscreen];
    }

    HikvisonWapper *player = new HikvisonWapper;
    connect(player,&HikvisonWapper::errormsg,this,&Widget::onplayererror);
    videowidget= ui->mainwidget->GetVideoWidget(currentpage,curscreen);

    videowidget->setPlayer(player);
    player->setWindow(videowidget);
    player->close();
    player->open(dev.ip,dev.port,dev.username,dev.password);
    map[curscreen] = player;

    curscreenindexplus1();
}


void Widget::closeEvent(QCloseEvent *event)
{
    for(int i =0 ;i<map.count();i++)
    {
        HikvisonWapper *player =map[i];
        if(player!=nullptr){
            player->close();
            delete player;
            player = nullptr;
            map[i] = nullptr;
        }
    }
    Config::GetConfig()->setscreennum(currentpage);
    Hikvison::hikvison_destory();
}

Widget::~Widget()
{

    delete ui;
}

void Widget::init()
{
    connect(this,&Widget::screennum,ui->mainwidget,&MainLayout::setScreenCount);
    connect(ui->mainwidget,&MainLayout::currentScreenIndex,this,&Widget::showcheckscreen);
    ui->mainwidget->setScreenCount(4);
    {
        for(int i=0;i<14;i++)
        {
            map[i] = nullptr;
        }
    }
}

void Widget::showcheckscreen(int index)
{
    if(index>=map.size())
        return;
    curscreen = index;
    ui->ptzwidget->release();
    ui->ptzwidget->setPlayer(map[curscreen]);
}

void Widget::setSplitScreenNum(int num)
{
    currentpage = num;
    curscreen = 0;
    switch (num) {
    case 0:
        ui->mainwidget->setScreenCount(1);
        break;
    case 1:
        ui->mainwidget->setScreenCount(4);
        break;
    case 2:
        ui->mainwidget->setScreenCount(9);
        break;
    }
}
