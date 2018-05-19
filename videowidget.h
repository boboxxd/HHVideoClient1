#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QOpenGLWidget>

class VideoWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);
    //void mouseDoubleClickEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
signals:

public slots:

};

#endif // VIDEOWIDGET_H
