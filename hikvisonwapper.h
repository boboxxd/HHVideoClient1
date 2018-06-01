#ifndef HIKVISONWAPPER_H
#define HIKVISONWAPPER_H
#include <QObject>
#include <HCNetSDK.h>

class VideoWidget;
namespace Hikvison {

    class HikvisonWapper;
    void hikvison_init();   //sdk初始化
    void hikvison_destory();    //sdk销毁
    class HikvisonWapper : public QObject
    {
        Q_OBJECT
    public:
         HikvisonWapper(QWidget *widget=nullptr);
        ~HikvisonWapper();
        void setWindow(QWidget *widget);
        //void close();
    signals:
        void playerror();
        void ptzerror();
        void errormsg(const QString &);

    private slots:
        void handleplayerror();     //视频错误处理
        void handleptzerror();      //PTZ错误

    public slots:
        bool open(QString ip,int port,QString username,QString password);
        void reopen();
        void close();
        void ptzup(int);//云台控制
        void ptzdown(int);
        void ptzright(int);
        void ptzleft(int);
        void ptzzoomin(int);    //变大
        void ptzzoomout(int);   //变小
    private:
        VideoWidget *videowidget;   //播放窗口的指针
        LONG lUserID;
        LONG lRealPlayHandle;

        //登录信息
        QString m_ip;
        int m_port;
        QString m_username;
        QString m_password;

        //子码流、主码流
        int stream_type; //0-主码流,1-子码流

    };

}



#endif // HIKVISONWAPPER_H
