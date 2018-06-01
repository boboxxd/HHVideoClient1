#ifndef IMAGELISTWIDGET_H
#define IMAGELISTWIDGET_H
#include "alarmmsgview.h"
#include <QListWidget>
#include <QTableView>
#include <QSqlQueryModel>
#include "previewwidget.h"
#include <QTimer>

class ImageListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ImageListWidget(QWidget *parent = nullptr);
    void init();
    void updateview();
public slots:
    void addimageItem(const QString &name);
    void getdata();
    void ondoubleClicked(const QModelIndex &index);
signals:

public slots:
    void recievecameraip(const QString& name);
private:
    QSqlQueryModel *model;
    QString cameraip;
    QTimer *timer;
};

#endif // IMAGELISTWIDGET_H
