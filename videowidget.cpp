#include "videowidget.h"
#include <QMouseEvent>
VideoWidget::VideoWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void VideoWidget::resizeEvent(QResizeEvent *event)
{

    update();
}

//void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
//{
//    if(event->button()==Qt::LeftButton)
//    {
//        if(isFullScreen() == false)
//        {
//            setWindowFlags(Qt::Window);
//            showFullScreen();
//        }else
//        {
//            setWindowFlags(Qt::SubWindow);
//            showNormal();
//        }
//    }
//}
