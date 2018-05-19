#include "ptzbutton.h"

PTZButton::PTZButton(QWidget *parent) : QPushButton(parent)
{

}

void PTZButton::mousePressEvent(QMouseEvent *event)
{
    emit sendstate(0);
}

void PTZButton::mouseReleaseEvent(QMouseEvent *event)
{
    emit sendstate(1);
}
