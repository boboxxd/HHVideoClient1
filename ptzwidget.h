#ifndef PTZWIDGET_H
#define PTZWIDGET_H

#include <QWidget>
#include "hikvisonwapper.h"
namespace Ui {
class PtzWidget;
}

class PtzWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PtzWidget(QWidget *parent = 0);
    void setPlayer(HikvisonWapper *wapper);
    ~PtzWidget();
private:
    Ui::PtzWidget *ui;
    HikvisonWapper *wapper;
};

#endif // PTZWIDGET_H
