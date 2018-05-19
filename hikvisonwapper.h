#ifndef HIKVISONWAPPER_H
#define HIKVISONWAPPER_H
#include <QWidget>
#include <QObject>
#include <HCNetSDK.h>

class HikvisonWapper : public QObject
{
    Q_OBJECT
public:
    explicit HikvisonWapper(QWidget *widget=nullptr);
    ~HikvisonWapper();
    void init();
    void destroy();
    void setWindow(QWidget *widget);
    void close();
signals:
    void error();
    void errormsg(const QString &);
private slots:
    //错误处理
    void handleerror();
public slots:
    bool open(QString ip,int port,QString username,QString password);
    //云台控制
    void ptzup(int);
    void ptzdown(int);
    void ptzright(int);
    void ptzleft(int);
    void ptzzoomin(int);//变大
    void ptzzoomout(int);//变小
private:
    QWidget *videowidget;
    LONG lUserID;
    LONG lRealPlayHandle;
};

#endif // HIKVISONWAPPER_H
