#include "videowidget.h"
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QDebug>

VideoWidget::VideoWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setStyleSheet("background-color: rgb(0, 0, 0);");
    player = nullptr;
}

void VideoWidget::setPlayer(HikvisonWapper *player)
{
    this->player=player;
}

void VideoWidget::contextMenuEvent(QContextMenuEvent* e)
{
    if(player == nullptr)
        return;
    QMenu *menu = new QMenu();
    QAction closevideo(tr("关闭视频"));
    connect(&closevideo,&QAction::triggered,player,&HikvisonWapper::close);
    menu->addSeparator();
    menu->addAction(&closevideo);
    menu->exec(e->globalPos());

    delete menu;
    update();
    return QOpenGLWidget::contextMenuEvent(e);
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(player == nullptr)
        return;
    if(event->button()==Qt::LeftButton)
    {
        if(isFullScreen() == false)
        {
            setWindowFlags(Qt::Window);
            showFullScreen();
            startPlayer();
        }else
        {
            setWindowFlags(Qt::SubWindow);        
            showNormal();
            startPlayer();
        }
    }
    return QOpenGLWidget::mouseDoubleClickEvent(event);
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    setFocus();
    if (event->button () & Qt::LeftButton )
    {
        qDebug()<<this->winId();
        emit sendWId(this->winId());
    }
    return QOpenGLWidget::mousePressEvent(event);
}

void VideoWidget::closeEvent(QCloseEvent *event)
{
    player->close();
    player = nullptr;
    return QOpenGLWidget::closeEvent(event);
}

bool VideoWidget::isplayerwork()
{
    return (player == NULL)?false:true;
}

void VideoWidget::startPlayer()
{
    player->reopen();
}

void VideoWidget::stopPlayer()
{
    player->close();
    player= NULL;
}
