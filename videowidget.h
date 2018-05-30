#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QOpenGLWidget>
#include "hikvisonwapper.h"
using namespace Hikvison;
class VideoWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);
    void setPlayer(HikvisonWapper *player);
    void contextMenuEvent(QContextMenuEvent* e);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
signals:
public slots:
private:
    HikvisonWapper *player;
};

#endif // VIDEOWIDGET_H
