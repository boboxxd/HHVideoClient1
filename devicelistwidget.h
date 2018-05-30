#ifndef DEVICELISTWIDGET_H
#define DEVICELISTWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "common.h"

namespace Ui {
class DeviceListWidget;
}

class DeviceListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit DeviceListWidget(QWidget *parent = 0);
    void init();
    QListWidgetItem* createItem(const Camera &dev);
    Camera deviceInfo(QListWidgetItem *item);
    ~DeviceListWidget();
signals:
    void senddevice(const Camera&);
    void sendCameraname(const QString &name);
public slots:
    void onitemDoubleClicked(QListWidgetItem *item);
    void onitemClicked(QListWidgetItem *item);
private:
    Ui::DeviceListWidget *ui;

};

#endif // DEVICELISTWIDGET_H
