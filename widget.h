#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include "hikvisonwapper.h"
#include "ptzwidget.h"
#include "common.h"
#include <QMap>
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
    void init();
public slots:
    void onplayererror(const QString &msg);
    void opencamera(const Camera&);
    void closeEvent(QCloseEvent *event);
    void showcheckscreen(int index);
    void setSplitScreenNum(int num);
signals:
    void screennum(int);
private:
    void curscreenindexplus1();
private:
    Ui::Widget *ui;
    Camera dev;

    VideoWidget *videowidget;
    int currentpage;
    WId curscreen;
    QMap<int,HikvisonWapper*> map;
};

#endif // WIDGET_H
