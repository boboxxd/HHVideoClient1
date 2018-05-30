#include "videowidget.h"
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <widget.h>
VideoWidget::VideoWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void VideoWidget::setPlayer(HikvisonWapper *player)
{
    this->player=player;
}

void VideoWidget::resizeEvent(QResizeEvent *event)
{
    update();
}

void VideoWidget::contextMenuEvent(QContextMenuEvent* e)
{
    QMenu *menu = new QMenu();
    Widget *pw=qobject_cast<Widget*>(parentWidget()->parentWidget());
    QAction closevideo(tr("关闭视频"));
    connect(&closevideo,&QAction::triggered,player,&HikvisonWapper::close);
    menu->addSeparator();
    menu->addAction(&closevideo);
    menu->exec(e->globalPos());
    delete menu;
    update();
}


void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if(isFullScreen() == false)
        {
            setWindowFlags(Qt::Window);
            showFullScreen();

        }else
        {
            setWindowFlags(Qt::SubWindow);
            showNormal();

        }
    }
}
