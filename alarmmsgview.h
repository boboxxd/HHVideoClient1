#ifndef ALARMMSGVIEW_H
#define ALARMMSGVIEW_H
#include "alarmmsgmodel.h"

#include <QTableView>
#include <QSqlQueryModel>
#include <QTimer>
class AlarmMsgView : public QTableView
{
    Q_OBJECT
public:
    explicit AlarmMsgView(QWidget *parent = nullptr);
    ~AlarmMsgView();
    void initUI();
    void updateview();
    AlarmmsgModel* mymodel() const;
signals:

public slots:
    void recievecameraip(const QString& name);
    void ondoubleClicked(const QModelIndex &index);
private:
    AlarmmsgModel *model;
    QString cameraip;
    QTimer *timer;
};

#endif // ALARMMSGVIEW_H
