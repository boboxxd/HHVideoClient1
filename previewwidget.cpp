#include "previewwidget.h"
#include <QGridLayout>
#include <QPainter>
#include <QStyleOption>
#include <QDesktopWidget>
#include <QApplication>
PreviewWidget::PreviewWidget(QWidget *parent) : QWidget(parent)
{
    QDesktopWidget *d=QApplication::desktop();
    resize(600,500);
    QPoint leftport((d->width()-width())/2,(d->height()-height())/2);
    move(leftport);
    setStyleSheet("border-image: url(:/icon/background.png);");
}

void PreviewWidget::setPixmap(const QString &jpgname)
{
    if(jpgname != pixname)
    {
        this->pixname = jpgname;
        update();
    }
}

void PreviewWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    pix=QPixmap(pixname).scaled(this->width(),this->height(),Qt::KeepAspectRatio);
    x = (this->width()-pix.width())/2;
    y = (this->height()-pix.height())/2;
    painter.drawPixmap(x,y,pix);
    painter.end();
    QWidget::paintEvent(event);
}

void PreviewWidget::resizeEvent(QResizeEvent *event)
{
    // update();
}

void PreviewWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(!isMaximized())
    {
        showMaximized();
    }else
    {
        showNormal();
    }
}

