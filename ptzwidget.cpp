#include "ptzwidget.h"
#include "ui_ptzwidget.h"
#include <QDebug>
PtzWidget::PtzWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PtzWidget)
{
    ui->setupUi(this);
}

void PtzWidget::setPlayer(HikvisonWapper *wapper)
{
    this->wapper = wapper;
    if(this->wapper)
    {
        connect(ui->upbtn,&PTZButton::sendstate,this->wapper,&HikvisonWapper::ptzup);
        connect(ui->downbtn,&PTZButton::sendstate,this->wapper,&HikvisonWapper::ptzdown);
        connect(ui->leftbtn,&PTZButton::sendstate,this->wapper,&HikvisonWapper::ptzleft);
        connect(ui->rightbtn,&PTZButton::sendstate,this->wapper,&HikvisonWapper::ptzright);
        connect(ui->zoominbtn,&PTZButton::sendstate,this->wapper,&HikvisonWapper::ptzzoomin);
        connect(ui->zoomoutbtn,&PTZButton::sendstate,this->wapper,&HikvisonWapper::ptzzoomout);
    }
}

void PtzWidget::release()
{
    if(this->wapper)
    {
        disconnect(ui->upbtn,&PTZButton::sendstate,this->wapper,&HikvisonWapper::ptzup);
        disconnect(ui->downbtn,&PTZButton::sendstate,this->wapper,&HikvisonWapper::ptzdown);
        disconnect(ui->leftbtn,&PTZButton::sendstate,this->wapper,&HikvisonWapper::ptzleft);
        disconnect(ui->rightbtn,&PTZButton::sendstate,this->wapper,&HikvisonWapper::ptzright);
        disconnect(ui->zoominbtn,&PTZButton::sendstate,this->wapper,&HikvisonWapper::ptzzoomin);
        disconnect(ui->zoomoutbtn,&PTZButton::sendstate,this->wapper,&HikvisonWapper::ptzzoomout);
    }
    wapper = nullptr;
}

PtzWidget::~PtzWidget()
{
    delete ui;
}

