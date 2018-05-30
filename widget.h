#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include "hikvisonwapper.h"
#include "ptzwidget.h"
#include "common.h"
using namespace Hikvison;
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
    void onplayererror(const QString &msg);
    void opencamera(const Camera&);
    void closeEvent(QCloseEvent *event);
private:
    Ui::Widget *ui;
    HikvisonWapper *player;
    Camera dev;
};

#endif // WIDGET_H
