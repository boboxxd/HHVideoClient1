#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "hikvisonwapper.h"
#include "ptzwidget.h"
#include "common.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void test(const QString &msg);
    void opencamera(const Camera&);
private:
    Ui::Widget *ui;
    HikvisonWapper *player;
    //PtzWidget *ptzwidget;
};

#endif // WIDGET_H
