#include "hikvisonwapper.h"
using namespace Hikvison;
#include "videowidget.h"
#include <QDebug>
#include "config.h"
void Hikvison::hikvison_init()
{
    NET_DVR_Init();
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);
}

void Hikvison::hikvison_destory()
{
    NET_DVR_Cleanup();
}


HikvisonWapper::HikvisonWapper(QWidget *widget)
    :videowidget(qobject_cast<VideoWidget*>(widget)),lUserID(0),lRealPlayHandle(0)
{
    connect(this,&HikvisonWapper::playerror,this,&HikvisonWapper::handleplayerror);
}

HikvisonWapper::~HikvisonWapper()
{
    close();
}

void HikvisonWapper::setWindow(QWidget *widget)
{
    videowidget = qobject_cast<VideoWidget*>(widget);
    wndid = videowidget->winId();
}

void HikvisonWapper::setWinId(WId id)
{
    wndid=id;
}


bool HikvisonWapper::open(QString ip,int port,QString username,QString password)
{
    NET_DVR_DEVICEINFO_V30 struDeviceInfo;
    lUserID = NET_DVR_Login_V30(ip.toLocal8Bit().data(), port, username.toLocal8Bit().data(), password.toLocal8Bit().data(), &struDeviceInfo);
    if (lUserID == -1)
    {
        emit playerror();
        return false;
    }

    NET_DVR_PREVIEWINFO struPlayInfo;
    memset(&struPlayInfo,0,sizeof(struPlayInfo));
    if(videowidget != nullptr)
    {
        struPlayInfo.hPlayWnd =wndid; //需要 SDK 解码时句柄设为有效值,仅取流不解码时可设为空
    }else
    {
        close();
    }
    struPlayInfo.lChannel = 1;//预览通道号
    struPlayInfo.dwStreamType = Config::GetConfig()->streamtype(); //0-主码流,1-子码流,2-码流 3,3-码流 4,以此类推
    struPlayInfo.dwLinkMode = 0; //0- TCP 方式,1- UDP 方式,2- 多播方式,3- RTP 方式,4-RTP/RTSP,5-RSTP/HTTP
    struPlayInfo.bBlocked = 0; //0- 非阻塞取流,1- 阻塞取流
    lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, NULL, NULL);
    if(lRealPlayHandle == -1)
    {
        emit playerror();
        return false;
    }

    if(m_ip !=ip || m_port!=port || m_username !=username || m_password !=password)
    {
        m_ip=ip;
        m_port=port;
        m_username=username;
        m_password=password;
    }

    return true;
}

void HikvisonWapper::reopen()
{
    open(m_ip,m_port,m_username,m_password);
}



void HikvisonWapper::close()
{
    if(lRealPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(lRealPlayHandle);
    }

    if(lUserID >= 0)
    {
        NET_DVR_Logout(lUserID);
    }

}


void HikvisonWapper::handleplayerror()
{
    videowidget = nullptr;
    if (lUserID == -1)
    {
        emit errormsg(QString("").append(NET_DVR_GetLastError()));
        return;
    }

    if (lRealPlayHandle == -1)
    {
        emit errormsg(QString("").append(NET_DVR_GetLastError()));
        NET_DVR_Logout(lUserID);
        return;
    }
}

void HikvisonWapper::handleptzerror()
{
    emit errormsg(QString("").append(NET_DVR_GetLastError()));
}

// state:
// 0--开始 1--停止
void HikvisonWapper::ptzup(int state)
{
    bool re=NET_DVR_PTZControlWithSpeed(lRealPlayHandle, TILT_UP,state, 3);
    if(!re)
    {
        emit ptzerror();
    }
}

void HikvisonWapper::ptzdown(int state)
{
    bool re=NET_DVR_PTZControlWithSpeed(lRealPlayHandle, TILT_DOWN,state, 3);
    if(!re)
    {
        emit ptzerror();
    }
}

void HikvisonWapper::ptzright(int state)
{
    bool re=NET_DVR_PTZControlWithSpeed(lRealPlayHandle, PAN_RIGHT,state, 3);
    if(!re)
    {
        emit ptzerror();
    }
}


void HikvisonWapper::ptzleft(int state)
{
    bool re=NET_DVR_PTZControlWithSpeed(lRealPlayHandle, PAN_LEFT,state, 3);
    if(!re)
    {
        emit ptzerror();
    }
}

void HikvisonWapper::ptzzoomin(int state)
{
    bool re=NET_DVR_PTZControlWithSpeed(lRealPlayHandle, ZOOM_IN,state, 3);
    if(!re)
    {
        emit ptzerror();
    }
}

void HikvisonWapper::ptzzoomout(int state)
{
    bool re=NET_DVR_PTZControlWithSpeed(lRealPlayHandle, ZOOM_OUT,state, 3);
    if(!re)
    {
        emit ptzerror();
    }
}



