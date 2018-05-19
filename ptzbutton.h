#ifndef PTZBUTTON_H
#define PTZBUTTON_H

#include <QPushButton>

class PTZButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PTZButton(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void sendstate(int);
public slots:

private:



};

#endif // PTZBUTTON_H
